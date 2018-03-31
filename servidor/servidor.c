#include "servidor.h"

t_log * logger;

int main(void)
{
	logger = log_new("servidor.log");

	int listener = init_listener(PORT, 10);

	fd_set connected_fds;
	fd_set read_fds;

	FD_ZERO(&connected_fds);
	FD_ZERO(&read_fds);
	FD_SET(listener, &connected_fds);

	int max_fd = listener;

	while (1) {
		read_fds = connected_fds;
		if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
			log_write(logger, ERROR, "Error select()");
			exit(EXIT_FAILURE);
		}

		int fd;
		for (fd = 0; fd <= max_fd; fd++) {
			if (FD_ISSET(fd, &read_fds) == 0) {
				continue;
			} else if (fd == listener) {
				struct sockaddr_in client_info;
				socklen_t addrlen = sizeof client_info;
				log_write(logger, INFO, "Nuevo cliente conectando...");

				int new_client_fd = accept(listener, (struct sockaddr *) &client_info, &addrlen);
				if (new_client_fd == -1) {
					log_write(logger, ERROR, "Error accept()");
				} else {
					FD_SET(new_client_fd, &connected_fds);
					if (new_client_fd > max_fd) {
						max_fd = new_client_fd;
					}
					log_info(logger, "Socket %d conectado", new_client_fd);
					if (send_hello(new_client_fd) == -1) {
						remove_fd(new_client_fd, &connected_fds);
						log_error(logger, "Fallo en el handshake con el Socket %d", new_client_fd);
					}
					if (send_content(new_client_fd) == -1) {
						remove_fd(new_client_fd, &connected_fds);
						log_error(logger, "Envío fallido de mensaje al Socket %d", new_client_fd);
					}
					log_info(logger, "Se envió un mensaje correctamente al Socket %d", new_client_fd);
				}
			} else {

			}
		}
	}
}

int send_hello(int fd)
{
	char *message = strdup("holapedazodegil");
	int ret = send(fd, (void *)message, strlen(message) + 1, 0);
	if (ret == -1) {
		log_error(logger, "Error al enviar hello");
	}
	return ret;
}

void remove_fd(int fd, fd_set *fdset)
{
	FD_CLR(fd, fdset);
	log_info(logger, "El socket %d fue echado", fd);
	close(fd);
}

int send_content(int fd) {

	char* datos = "Hola, capo. ACM1PT";
	int id = 18;
	int tamanio_dato = strlen(datos) + 1;

	void* paquete = malloc(sizeof(id) + sizeof(tamanio_dato) + tamanio_dato);

	memcpy(paquete, &id, sizeof(id));
	paquete += sizeof(id);

	memcpy(paquete, &tamanio_dato, sizeof(tamanio_dato));
	paquete += sizeof(tamanio_dato);

	memcpy(paquete, datos, tamanio_dato);
	paquete -= sizeof(int) - sizeof(size_t);

	int ret = send(fd, paquete, sizeof(id) + sizeof(tamanio_dato) + tamanio_dato, 0);

	free(paquete);
	return ret;

}

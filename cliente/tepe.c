#include "tepe.h"

t_log *logger;

void wait_hello(int fd);

int main(void) {
	logger = log_new("cliente.log");
	int fd = connect_to_server(HOST, PUERTO);
	wait_hello(fd);
	wait_content(fd);
	while (1);
}

void wait_content(int fd) {
	int id;
	int size;

	int ret = recv(fd, &id, sizeof(id), 0);
	if (ret == -1) {
		log_error(logger, "Error al recibir el contenido\n");
	}

	ret = recv(fd, &size, sizeof(size), 0);
	if (ret == -1) {
		log_error(logger, "Error al recibir el contenido\n");
	}

	char* datos = malloc(size);

	ret = recv(fd, datos, size, 0);
	if (ret == -1) {
		log_error(logger, "Error al recibir el contenido\n");
	}

	log_info(logger, "Mensaje recibido: %s\n",datos);
}

void wait_hello(int fd) {
	char *message = malloc(16);
	int ret = recv(fd, (void *) message, 16, 0);
	if (ret != -1) {
		printf("%s\n", message);
		log_info(logger, "%s\n", message);
	} else {
		log_error(logger, "Error al recibir hello\n");
		exit(EXIT_FAILURE);
	}

}

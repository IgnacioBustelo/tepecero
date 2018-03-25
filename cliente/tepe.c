#include "tepe.h"

t_log *logger;

void wait_hello(int fd);

int main(void)
{
	logger = log_new("cliente.log");
	int fd = connect_to_server(HOST, PUERTO);
	wait_hello(fd);
}

void wait_hello(int fd)
{
	char *message = malloc(16);
	int ret = recv(fd, (void *)message, 16, 0);
	if (ret != -1) {
		printf("%s\n", message);
		log_info(logger, "%s\n", message);
	} else {
		log_error(logger, "Error al recibir hello\n");
		exit(EXIT_FAILURE);
	}
}

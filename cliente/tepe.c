#include "tepe.h"

t_log *logger;

int main(void) {
	logger = log_new("cliente.log");
	int fd = connect_to_server(HOST, PUERTO);
	wait_hello(fd);
	wait_content(fd);
	while (1)
		;
}

package_t* wait_package(int fd) {
	package_t *package = malloc(sizeof(package_t));

	int ret = recv(fd, &(package->id), sizeof(package->id), 0);
	if (ret == -1) {
		free(package);
		return NULL;
	}

	ret = recv(fd, &(package->size), sizeof(package->size), 0);
	if (ret == -1) {
		free(package);
		return NULL;
	}

	package->data = malloc(package->size);

	ret = recv(fd, package->data, package->size, 0);
	if (ret == -1) {
		free(package->data);
		free(package);
		return NULL;
	}

	return package;
}

void wait_content(int fd) {
	package_t *package = wait_package(fd);
	if (package == NULL) {
		log_error(logger, "Error al recibir el paquete\n");
	}

	log_info(logger, "Mensaje recibido: %s\n", (char *)package->data);
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

char* hash_md5(char* input, size_t input_size) {
	unsigned char digest[16];

	MD5((unsigned char*) input, input_size, digest);

	char md5_str[33];
	int i;
	for (i = 0; i < 16; i++) {
		sprintf(&md5_str[i * 2], "%02x", (unsigned int) digest[i]);
	}

	return strdup(md5_str);
}

void *serialize_package(package_t *package, size_t *size) {
	*size = sizeof(package->id) + sizeof(package->size) + package->size;

	void* buffer = malloc(*size);

	memcpy(buffer, &(package->id), sizeof(package->id));
	buffer += sizeof(package->id);

	memcpy(buffer, &(package->data), sizeof(package->data));
	buffer += sizeof(package->data);

	memcpy(buffer, package->data, package->size);
	buffer -= sizeof(package->id) + sizeof(package->size);

	return buffer;
}

void wait_confirmation(int fd) {
	int confirmation;
	int ret = recv(fd, &confirmation, sizeof(confirmation), 0);
	if (ret == -1) {
		log_error(logger, "Error en el recv()\n");
	}

	if (confirmation == 1) {
		log_info(logger, "Esta todo OK\n");
	} else if (confirmation == 0) {
		log_error(logger, "RIP\n");
	} else {
		log_info(logger, "Que carajos\n");
	}
}

void send_md5(int fd, package_t *input) {
	char *md5 = hash_md5(input->data, input->size);

	package_t package;
	package.id = 33;
	package.size = strlen(md5) + 1;
	package.data = md5;

	size_t buffer_size;
	char *buffer = serialize_package(&package, &buffer_size);

	send(fd, buffer, buffer_size, 0);
	wait_confirmation(fd);
}

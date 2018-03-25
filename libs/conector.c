#include "conector.h"
#include "errno.h"

int connect_to_server(char *host, int port)
{
	struct sockaddr_in conexion_server;
	conexion_server.sin_family = AF_INET;
	conexion_server.sin_addr.s_addr = inet_addr(host);
	conexion_server.sin_port = htons(port);
	memset(&(conexion_server.sin_zero), 0, sizeof(conexion_server.sin_zero));

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(fd,
			(struct sockaddr *) &conexion_server,
			sizeof(conexion_server)) < 0) {
		return -1;
	}

	return fd;
}

int init_listener(int listen_port, int max_conn)
{
	int listener_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listener_fd == -1) {
		return NO_FD_ERROR;
	}

	int activate = 1;
	setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &activate, sizeof(activate));

	struct sockaddr_in listener_info;

	listener_info.sin_family = AF_INET;
	listener_info.sin_port = htons(listen_port);
	listener_info.sin_addr.s_addr = INADDR_ANY;
	memset(&(listener_info.sin_zero), 0, 8);

	if (bind(listener_fd, (struct sockaddr*) &listener_info, sizeof(struct sockaddr)) == -1) {
		return BIND_ERROR;
	}

	if (listen(listener_fd, max_conn) == -1) {
		return LISTEN_ERROR;
	}

	return listener_fd;
}

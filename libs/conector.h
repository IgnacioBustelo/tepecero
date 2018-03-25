#ifndef CONECTOR_H_
#define CONECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

/**
 * Retorna el FD.
 */
int connect_to_server(char *host, int port);

#define NO_FD_ERROR		-1
#define BIND_ERROR		-2
#define LISTEN_ERROR	-3
int init_listener(int listen_port, int max_conn);

#endif /* CONECTOR_H_ */

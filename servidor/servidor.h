#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "../libs/conector.h"
#include "../libs/log.h"

#define PORT 8080

int send_hello(int fd);
void remove_fd(int fd, fd_set *fdset);
void send_content(int fd);

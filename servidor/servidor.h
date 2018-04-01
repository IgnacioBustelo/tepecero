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
int send_content(int fd);
int recv_md5(int fd);
int send_confirmation(int fd, int ret);

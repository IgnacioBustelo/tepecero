#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>

#include "../libs/conector.h"
#include "../libs/log.h"

#define HOST "127.0.0.1"
#define PUERTO 8080

typedef struct {
	int id_mensaje;
	int legajo;
	char nombre[40];
	char apellido[40];
}__attribute__((packed)) Alumno;

typedef struct {
	int id;
	int size;
	void *data;
} package_t;

void wait_hello(int fd);
package_t *wait_content(int fd);
void send_md5(int fd, package_t *input);

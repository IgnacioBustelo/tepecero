#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>

#include "../libs/conector.h"
#include "../libs/log.h"

#define HOST "192.168.0.30"
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
void wait_content(int fd);

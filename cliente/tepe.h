#include <stdio.h>
#include <stdlib.h>

#include "../libs/conector.h"
#include "../libs/log.h"

#define HOST "192.168.0.18"
#define PUERTO 8080

typedef struct {
  int id_mensaje;
  int legajo;
  char nombre[40];
  char apellido [40];
} __attribute__((packed)) Alumno;

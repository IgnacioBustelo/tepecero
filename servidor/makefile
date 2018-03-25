CC = gcc

all: servidor

servidor: servidor.c ../libs/log.c ../libs/conector.c
	$(CC) servidor.c ../libs/log.c ../libs/conector.c -o servidor -lcommons

debug: CC += -DDEBUG -g
debug: all

clean:
	rm -f servidor
	
.PHONY: clean
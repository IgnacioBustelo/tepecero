CC = gcc

all: tepe

tepe: tepe.c tepe.h ../libs/conector.c ../libs/log.c
	$(CC) tepe.c ../libs/conector.c ../libs/log.c -o tepe -lcommons -lcrypto
	
debug: CC += -DDEBUG -g
debug: all
	
clean:
	rm -rf tepe
	rm -rf cliente.log
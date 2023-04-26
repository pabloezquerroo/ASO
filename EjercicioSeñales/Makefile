all: mensaje

mensaje: mensaje.o
	gcc -o mensaje mensaje.o

mensaje.o: mensaje.c
	gcc -c mensaje.c

clean: 
	rm mensaje.o mensaje
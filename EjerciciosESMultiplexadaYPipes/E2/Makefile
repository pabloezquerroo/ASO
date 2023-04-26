

all: programa

programa: programa.o
	gcc -g -o programa programa.o

programa.o: programa.c
	gcc -c -g programa.c

clean:
	rm programa.o programa
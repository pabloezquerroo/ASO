
all: programa

programa: cerrojos.o
	gcc -o programa cerrojos.o

cerrojos.o: cerrojos.c
	gcc -c cerrojos.c

clean:
	rm cerrojos.o programa
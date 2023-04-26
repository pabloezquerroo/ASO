

all: programa programa2

programa: programa.o
	gcc -o programa programa.o

programa2: programa2.o
	gcc -o programa2 programa2.o

programa.o: programa.c
	gcc -c programa.c

programa2.o: programa2.c
	gcc -c programa2.c

clean:
	rm programa.o programa programa2.o programa2
	rm tuberia1 tuberia2
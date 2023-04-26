

all: programa

programa: myls.o
	gcc -o programa myls.o

myls.o: myls.c
	gcc -c myls.c

clean:
	rm myls.o programa
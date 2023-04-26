#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/select.h>

#define MAX_BUF 1024

int main(int argc, char *argv[]) {
    int fd1, fd2, fdmax, i, retval;
    fd_set rfds;
    char buf[MAX_BUF];

    int r; //bytes leidos

    const char *nombre1 = "tuberia1";
    const char *nombre2 = "tuberia2";

    if (argc != 1) {
        printf("Numero de argumentos invalido\n");
        return 1;
    }

    mkfifo(nombre1, 0666);
    mkfifo(nombre2, 0666);

    fd1 = open(nombre1, O_RDONLY | O_NONBLOCK);
    fd2 = open(nombre2, O_RDONLY | O_NONBLOCK);

    if (fd1 == -1 || fd2 == -1) {
        perror("Error al abrir la tuberia");
        return 1;
    }

    fdmax = fd1 > fd2 ? fd1 : fd2;
    fdmax = fdmax > STDIN_FILENO ? fdmax : fdmax;

    while (1) {
        FD_ZERO(&rfds);
        FD_SET(fd1, &rfds);
        FD_SET(fd2, &rfds);
        FD_SET(STDIN_FILENO, &rfds);

        retval = select(fdmax+1, &rfds, NULL, NULL, NULL);

        if (retval == -1) {
            perror("select()");
            return 1;
        }
        else if (retval > 0) {
            for (i = 0; i <= fdmax; i++) {
                if (FD_ISSET(i, &rfds)) {
                    if (i == fd1) {
                        r=read(fd1, buf, MAX_BUF);
                        if (r > 0) {
                            printf("Tuberia 1: %s\n", buf);
                        }
                    }
                    else if (i == fd2) {
                        r=read(fd2, buf, MAX_BUF);
                        if (r > 0) {
                            printf("Tuberia 2: %s\n", buf);
                        }
                    }else if (i==STDIN_FILENO){
                        if(read(STDIN_FILENO, buf, MAX_BUF)==0){
                            printf("Terminando porgrama...\n");
                            exit(-1);
                        }
                    }
                }
            }
        }
    }

    close(fd1);
    close(fd2);

    return 0;
}

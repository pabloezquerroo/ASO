#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
        int fd;
        int seleccion=0;
        const char *nombre1= "tuberia1";
        const char *nombre2= "tuberia2";

        if (argc!=2){
                printf("numero de argumentos invalido");
                return 1;
        }
        
        while (seleccion!=1 && seleccion!=2){
                printf("Por que tubería quieres transmitir(1 o 2): ");
                scanf("%d", &seleccion);
                if (seleccion!=1 && seleccion!=2){
                        printf("valor no valido\n");
                }
                
        }

        if (seleccion==1){
                fd= open(nombre1, O_WRONLY);
        }else{
                fd= open(nombre2, O_WRONLY);
        }

        if (fd==-1){
                perror("Error al abrir la tuberia");
                return 1;
        }

        if (write(fd, argv[1], strlen(argv[1]))==-1){
                perror("Error al escribir en la tuberia");
                close(fd);
                return 1;
        }

        close(fd);
        return 0;
}
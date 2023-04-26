#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]){
        if (argc!=2){
                printf("Numero de argumentos no valido\n");
                return 1;
        }
        
        int fd= open(argv[1], O_RDWR|O_APPEND);
        if (fd== -1){
                printf("Error al leer el archivo\n");
                return 1;
        }

        struct flock cerrojo;

        cerrojo.l_len= 0;
        cerrojo.l_start= 0;
        cerrojo.l_type= F_WRLCK;
        cerrojo.l_whence= SEEK_SET;

        int estado= fcntl(fd, F_GETLK, &cerrojo);

        if (estado==-1){
                printf("Error al leer el cerrojo\n");
                return 1;
        }
        
        //Archivo bloqueado
        if(cerrojo.l_type != F_UNLCK){
                printf("El archivo esta bloqueado\n");
                return 1;

        }

        //Archivo desbloqueado
        cerrojo.l_len= 0;
        cerrojo.l_start= 0;
        cerrojo.l_type= F_WRLCK;
        cerrojo.l_whence= SEEK_SET;
        if (fcntl(fd, F_SETLK, &cerrojo)==-1){
                printf("Error al bloquear el archivo\n");
                return 1;
        }

        time_t t;
        time(&t);
        char *time_string = ctime(&t);
        if(write(fd, time_string, strlen(time_string))==-1){
                printf("Error al escribir en el fichero\n");
                return 1;
        }

        sleep(40);

        cerrojo.l_type = F_UNLCK;
        estado = fcntl(fd, F_SETLK, &cerrojo);
        if (estado == -1) {
            printf("Error al desbloquear el cerrojo\n");
            return 1;
        }

        return 0;
}


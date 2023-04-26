#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <bits/sigaction.h>
#include <time.h>

int segundos=0;
__time_t t0;
__time_t t1;

void handler(int sig){
        t1=time(&t1);
        segundos=t1-t0;
        printf("Segundos transcurridos: %ds\n", segundos);
        exit(1);
}

int main(int argc, char *argv[]){
        t0= time(&t0);
        if (argc!=2){
                printf("Numero de atgumentos no valido\n");
                return 1;
        }

        struct sigaction sa;
        sa.sa_handler=handler;
        sigaction(SIGTERM, &sa, NULL);

        signal(SIGINT, SIG_IGN);

        int s = atoi(argv[1]);

        while (1){
                segundos+=s;
                printf("Ejecutando programa...\n");
                sleep(s);

        }
        
        return 0;
}
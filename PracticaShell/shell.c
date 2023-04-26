/* shell.c -- Shell elemental. Solo admite jobs con una orden */
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

// Variables globales
struct listaJobs listaJobs = {NULL, NULL};



// Programa principal
int main(int argc, char **argv) {

    char orden[LONG_MAX_ORDEN + 1];
    char *otraOrden = NULL;
    struct job JobNuevo;
    int esBg=0;

    // Procesamiento argumentos de entrada (versión simplificada)
    if (argc > 1) {
        fprintf(stderr, "Uso: Shell");
        exit(EXIT_FAILURE);
    }

    // Ignorar la señal SIGTTOU, capturar SIGINT, SIGQUIT...
    signal(SIGTTOU, SIG_IGN);
        signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);


    // Repetir
    while (1) {
    
    // Si no hay job_en_foreground
		if (!listaJobs.fg){

	    // Comprobar finalización de jobs
		compruebaJobs(&listaJobs);

			// Leer ordenes
			if (!otraOrden) {
				if (leeOrden(stdin, orden)) break;
				otraOrden = orden;
			}

			// Si la orden no es vacia, analizarla y ejecutarla
			if (!analizaOrden(&otraOrden,&JobNuevo,&esBg) && JobNuevo.numProgs) {
				ejecutaOrden(&JobNuevo,&listaJobs,esBg);
			}

		}
    // (Else) Si existe job en foreground
		else{
			int estado;
			pid_t pid;
			// Esperar a que acabe el proceso que se encuentra en foreground
			pid =waitpid(listaJobs.fg->progs[0].pid, &estado, WUNTRACED);

			// Recuperar el terminal de control
			if(tcsetpgrp(0, getpid())==-1){
                                perror("Error: setpgid");
                                exit(EXIT_FAILURE);
                        }
			// Si parada_desde_terminal
			if (WIFSTOPPED(estado)){

				// Informar de la parada
				printf("\nJob %d detenido desde el terminal\n", listaJobs.fg->jobId);

				// Actualizar el estado del job y la lista
                                listaJobs.fg->runningProgs=0;
				listaJobs.fg=NULL;
			}else if (WIFSIGNALED(estado)){
                        
                                // Informar de la parada
                                printf("\nJob %d terminado por señal\n", listaJobs.fg->jobId);
                                eliminaJob(&listaJobs, listaJobs.fg->progs[0].pid, 0);
                                listaJobs.fg=NULL;
                                // Actualizar el estado del job y la lista
                        }
			// (Else) si no
			else {
				// Eliminar el job de la lista
				eliminaJob(&listaJobs, listaJobs.fg->progs[0].pid, 0);
                                listaJobs.fg=NULL;
			}
		}
    }

   // Salir del programa (codigo error)
   exit(EXIT_FAILURE);
}




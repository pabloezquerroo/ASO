#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
        int descf[2];
        
        if (pipe(descf)==-1){
                perror("pipe");
                return 1;
        }

        pid_t pid= fork();

        if (pid == -1) { //error
                perror("fork");
                return 1;
        }else if (pid==0){ // hijo
                dup2(descf[0], STDIN_FILENO);
                close(descf[1]);
                execlp(argv[3], argv[3], argv[4], NULL);
        }else{ // padre
                dup2(descf[1], STDOUT_FILENO);
                close(descf[0]);
                execlp(argv[1], argv[1], argv[2], NULL);
        }
        return 0;
}
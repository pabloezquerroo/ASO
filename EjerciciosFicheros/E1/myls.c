#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>


void casos(struct dirent *dt,  char path[256]){
        struct stat aux;
        stat(path, &aux);
        switch (dt->d_type)
        {
                case DT_REG:
                        printf("%s (%d kb, %d link)\n", dt->d_name, aux.st_size, aux.st_nlink);
                        break;
                case DT_DIR:
                        printf("[%s] (%d links)\n", dt->d_name, aux.st_nlink);
                        break;
                case DT_LNK:
                        {
                                char buf[256];
                                ssize_t len = readlink(path, buf, sizeof(buf) - 1);
                                if (len != -1) {
                                        buf[len] = '\0';
                                        printf("%s (%s)\n", dt->d_name, buf);
                                } else {
                                        printf("Error al leer enlace simbólico\n");
                                }
                        }
                        break;
                default:
                        printf("default");
                        break;
        }
}

int main(int argc, char *argv[]){
	DIR *dir;
	struct stat st;
	struct dirent *dt;
        char raiz[256];
        char path[256];
        getcwd(raiz, sizeof(raiz));
        strcat(raiz, "/");
	
	int opt;
	while ((opt = getopt(argc, argv, "d:f:")) != -1) {
		switch(opt){
			case 'd':
				if(stat(optarg, &st)==0){
					if((st.st_mode & __S_IFDIR)&&(st.st_mode&S_IXUSR)&&(st.st_mode&S_IRUSR)){
						dir = opendir(optarg);
						while ((dt = readdir(dir)) != NULL) {
                                                        strcpy(path, raiz);
                                                        strcat(path, dt->d_name);
                                                        casos(dt, path);
                                                }
                                                closedir(dir);
					}
				}else{
					printf("Error al leer el archivo");
				}	
				break;
			case 'f':
                                if(stat(optarg, &st)==0){
                                        if(st.st_mode & __S_IFREG){
                                                int descriptor= open(optarg, O_RDONLY);
                                                char *name= basename(optarg); 
                                                printf("%s (inodo %d, %d kb)\n",name, st.st_ino, st.st_size);
                                        }else{
                                                printf("No es un fichero regular\n");
                                        }
                                }
				break;
			case '?':
				printf("Opción invalida\n");
				break;
			default:
				break;
		}
	}
	return 0;
}
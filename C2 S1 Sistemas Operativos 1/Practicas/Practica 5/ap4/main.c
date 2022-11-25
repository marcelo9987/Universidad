#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

void procmap(int numUso)
{
    char nombreArchivoDestino[5];
    sprintf(nombreArchivoDestino, "%s%i", "mem", numUso);
    FILE *archivo = fopen(nombreArchivoDestino, "w+");
    
    char nombreArchivo[0xfff];
    sprintf(nombreArchivo, "%s%d%s", "/proc/", getpid(), "/maps");
    FILE* contenidosMapaMemoria;
    contenidosMapaMemoria = fopen(nombreArchivo, "r");
    int counter =0;
    
    char buffer[300];
    while(1)
    {
        
        fgets(buffer, sizeof(buffer), contenidosMapaMemoria);
        if(feof(contenidosMapaMemoria))
        {
            break;
        }
        fprintf(archivo,"%s",buffer);
        
        ++counter;
    }
    printf("He leído %i líneas",counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}

int main()
{
    char pausa[20];
    printf("[Padre:%i] Soy el padre\n", getpid());
    pid_t pid_hijo;
    int status_hijo;
    procmap(0);
    scanf("%s",pausa);
    if ((pid_hijo = fork()) < 0)
    {
        perror("fork() error");
    } else if (pid_hijo == 0)
    {
        procmap(10);
        
        scanf("%s",pausa);
        printf("[Hijo: %i] Soy el hijo\n", (int) getpid());
        double *memoriaReservada = (double*) malloc(403010 * sizeof(double ));
        procmap(11);
//        system("ls");
        execl("../hijoAcopiar","../hijoAcopiar",NULL);
        free(memoriaReservada);
        exit(0);
    }else
    {
        procmap(1);
        sleep(30);
        wait(&status_hijo);
    }
    return 0;
}

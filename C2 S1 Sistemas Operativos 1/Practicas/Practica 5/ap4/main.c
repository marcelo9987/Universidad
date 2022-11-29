#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

#define esperar()
//#define esperar() \
//{                 \
//    printf("\nContinuar: ");\
//    while(getchar()!='\n');\
//}

//#define procmap(numUso)
#define procmap(numUso) _procmap(numUso)


void _procmap(int numUso)
{
    char nombreArchivoDestino[20];
    sprintf(nombreArchivoDestino, "%s%i.mem", "maps", numUso);
    FILE* archivo = fopen(nombreArchivoDestino, "w+");
    
    char nombreArchivo[0xfff];
    sprintf(nombreArchivo, "%s%d%s", "/proc/", getpid(), "/maps");
    FILE* contenidosMapaMemoria;
    contenidosMapaMemoria = fopen(nombreArchivo, "r");
    int counter = 0;
    
    char buffer[300];
    while (1)
    {
        
        fgets(buffer, sizeof(buffer), contenidosMapaMemoria);
        if (feof(contenidosMapaMemoria))
        {
            break;
        }
        fprintf(archivo, "%s", buffer);
        
        ++counter;
    }
    printf("He leído %i líneas.\n", counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}

int main()
{
    printf("[Padre:%i] Soy el padre\n", getpid());
    
    
    procmap(0);
    
    char* memoriaReservadaPrevia = (char*) malloc(1024 * sizeof(char));
    
    printf("[Común] memoriaReservadaPrevia %p\n", memoriaReservadaPrevia);
    
    
    procmap(1);
    
    pid_t pid_hijo;
    if ((pid_hijo = fork()) < 0)
    {
        perror("fork() error");
        free(memoriaReservadaPrevia);
        exit(-1);
    }
    
    if (pid_hijo == 0)
    {
        printf("[Hijo: %i] Soy el hijo\n", (int) getpid());
        
        printf("[Hijo] memoriaReservadaPrevia %p\n", memoriaReservadaPrevia);
        
        procmap(10);
        
        double* memoriaReservadaHijo = (double*) malloc(403010 * sizeof(double));
        printf("[Hijo] memoriaReservadaHijo %p\n", memoriaReservadaHijo);
        
        procmap(11);
        
        if (execl("./hijoAcopiar", "./hijoAcopiar", NULL) == -1)
        {
            perror("Fallo en ejecución de execl");
            free(memoriaReservadaHijo);
            free(memoriaReservadaPrevia);
        }
        
        exit(-1);
    } else
    {
        printf("[Padre] memoriaReservadaPrevia %p\n", memoriaReservadaPrevia);
        
        procmap(20);
        
        int status_hijo;
        wait(&status_hijo);
        
        if (WIFEXITED(status_hijo))
        {
            printf("Child exited with RC=%d\n", WEXITSTATUS(status_hijo));
        } else if (WIFSIGNALED(status_hijo))
        {
            printf("Child exited via signal %d\n", WTERMSIG(status_hijo));
        }
        free(memoriaReservadaPrevia);
        
        return 0;
    }
}

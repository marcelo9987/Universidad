/**
 * @file muereHijo.c
 * @date 2012-11-20
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void dormir()
{
//    pause();
    raise(SIGSTOP);
}

void despertar(pid_t pid_otro)
{
    kill(pid_otro, SIGCONT);
}

int main()
{
    pid_t pid_padre = getpid();
    pid_t pid_procesoHijo = fork();
    if (pid_procesoHijo == -1)
    {
        perror("Error al crear el proceso hijo");
        return -1;
    } else if (pid_procesoHijo == 0)
    { // Proceso hijo
        pid_procesoHijo = getpid();
        printf("[Hijo  :: %d] Espero un segundo para que le dé tiempo al padre a dormirse\n", pid_procesoHijo);
        
        sleep(1);
        
        printf("[Hijo  :: %d] Entro en la región crítica (realmente no voy a hacer nada)\n", pid_procesoHijo);
        
        // División por cero
//        int t = 14 / 0;
        
        printf("[Hijo  :: %d] Salgo de la región crítica. Despierto al padre\n", pid_procesoHijo);
        despertar(pid_padre);
        
        printf("[Hijo  :: %d] Finalizo mi ejecución.\n", pid_procesoHijo);
        exit(0);
    } else
    {// Proceso padre
        
        printf("[Padre :: %d] Me duermo porque mi hijo va a entrar a la región crítica\n", pid_padre);
        dormir();
        printf("[Padre :: %d] Mi hijo me ha despertado pues ha salido de la región crítica\n", pid_padre);
        
        printf("[Padre :: %d] Espero a que el hijo termine\n", pid_padre);
        waitpid(pid_procesoHijo, NULL, 0);
        printf("[Padre :: %d] El hijo ha terminado. Finalizo mi ejecución\n", pid_padre);
        exit(0);
    }
}

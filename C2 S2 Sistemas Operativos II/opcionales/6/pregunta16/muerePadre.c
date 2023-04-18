/**
 * @file muerePadre.c
 * @date 2012-11-20
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define true 1

void dormir()
{
//    pause();
    raise(SIGSTOP);
//    while (true);
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
    } else if (pid_procesoHijo != 0)
    { // Proceso padre
        
        printf("[Padre :: %d] Espero un segundo para que le dé tiempo al hijo a dormirse\n", pid_padre);
        
        sleep(1);
        
        printf("[Padre :: %d] Entro en la región crítica (realmente no voy a hacer nada)\n", pid_padre);
        
        // División por cero
//        int t = 14 / 0;
        
        printf("[Padre :: %d] Salgo de la región crítica. Despierto al hijo\n", pid_padre);
        despertar(pid_procesoHijo);
        
        printf("[Padre :: %d] Espero a que el hijo termine\n", pid_padre);
        waitpid(pid_procesoHijo, NULL, 0);
        printf("[Padre :: %d] El hijo ha terminado. Finalizo mi ejecución\n", pid_padre);
        
        exit(0);
    } else
    {// Proceso hijo
        pid_procesoHijo = getpid();
        printf("[Hijo  :: %d] Me duermo porque mi padre va a entrar a la región crítica\n", pid_procesoHijo);
        dormir();
        printf("[Hijo  :: %d] Mi padre me ha despertado pues ha salido de la región crítica. Finalizo mi ejecución\n", pid_procesoHijo);
        
        exit(0);
    }
}

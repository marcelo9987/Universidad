/* Haz un programa que cree un proceso hijo, espere 5 segundos y le envíe la señal SIGUSR1. El
*  hijo al ser generado ejecuta la llamada al sistema pause que lo bloqueará hasta que reciba una señal.
*  Comprueba que el hijo se desbloquea (sale del pause) al recibir la señal.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void handler(int);

int main()
{
    
    pid_t hijo;
    if((hijo=fork())==-1)
    {
        printf("Error en el fork del hijo");
        exit(-1);
    }
    if(hijo==0)
    {
        if(signal(SIGUSR1,handler)==SIG_ERR)
        {
            printf("Algo no ha salido bien.\n");
            exit(-1);
        }
        pause();
        printf("[Hijo] He salido del pause\n");
        exit(0);
    }
    sleep(5);
    printf("[Padre] Enviando SIGUSR1 al hijo\n");
    kill(hijo,SIGUSR1);
    printf("[Padre] Esperando al hijo\n");
    
    int status;
    pid_t pidSalida = wait(&status);
    if (WIFEXITED(status))
    {
        printf("[Parent] Child %d exited with RC=%d\n", pidSalida,WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status))
    {
        printf("[Parent] Child %d exited with SIG=%d\n",pidSalida, WTERMSIG(status));
    }
    return 0;
}

void handler(int senhal)
{
    switch(senhal)
    {
        case SIGUSR1:
            printf("[Hijo]¡He gestionado la primera!\n");
            break;
        
    }
}

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

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
    printf("Soy el padre y mi pid es %d\n", getpid());
    
    pid_t pid_procesoHijo = fork();
    if (pid_procesoHijo == -1)
    {
        perror("Error al crear el proceso hijo");
        return -1;
    } else if (pid_procesoHijo == 0)
    { // Proceso hijo
        pid_procesoHijo = getpid();
        printf("Soy el proceso hijoS y mi pid es %d\n", getpid());
        printf("[Hijo :: %d] Me duermo\n", pid_procesoHijo);
        dormir();
        printf("[Hijo :: %d] Me despierto\n",  pid_procesoHijo);
    } else
    {// Proceso padre
        sleep(2);
        
        despertar(pid_procesoHijo);
        
        waitpid(pid_procesoHijo, NULL, 0);
    }
    return 0;
}

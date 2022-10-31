#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>


void manej(int n)
{
    switch(n)
    {
        case SIGTERM:
            exit(1);
            
        case SIGUSR1:
            printf("hola");
            break;
    }
    
    
}
int main()
{
    signal(SIGTERM,manej);
    pid_t procesoHijo = fork();
    if (procesoHijo == 0)
    {
        //raise(SIGTERM);
        exit(1);
    } else
    {
        int chld_state;
        wait(&chld_state);
        if (WIFEXITED(chld_state))
        {
            printf("Child exited with RC=%d\n", WEXITSTATUS(chld_state));
        }
        if (WIFSIGNALED(chld_state))
        {
            printf("Child exited via signal %d\n", WTERMSIG(chld_state));
        }
    }
    
    return 0;
}

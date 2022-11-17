#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


void * handle(void* args)
{
    printf("[PADRE] [Hilo %i] mi pid es: %i\n",(int)args,getpid());
    switch((int)args)
    {
        case 0:
            
            if(fork()==0)
            {
                printf("Soy el hijo con pid %i\n",getpid());
                sleep(5);
                printf("me voy.\n");
                exit(0);
            }else
            {
                sleep(30);
                printf("[HILO1] ME VOY \n");
            }
            break;
        case 1:
            {
            int status;
            wait(&status);
            printf("Algo ha muerto.\n");
            sleep(60);
            }
            break;
        case 2:
            sleep(60);
            break;
        default:
            printf("ERROR: hilo no reconocido.\n");
    }
    sleep(2);
    pthread_exit("he salido correctamente.\n");
}
int main()
{
    printf("[PADRE] [Hilo0] mi pid es: %i\n",getpid());
    pthread_t hilo1,hilo2,hilo3;
    
    
    if(pthread_create(&hilo1,NULL,handle,(void*)0)!=0)
    {
        perror("Fallo al crear el hilo.\n");
    }
    sleep(1);
    if(pthread_create(&hilo2,NULL,handle,(void*)1)!=0)
    {
        perror("Fallo al crear el hilo.\n");
    }
    sleep(1);
    
    if(pthread_create(&hilo3,NULL,handle,(void*)2)!=0)
    {
        perror("Fallo al crear el hilo.\n");
    }
    
    void* ret;
    pthread_join(hilo3,ret);
    pthread_join(hilo2,ret);
    pthread_join(hilo1,ret);
    
    printf("[Padre] He terminado la ejecución!\n");
    return 0;
}

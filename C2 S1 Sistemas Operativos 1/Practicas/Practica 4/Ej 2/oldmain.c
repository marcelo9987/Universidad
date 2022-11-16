#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <unistd.h>


void * handle(void* args)
{
    printf("Soy el hilo %i\n",(int)args);
    sleep(2);
    pthread_exit("he salido correctamente.\n");
}
int main()
{
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

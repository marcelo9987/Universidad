/*
 *  Haz un programa con tres hilos (además del hilo principal) de modo que uno de ellos ejecute exit
 * (no pthread_exit) antes que los otros dos hilos terminen y comprueba que efecto tiene este exit
 * sobre los demás hilos. Debes garantizar que los hilos no nalizan previamente a la ejecución de
 * dicho exit.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
//#pragma clang diagnostic ignored "-Wformat"

void *threadHandle(void* args)
{
    switch((int)args)
    {
        case 1:
            printf("[HILO 1] me dispongo a hacer el exit");
            exit(5);
            
        case 2:
            printf("[HILO 2] voy a dormir 30s");
            sleep(30);
            printf("[HILO 2] Me despierto y me vpy");
            break;
        case 3:
            printf("[HILO 3] voy a dormir 31s");
            sleep(30);
            printf("[HILO 3] Me despierto y me vpy");
            break;
            
        default:
            break;
    }

}
int main()
{
    pthread_t hilo1,hilo2,hilo3;
    void *ret1,*ret2,*ret3;
    printf("[PROCESO ÚNICO][HILO 0] Creando hilo 1.\n");
    if (pthread_create(&hilo1, NULL, threadHandle, 1) != 0)
    {
        perror("pthread_create() error");
        exit(1);
    }
    printf("[PROCESO ÚNICO][HILO 0] Creando hilo 2.\n");
    if (pthread_create(&hilo2,NULL, threadHandle, 2) != 0)
    {
        perror("pthread_create() error");
        exit(1);
    }
    printf("[PROCESO ÚNICO][HILO 0] Creando hilo 3.\n");
    if (pthread_create(&hilo3, NULL, threadHandle, 3) != 0)
    {
        perror("pthread_create() error");
        exit(1);
    }
    
    if (pthread_join(hilo1, &ret1) != 0)
    {
        perror("pthread_create() error");
        exit(3);
    }
    
    printf("[HILO 0] thread %i exited with '%s'\n",hilo1, ret1);
    printf("[HILO 0] thread %i exited with '%s'\n",hilo2, ret2);
    printf("[HILO 0] thread %i exited with '%s'\n",hilo3, ret3);
}

//#pragma clang diagnostic pop
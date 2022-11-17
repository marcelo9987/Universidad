/*
    1. Haz un programa para comprobar que tanto las variables globales como las locales a los hilos
    son accesibles por todos ellos. Comprueba que si un hilo cambia una de esas variables, los demás
    pueden comprobar dicho cambio.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int variableGlobal1=55;

void* rutina1(void* arg)
{
    
    printf("El valor de la variable global es : %i\n",variableGlobal1);
//    printf("El valor de la variable local es : %i\n",variableLocal1);
    sleep(2);
    printf("El valor de la variable global es : %i\n",variableGlobal1);
 //   printf("El valor de la variable local es : %i\n",*arg);
    exit(-3);
    pthread_exit("hola");
}

int main()
{
    pthread_t hilo1;
    int varLocal=3;
    if(pthread_create(&hilo1,NULL,rutina1,NULL) != 0)
    {
        perror("pthread_create() error");
        exit(1);
    }
    sleep(1);
    variableGlobal1 = -33;
    varLocal = -3;
    void ** status;
    
    if (pthread_join(hilo1,status) != 0) {
        perror("pthread_create() error");
        exit(3);
    }
    printf("SALIENDO\n");
    return 0;
}

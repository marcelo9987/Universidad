#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
//#define T 15
//#define M 5000

double suma = 0;
int M, T;

void *sum(void *philo)
{
    uintptr_t hilo = (uintptr_t) philo;
    int j;
    for (j = hilo; j <= M; j += T)
    {
        suma = suma + j;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    { return (-1); }
    M = atoi(argv[1]);
    T = atoi(argv[2]);
    pthread_t hilos[T];
    for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
    {
        pthread_create(&hilos[indice_creacionHilos], NULL, &sum, (void *) indice_creacionHilos);
    }

    for (int indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
    {
        pthread_join(hilos[indice_creacionHilos], NULL);
    }


    fprintf(stdout, "%d,%d,%d,%lf,[%s]\n", M, T, (M * (M + 1)) / 2, suma, (suma - (M * (M + 1)) / 2 == 0) ? "OK" : "Error");
    return (0);
}

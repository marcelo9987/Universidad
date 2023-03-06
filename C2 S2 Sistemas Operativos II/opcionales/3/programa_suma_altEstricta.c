//
// Created by Marcelo on 03/03/2023.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>

int turno =  0;
double suma = 0;
int M, T;

void esperarTurnoRegionCritica(uintptr_t self)
{
    while(turno != self)
    {
        sched_yield();
    }
}

void regionCritica(int j)
{
    suma = suma + j;
}

void regionNoCritica()
{
}

void cederTurnoRegionCritica()
{
    turno ++;
    if(turno>=T)
    {
        turno = 0;
    }
}

void *sum(void *philo)
{
    uintptr_t hilo = (uintptr_t) philo;
    
    for (int j = hilo; j <= M; j += T)
    {
        esperarTurnoRegionCritica(hilo);
        regionCritica(j);
        cederTurnoRegionCritica();
        regionNoCritica();
    }
}



int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        return (-1); 
    }
    M = atoi(argv[1]);
    T = atoi(argv[2]);
    pthread_t hilos[T];
    for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
    {
        pthread_create(&hilos[indice_creacionHilos], NULL, &sum, (void *) indice_creacionHilos);
    }
    
    for (int indice_destruccionHilos = 0; indice_destruccionHilos < T; indice_destruccionHilos++)
    {
        pthread_join(hilos[indice_destruccionHilos], NULL);
    }
    
    long suma_esperada = ((long)M * (long)(M + 1)) / 2L;
    fprintf(stdout, "%d,%d,%ld,%lf,[%s]\n", M, T, suma_esperada, suma, ( (suma - suma_esperada) == 0) ? "OK" : "Error");
    return (0);
}

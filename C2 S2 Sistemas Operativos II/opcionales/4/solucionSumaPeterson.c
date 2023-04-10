/**
* @author Marcelo Fort Muñoz
*/
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//#define kNumHilos 3

double d_suma = 0;

int i_turno = 0;

int M;
int T;

//Array de booleanos para saber si un hilo está interesado en entrar en la región crítica
bool b_interesado[kNumHilos];

/**
 * @brief Región crítica
 * @param j Valor a sumar
 */
void regionCritica(int j)
{
    d_suma = d_suma + j;
}

/**
 * @brief Región no crítica (Nada que hacer)
 */
void regionNoCritica()
{
    //NadaQueHacer
}

/**
 * @brief Calcula el nuevo turno
 * @param entrada_turno Turno actual (Anterior)
 * @param n Nº de hilos
 * @return Nuevo turno (Siguiente)
 */
int nuevoTurno(int entrada_turno, int n)
{
    return (entrada_turno + 1) % n;
}

void *funcionHilo(void *philo)
{
    uintptr_t hilo = (uintptr_t) philo;
    for(int i = hilo;i <=M ;i+=T)
    {
        b_interesado[hilo] = true;
        i_turno = nuevoTurno(i_turno, kNumHilos);
        fprintf(stdout, "Esperando...\n");
        while (b_interesado[hilo] && i_turno == hilo)
        {
            //Esperando a que el turno sea el mío
        }
        regionCritica(hilo);
        b_interesado[hilo] = false;
        regionNoCritica();
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Error en los argumentos. Debe ser: ./solucionSumaPeterson M T");
        return 1;
    }
    M = atoi(argv[1]);
    T = atoi(argv[2]);
    pthread_t hilos[kNumHilos];
    for(int i = 0; i < kNumHilos; i++)
    {
        if (pthread_create(&hilos[i], NULL, (void *) &funcionHilo, (void *) i) != 0)
        {
            printf("Error al crear el hilo %d...\n Abortando. ", i);
        }
    }
    
    for (int i = 0; i < kNumHilos; i++)
    {
        pthread_join(hilos[i], NULL);
    }
    for(int i = 0; i < kNumHilos; i++)
    {
        b_interesado[i] = false;
    }
    
    long suma_esperada = ((long) M * (long) (M + 1)) / 2L;
    
    fprintf(stdout, "Suma esperada: %ld \t Suma obtenida: %f \t Diferencia: %ld \t", suma_esperada, d_suma, suma_esperada - (long) d_suma);
    
}
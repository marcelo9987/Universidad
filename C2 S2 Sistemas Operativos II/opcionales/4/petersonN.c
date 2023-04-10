//
// Created by Marcelo on 03/03/2023.
//
/*
 * tipos de datos:
 * p: puntero
 * i: entero
 * f: flotante
 * pi: puntero a entero
 *
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
//#include <sched.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdatomic.h>

static unsigned cyc_hi = 0;
static unsigned cyc_lo = 0;


/* Set *hi and *lo to the high and low order bits of the cycle counter.
Implementation requires assembly code to use the rdtsc instruction. */
void access_counter(unsigned *hi, unsigned *lo)
{
    asm("rdtsc; movl %%edx,%0; movl %%eax,%1" /* Read cycle counter */
            : "=r" (*hi), "=r" (*lo) /* and move results to */
            : /* No input */ /* the two outputs */
            : "%edx", "%eax");
}

/* Record the current value of the cycle counter. */
void start_counter()
{
    access_counter(&cyc_hi, &cyc_lo);
}

/* Return the number of cycles since the last call to start_counter. */
double get_counter()
{
    unsigned ncyc_hi, ncyc_lo;
    unsigned hi, lo, borrow;
    double result;
    
    /* Get cycle counter */
    access_counter(&ncyc_hi, &ncyc_lo);
    
    /* Do double precision subtraction */
    lo = ncyc_lo - cyc_lo;
    borrow = lo > ncyc_lo;
    hi = ncyc_hi - cyc_hi - borrow;
    result = (double) hi * (1 << 30) * 4 + lo;
    if (result < 0)
    {
        fprintf(stderr, "Error: counter returns neg value: %.0f\n", result);
    }
    return result;
}

//enum AccionEspera{
//    SEGUIR_COMPROBANDO,
//    ESPERAR,
//    AVANZAR
//};

int *nivel = NULL;
int *ultimo_en_llegar = NULL;

uint64_t suma = 0;
int M, T;

bool existeAlguienConMayorPrioridad(uintptr_t self, int l)
{
    for (int k = 0; k < T; k++)
    {
        if (k != self && nivel[k] >= l)
        {
            return true;
        }
    }
    
    return false;
}

void esperarTurnoRegionCritica(uintptr_t self)
{
    for (int l = 0; l < T - 1; l++)
    {
        nivel[self] = l;
        ultimo_en_llegar[l] = self;
        
        atomic_thread_fence(memory_order_seq_cst);
        while (ultimo_en_llegar[l] == self && existeAlguienConMayorPrioridad(self, l))
        {
            sched_yield();
        }
    }
}


void regionCritica(int j)
{
    suma = suma + j;
}

void regionNoCritica()
{
}

void cederTurnoRegionCritica(uintptr_t self)
{
    nivel[self] = -1;
}

void *sum(void *philo)
{
    uintptr_t hilo = (uintptr_t) philo;
    
    for (int j = hilo; j <= M; j += T)
    {
        esperarTurnoRegionCritica(hilo);
        regionCritica(j);
        cederTurnoRegionCritica(hilo);
        regionNoCritica();
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Error: Faltan argumentos\n");
        return (-1);
    }
    
    // M
    M = atoi(argv[1]);
    T = atoi(argv[2]);
    
    nivel = (int *) malloc(T * sizeof(int));
    ultimo_en_llegar = (int *) malloc((T - 1) * sizeof(int));
    
    while (true)
    {
        for (int i = 0; i < T; i++)
        {
            nivel[i] = -1;
        }
        
        for (int i = 0; i < T - 1; i++)
        {
            ultimo_en_llegar[i] = -1;
        }
        
        suma = 0;
        
        pthread_t hilos[T];
        
        start_counter();
        
        for (uintptr_t indice_creacionHilos = 0; indice_creacionHilos < T; indice_creacionHilos++)
        {
            pthread_create(&hilos[indice_creacionHilos], NULL, &sum, (void *) indice_creacionHilos);
        }
        
        for (int indice_destruccionHilos = 0; indice_destruccionHilos < T; indice_destruccionHilos++)
        {
            pthread_join(hilos[indice_destruccionHilos], NULL);
        }
        
        double d_ciclos = get_counter();
        
        uint64_t suma_esperada = ((uint64_t) M * (uint64_t) (M + 1)) / 2L;
        
        fprintf(stdout, "%d;%d;%.0lf;[%s];%lu;%lu\n", M, T, d_ciclos, ((suma - suma_esperada) == 0) ? "OK" : "Error", suma, suma_esperada);
    }
    
    free(nivel);
    free(ultimo_en_llegar);
    
    return (0);
}

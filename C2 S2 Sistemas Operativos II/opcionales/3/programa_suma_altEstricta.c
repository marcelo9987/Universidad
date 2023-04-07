//
// Created by Marcelo on 03/03/2023.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <unistd.h>

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

//double mhz(int verbose, int sleeptime)
//{
//    double rate;
//
//    start_counter();
//    sleep(sleeptime);
//    rate = get_counter() / (1e6 * sleeptime);
//    if (verbose)
//    {
//        printf("\n Processor clock rate = %.1f MHz\n", rate);
//    }
//    return rate;
//}


int turno = 0;
double suma = 0;
int M, T;

void esperarTurnoRegionCritica(uintptr_t self)
{
    while (turno != self)
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
    turno++;
    if (turno >= T)
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
    // M
    M = atoi(argv[1]);
    T = atoi(argv[2]);
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
    
    long suma_esperada = ((long) M * (long) (M + 1)) / 2L;
    
    fprintf(stdout, "%d;%d;%.0lf;[%s]\n", M, T, d_ciclos, ((suma - suma_esperada) == 0) ? "OK" : "Error");
    
//    fprintf(stdout, "%d;%d,%ld;%lf,[%s]\n", M, T, suma_esperada, suma, ((suma - suma_esperada) == 0) ? "OK" : "Error");
    return (0);
}

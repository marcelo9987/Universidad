#include <stdio.h>
#include <stdlib.h>
#include <pmmintrin.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

//getconf -a --> comando utilizado para saber los tamaños de las caches

#define DEBUG 0

#define kNumBytesDeCadaLineaCache 64

// Configuración para el Finisterrae III:
//#define S1 (49152/kNumBytesDeCadaLineaCache)
//#define S2 (1310720/kNumBytesDeCadaLineaCache)

// Configuración para ubuntu del portátil de Marcelo:
//#define S1 (32768/kNumBytesDeCadaLineaCache)
//#define S2 (262144/kNumBytesDeCadaLineaCache)



#define kTotalRepeticiones 10

/* Initialize the cycle counter */


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

double mhz(int verbose, int sleeptime)
{
    double rate;
    
    start_counter();
    sleep(sleeptime);
    rate = get_counter() / (1e6 * sleeptime);
    if (verbose)
    {
        printf("\n Processor clock rate = %.1f MHz\n", rate);
    }
    return rate;
}


/**
 * @brief Calcula el valor de R
 * @param D Separación entre lecturas
 * @return R: Numero de iteraciones
 */
int calcular_R(int D, int L)
{
    
    int i_bytesSeparacionLecturas = D * sizeof(double);
    
    if (i_bytesSeparacionLecturas < kNumBytesDeCadaLineaCache)
    {
        int R = ceil((sizeof(double) * (L - 1)) / D) + 1;
        return R;
    } else
    {
        return L;
    }
}

/**
 * @brief Genera un número aleatorio en el intervalo [d_min, d_max).
 * @param d_min El valor mínimo del intervalo.
 * @param d_max El valor máximo del intervalo.
 * @return Un número aleatorio en el intervalo [d_min, d_max).
 */

double generarNumeroAleatorio(double d_min, double d_max)
{
    double rango = (d_max - d_min);
    double div = RAND_MAX / rango;
    int aleatorio;
    
    do
    {
        //Genero un número aleatorio entre 0 y RAND_MAX
        aleatorio = rand();
    } while (aleatorio == RAND_MAX); //Así evito dar el valor máximo (Se ha pedido intervalo abierto por la derecha)
    
    double d_numero = d_min + (aleatorio / div);
    if (rand() >= RAND_MAX / 2)
    {
        return d_numero;
    } else
    {
        return -d_numero;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stdout, "[error]: número de argumentos incorrecto");
        exit(-1);
    }
    
    /*
     * 0.- Inicialización
     */
    
    /*
     * Repetir kTotalRepeticiones veces la operación de reducción y guardar el resultado en S[]
     */
    double S[kTotalRepeticiones];
    
    
    int D = atoi(argv[1]); //distancia entre accesos consecutivos
    
    int L = atoi(argv[2]); //Numero de lineas de cache a acceder
    
    int R = calcular_R(D, L);
    
    srand(time(NULL));
    
    
    /*
    * 1.- RESERVAR MEMORIA DINÁMICA PARA EL VECTOR A[]
    */
    
    double *A = (double *) _mm_malloc((R - 1) * D * sizeof(double), kNumBytesDeCadaLineaCache);
    
//    int *ind = (int *) _mm_malloc(R * sizeof(int), kNumBytesDeCadaLineaCache); //Reservamos memoria para el vector ind[]
//
//    for (int i = 0; i < R; ++i)
//    {
//        ind[i] = i * D;
//    }
    
    
    /*
     * 2.- Fase de Calentamiento
     */
    
    //Recorremos A y le asignamos valores aleatorios
    for (int i = 0, despl = 0; i < R; ++i, despl += D)
    {
        A[despl] = generarNumeroAleatorio(1, 2); //Generamos un número aleatorio en el intervalo [1,2)
    }
    
    
    /*
     * 3.- Medida de tiempos
     */
    
    //Inicializamos el contador de ciclos
    start_counter();
    
    //Repetir kTotalRepeticiones veces
    for (int repeticion = 0; repeticion < kTotalRepeticiones; ++repeticion)
    {
        
        //Sumamos los valores de A y los guardamos en S, hay que ir imprimiendo S
        for (int i = 0, despl = 0; i < R; ++i, despl += D)
        {
            S[repeticion] = S[repeticion] + A[despl];
        }
    }
    
    double d_ciclos = get_counter();
    int i_numAccesosMemoria = 3 * R * kTotalRepeticiones; //4 accesos por cada iteración del bucle externo
    double d_ciclosPorAcceso = d_ciclos / i_numAccesosMemoria; //ciclos medios por acceso a memoria
    
    #if DEBUG
    fprintf(stdout, "D: %d, L: %d, R: %d, ciclos: %.0f, accesos: %d, ciclos/acc: %f\n", D, L, R, d_ciclos, i_numAccesosMemoria, d_ciclosPorAcceso);
    #elif !DEBUG
    fprintf(stdout, "%d, %d, %d, %.0f, %d, %f\n", D, L, R, d_ciclos, i_numAccesosMemoria, d_ciclosPorAcceso);
    #endif
    
    
    /*
     * 4.- Imprimir resultados
     */
    
    
    
    for (int repeticion = 0; repeticion < kTotalRepeticiones; ++repeticion)
    {
        //Imprimimos S[]
        fprintf(stderr, "El valor de S en la repeticion %d es %f\n", repeticion, S[repeticion]);
    }
    
    
    /*
     * 5.- Liberar memoria
     */
//    free(nombreFichero);
//    fclose(fichero);
    
    _mm_free(A);
//    _mm_free(ind);
    
    
}







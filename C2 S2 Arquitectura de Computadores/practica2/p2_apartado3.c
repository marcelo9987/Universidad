#include <stdio.h>
#include <mm_malloc.h>
#include <immintrin.h>
//#include <memory.h>
#include <unistd.h>


#define KByteslineaCache 64

#define kMaxAleatorio 100

/************************************/

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

/************************************/

void desordenar(int *ind, int N)
{
    int valor_a_intercambiar;
    int valor_temporal;
    for (int i = 0; i < N; ++i)
    {
        valor_a_intercambiar = rand() % N;
        valor_temporal = ind[i];
        ind[i] = ind[valor_a_intercambiar];
        ind[valor_a_intercambiar] = valor_temporal;
    }
}

void aleatorioVector(double *pd_array, int cuantos, int rellenarConCerosHasta)
{
    for (int i = 0; i < cuantos; ++i)
    {
        pd_array[i] = rand() % kMaxAleatorio;
    }
    for (int i = cuantos; i < rellenarConCerosHasta; ++i)
    {
        pd_array[i] = 0;
    }
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error en el número de argumentos\n");
        return 1;
    }

    srand(1);

    int N = atoi(argv[1]);

    int N_multiplo8 = (N + 7) / 8 * 8;



    // ******************************************************
    // Vector c [8]
    double *c = (double *) _mm_malloc(8 * sizeof(double), KByteslineaCache);
    aleatorioVector(c, 8, 8);


    // ******************************************************
    // Matriz A [N][8]
    double **A = (double **) _mm_malloc(N * sizeof(double *), KByteslineaCache);

    for (int i = 0; i < N; ++i)
    {
        A[i] = (double *) _mm_malloc(8 * sizeof(double), KByteslineaCache);
        aleatorioVector(A[i], 8, 8);
    }

    // ******************************************************
    // Matriz B [8][N_multiplo8]
    // La matriz que nos interesa es realmente solo de tamaño 8xN, pero tenemos que "redondear" hasta 8xN_multiplo8

    double **B = (double **) _mm_malloc(8 * sizeof(double *), KByteslineaCache);

    for (int k = 0; k < 8; ++k)
    {
        B[k] = (double *) _mm_malloc(N_multiplo8 * sizeof(double), KByteslineaCache);
        aleatorioVector(B[k], N, N_multiplo8);
    }

    // ******************************************************
    // Matriz D [N][N_multiplo8]
    // La matriz que nos interesa es realmente solo de tamaño NxN, pero tenermos que "redondear" hasta NxN_multiplo8

    double **D = (double **) _mm_malloc(N * sizeof(double *), KByteslineaCache);

    for (int i = 0; i < N; ++i)
    {
        D[i] = (double *) _mm_malloc(N_multiplo8 * sizeof(double), KByteslineaCache);
    }

    // ******************************************************
    // Vector ind[N]
    //creo los índices de la variable ind
    int *ind = (int *) _mm_malloc((N * sizeof(int)), KByteslineaCache);
    for (int i = 0; i < N; ++i)
    {
        ind[i] = i;
    }
    //Y los desordeno
    desordenar(ind, N);

    // ******************************************************
    // +++ Inicio el contador
#ifdef MEDIR_CICLOS
    start_counter();
#endif

    // Matriz B_c [8][N_multiplo8]
    // Va a contener el resultado de restar a cada columna de B el vector c
    double **B_c = (double **) _mm_malloc(8 * sizeof(double *), KByteslineaCache);

    // Resto previamente B-c y lo voy guardando en una matriz auxiliar para usarlo luego
    for (int k = 0; k < 8; ++k)
    {
        //Usando punteros intermedios, me ahorro accesos "de doble salto" a memoria.
        register double *pB = B[k];

        register double *pB_c = (double *) _mm_malloc(N_multiplo8 * sizeof(double), KByteslineaCache);
        B_c[k] = pB_c;

        // --

        __m512d vector_8d_c_k = _mm512_set1_pd(c[k]);

        for (int j = 0; j < N; j += 8)
        {
            __m512d vector_8d_B = _mm512_load_pd(&pB[j]);

            __m512d vector_8d_resta = _mm512_sub_pd(vector_8d_B, vector_8d_c_k);

            _mm512_store_pd(&pB_c[j], vector_8d_resta);
        }

    }

    __m512d vector_8d_factor2 = _mm512_set1_pd(2.0);

    // Bucle de la operación principal
    for (int i = 0; i < N; ++i)
    {
        __m512d vector_8d_A = _mm512_load_pd(&A[i][0]);

        __m512d vector_8d_Ax2 = _mm512_mul_pd(vector_8d_A, vector_8d_factor2);

        //Usando punteros intermedios, me ahorro accesos "de doble salto" a memoria.
        register double *pD = D[i];

        for (int j = 0; j < N; j += 8)
        {
            __m512d vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[0]);
            __m512d vector_8d_B_c_k = _mm512_load_pd(&B_c[0][j]);
            __m512d vector_8d_D = _mm512_mul_pd(vector_8d_Ax2_k, vector_8d_B_c_k);

            vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[1]);
            vector_8d_B_c_k = _mm512_load_pd(&B_c[1][j]);
            vector_8d_D = _mm512_fmadd_pd(vector_8d_Ax2_k, vector_8d_B_c_k, vector_8d_D);

            vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[2]);
            vector_8d_B_c_k = _mm512_load_pd(&B_c[2][j]);
            vector_8d_D = _mm512_fmadd_pd(vector_8d_Ax2_k, vector_8d_B_c_k, vector_8d_D);

            vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[3]);
            vector_8d_B_c_k = _mm512_load_pd(&B_c[3][j]);
            vector_8d_D = _mm512_fmadd_pd(vector_8d_Ax2_k, vector_8d_B_c_k, vector_8d_D);

            vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[4]);
            vector_8d_B_c_k = _mm512_load_pd(&B_c[4][j]);
            vector_8d_D = _mm512_fmadd_pd(vector_8d_Ax2_k, vector_8d_B_c_k, vector_8d_D);

            vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[5]);
            vector_8d_B_c_k = _mm512_load_pd(&B_c[5][j]);
            vector_8d_D = _mm512_fmadd_pd(vector_8d_Ax2_k, vector_8d_B_c_k, vector_8d_D);

            vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[6]);
            vector_8d_B_c_k = _mm512_load_pd(&B_c[6][j]);
            vector_8d_D = _mm512_fmadd_pd(vector_8d_Ax2_k, vector_8d_B_c_k, vector_8d_D);

            vector_8d_Ax2_k = _mm512_set1_pd(vector_8d_Ax2[7]);
            vector_8d_B_c_k = _mm512_load_pd(&B_c[7][j]);
            vector_8d_D = _mm512_fmadd_pd(vector_8d_Ax2_k, vector_8d_B_c_k, vector_8d_D);

            // --

            // Guardamos 8 resultados de una sola vez.
            // No habrá hecho falta ni siquiera inicializarlo al principio :)
            _mm512_store_pd(&pD[j], vector_8d_D);

        }

    }

    // Suma de los elementos, accedidos de forma desordenada gracias al vector ind

    double f = 0;

    for (int i = 0; i < N; ++i)
    {
        f += D[ind[i]][ind[i]];
    }

    f /= 2;


    for (int i = 0; i < 8; ++i)
    {
        _mm_free(B_c[i]);
    }
    _mm_free(B_c);

    // ******************************************************
    // Fin del contador
#ifdef MEDIR_CICLOS
    double ciclos = get_counter();
    fprintf(stdout, "%f; %f\n", f, ciclos);
#else
    fprintf(stdout, "f: %f\n", f);
#endif


    // ******************************************************
    // Liberación de memoria

    for (int i = 0; i < N; ++i)
    {
        _mm_free(A[i]);
    }
    _mm_free(A);

    for (int i = 0; i < 8; ++i)
    {
        _mm_free(B[i]);
    }
    _mm_free(B);

    _mm_free(c);

    for (int i = 0; i < N; ++i)
    {
        _mm_free(D[i]);
    }
    _mm_free(D);

    _mm_free(ind);

    return EXIT_SUCCESS;
}

#include <stdio.h>
#include <mm_malloc.h>
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

void aleatorioVector(double *pd_array, int cuantos)
{
    for (int i = 0; i < cuantos; ++i)
    {
        pd_array[i] = rand() % kMaxAleatorio;
    }
}

void aleatorioMatriz(double **matriz, int cuantos)
{
    for (int i = 0; i < cuantos; ++i)
    {
        matriz[i][0] = rand() % kMaxAleatorio;
        matriz[i][1] = rand() % kMaxAleatorio;
        matriz[i][2] = rand() % kMaxAleatorio;
        matriz[i][3] = rand() % kMaxAleatorio;
        matriz[i][4] = rand() % kMaxAleatorio;
        matriz[i][5] = rand() % kMaxAleatorio;
        matriz[i][6] = rand() % kMaxAleatorio;
        matriz[i][7] = rand() % kMaxAleatorio;
    }
}

void aleatorioTraspuesta(double **matrizTraspuesta, int cuantos)
{

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < cuantos; ++j)
        {
            matrizTraspuesta[j][i] = rand() % kMaxAleatorio;
        }
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


    // ******************************************************
    // Vector c [8]
    double *c = (double *) _mm_malloc(8 * sizeof(double), KByteslineaCache);
    aleatorioVector(c, 8);


    // ******************************************************
    // Matriz A [N][8]
    double **A = (double **) _mm_malloc(N * sizeof(double *), KByteslineaCache);
    for (int i = 0; i < N; ++i)
    {
        A[i] = (double *) _mm_malloc(8 * sizeof(double), KByteslineaCache);
    }

    aleatorioMatriz(A, N);

    // ******************************************************
    // Matriz B_traspuesta [N][8]
    double **B_traspuesta = (double **) _mm_malloc(N * sizeof(double *), KByteslineaCache);
    for (int i = 0; i < N; ++i)
    {
        B_traspuesta[i] = (double *) _mm_malloc(8 * sizeof(double), KByteslineaCache);
    }

    aleatorioTraspuesta(B_traspuesta, N);

    // ******************************************************
    // Matriz D [N][N]
    double **D = (double **) _mm_malloc(N * sizeof(double *), KByteslineaCache);

    for (int i = 0; i < N; ++i)
    {
        D[i] = (double *) _mm_malloc(N * sizeof(double), KByteslineaCache);
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

    // Bucle de la operación principal
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {

            //Desenrollo el bucle de k

            register double r_d_valorSuma = A[i][0] * (B_traspuesta[j][0] - c[0]);
            r_d_valorSuma += A[i][1] * (B_traspuesta[j][1] - c[1]);
            r_d_valorSuma += A[i][2] * (B_traspuesta[j][2] - c[2]);
            r_d_valorSuma += A[i][3] * (B_traspuesta[j][3] - c[3]);
            r_d_valorSuma += A[i][4] * (B_traspuesta[j][4] - c[4]);
            r_d_valorSuma += A[i][5] * (B_traspuesta[j][5] - c[5]);
            r_d_valorSuma += A[i][6] * (B_traspuesta[j][6] - c[6]);
            r_d_valorSuma += A[i][7] * (B_traspuesta[j][7] - c[7]);

            // Guardamos el dato en D sin necesidad de haber inicializado previamente la matriz
            D[i][j] = 2 * r_d_valorSuma;
        }
    }


    // Suma de los elementos, accedidos de forma desordenada gracias al vector ind

    double f = 0;

    for (int i = 0; i < N; ++i)
    {
        f += D[ind[i]][ind[i]];
    }

    f /= 2;

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

    for (int i = 0; i < N; ++i)
    {
        _mm_free(B_traspuesta[i]);
    }
    _mm_free(B_traspuesta);

    _mm_free(c);

    for (int i = 0; i < N; ++i)
    {
        _mm_free(D[i]);
    }
    _mm_free(D);

    _mm_free(ind);

    return EXIT_SUCCESS;
}

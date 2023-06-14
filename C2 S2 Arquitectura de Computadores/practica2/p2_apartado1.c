#include <stdio.h>
#include <mm_malloc.h>
#include <unistd.h>

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

#ifdef INFO_DEBUG

void imprime_array(const double *pd_array, int cuantos, char *mensaje)
{
    printf("INFO %s", mensaje);
    
    for (int i = 0; i < cuantos; ++i)
    {
        printf("%6d", (int) pd_array[i]);
    }
    printf("\n");
}

#else

#define imprime_array(pd_array, cuantos, mensaje) {}

#endif // DEBUG

/************************************/

void desordenar(int *ind, int N)
{
    int valor_a_intercambiar;
    int valor_temporal;
    for (int i = 0; i < N; i++)
    {
        valor_a_intercambiar = rand() % N;
        valor_temporal = ind[i];
        ind[i] = ind[valor_a_intercambiar];
        ind[valor_a_intercambiar] = valor_temporal;
    }
}

void aleatorioVector(double *pd_array, int cuantos)
{
    for (int i = 0; i < cuantos; i++)
    {
        pd_array[i] = rand() % kMaxAleatorio;
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
    double *c = (double *) malloc(8 * sizeof(double));
    aleatorioVector(c, 8);


    // ******************************************************
    // Matriz A [N][8]

    double **A = (double **) malloc(N * sizeof(double *));

    for (int i = 0; i < N; i++)
    {
        A[i] = (double *) malloc(8 * sizeof(double));
        aleatorioVector(A[i], 8);
    }


    // ******************************************************
    // Matriz B [8][N]

    double **B = (double **) malloc(8 * sizeof(double *));

    for (int i = 0; i < 8; i++)
    {
        B[i] = (double *) malloc(N * sizeof(double));
        aleatorioVector(B[i], N);
    }

    // ******************************************************
    // Matriz D [N][N]

    double **D = (double **) malloc(N * sizeof(double *));

    for (int i = 0; i < N; i++)
    {
        D[i] = (double *) malloc(N * sizeof(double));
    }

    // ******************************************************
    // Vector ind[N]
    //creo los índices de la variable ind
    int *ind = (int *) malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i)
    {
        ind[i] = i;
    }
    //Y los desordeno
    desordenar(ind, N);

    // ******************************************************
    // Vector e[N]
    double *e = malloc(N * sizeof(double));

    // ******************************************************
    // +++ Inicio el contador
#ifdef MEDIR_CICLOS
    start_counter();
#endif

    //Inicialización de todas las componentes de la matriz D a cero:
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            D[i][j] = 0;
        }

#ifdef INFO_DEBUG
        imprime_array(D[i], N, "D[i]: ");
#endif // INFO_DEBUG
    }

    for (int i = 0; i < N; i++)
    {

#ifdef INFO_DEBUG
        printf("INFO>>> i=%4d\n", i);
        imprime_array(A[i], 8, "pA: ");
#endif // INFO_DEBUG

        // Bucle de la operación principal
        for (int j = 0; j < N; j++)
        {

            for (int k = 0; k < 8; k++)
            {

#ifdef INFO_DEBUG
                imprime_array(B[k], 1, "pB: ");
#endif // INFO_DEBUG

                D[i][j] += 2 * A[i][k] * (B[k][j] - c[k]);

#ifdef INFO_DEBUG
                printf(">>> D[%d][%d] = %f\n", i, j, D[i][j]);
#endif // INFO_DEBUG
            }

        }

#ifdef INFO_DEBUG
        imprime_array(D[i], 8, ">>> D[i]: ");
#endif // INFO_DEBUG

    }

    // Suma de los elementos, accedidos de forma desordenada gracias al vector ind

    double f = 0;

    for (int i = 0; i < N; i++)
    {
        e[i] = D[ind[i]][ind[i]] / 2;
        f += e[i];
    }


    // ******************************************************
    // Fin del contador
#ifdef MEDIR_CICLOS
    double ciclos = get_counter();
    fprintf(stdout, "%f ; %f\n", f, ciclos);
#else
    fprintf(stdout, "f: %f\n", f);
#endif


    // ******************************************************
    // Liberación de memoria

    for (int i = 0; i < N; i++)
    {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < 8; i++)
    {
        free(B[i]);
    }
    free(B);

    free(c);

    for (int i = 0; i < N; i++)
    {
        free(D[i]);
    }
    free(D);

    free(ind);

    free(e);

    return EXIT_SUCCESS;
}

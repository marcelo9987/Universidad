#include <mmintrin.h>

/*
 Entradas:
a[N][8], b[8][N], c[8]: matrices y vector que almacenan valores aleatorios
de tipo double.
ind[N]: vector desordenado aleatoriamente que contiene índices de
fila/columna sin que se repitan.
Salida:
f: variable de salida tipo double.
Computación:
d[N][N]=0; // inicialización de todas las componentes de la matriz d a cero;
 for (i=0; i<N; i++) {
 for(j=0; j<N; j++) {
for (k=0; k<8; k++) {
 d[i][j] += 2 * a[i][k] * (b[k][j]- c[k]);
}
 }
f=0;
for (i=0; i<N; i++) {
 e[i]= d[ind[i]][ind[i]]/2;
 f+=e[i];}
Imprimir el valor de f.

 */


#include <stdio.h>
#include <mm_malloc.h>

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

void aleatorioVector(double *a, int N)
{
    
    for (int i = 0; i < N; i++)
    {
        a[i] = rand() % kMaxAleatorio;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Error en el número de argumentos\n");
        return 1;
    }

    /**
     * Tomamos el primer argumento que se pasa por línea de comandos como el valor para N
     */
    int N = atoi(argv[1]);

    /**
     * Reservamos memoria para la matriz A
     */
    double **A = (double **) malloc(N * sizeof(double *));
    for (int i = 0; i < N; i++)
    {
        A[i] = (double *) malloc(8 * sizeof(double));
    }
    
    for (int i = 0; i < N; i++)
    {
        aleatorioVector(A[i], 8);
    }

    /**
     * Reservamos memoria para la matriz B
     */
    double **B = (double **) malloc(8 * sizeof(double *));
    
    for (int i = 0; i < 8; i++)
    {
        B[i] = (double *) malloc(N * sizeof(double));
    }
    
    for (int i = 0; i < 8; i++)
    {
        aleatorioVector(B[i], N);
    }

    /**
     * Reservamos memoria para el vector c
     */
    double *c = (double *) malloc(8 * sizeof(double));
    aleatorioVector(c, 8);

    /**
     * Reservamos memoria para la matriz d
     */
    double **d = (double **) malloc(N * sizeof(double *));
    
    for (int i = 0; i < N; i++)
    {
        d[i] = (double *) malloc(N * sizeof(double));
    }
    
    
    //incialización de todas las componentes de la matriz d a cero;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            d[i][j] = 0;
        }
    }

    //operación especificada en el pseudocódigo
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                d[i][j] += 2 * A[i][k] * (B[k][j] - c[k]);
            }
        }
    }
    
    int *ind = (int *) malloc(N * sizeof(int));
    
    double *e = malloc(N * sizeof(double));
    
    double f = 0;

    //inicializamos los valores del vector e[] a 0
    for (int i = 0; i < N; i++)
    {
        e[i] = 0;
    }

    //desordenamos los valores
    desordenar(ind, N);
    
    f = 0;
    //Realizamos la operación especificada para f en el pseudocódigo.
    for (int i = 0; i < N; i++)
    {
        e[i] = d[ind[i]][ind[i]] / 2;
        f += e[i];
    }
    
    fprintf(stdout, "f: %f\n", f);
    
    //liberacion de memoria
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
        free(d[i]);
    }
    free(d);
    
    free(ind);
    
    free(e);
    
    return EXIT_SUCCESS;
}

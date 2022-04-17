#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matriz.h"

#define SUMA 0
#define MULTP 1

int main(int argc, char* argv[])
{
    if (argc == 1) //si solo existe argv[0], que es el nombre del programa
    {
        fprintf(stderr, "FATAL: No se han pasado argumentos.\n");
        exit(-0); // Sale del programa de forma segura. También indica un poco las intenciones del desarrollador.
    } else if (argc != 4) // si solo hay dos argumentos
    {
        fprintf(stderr, "FATAL: No se han comunicado los argumentos requeridos para la ejecución del programa.\n");
        exit(255);
    }
    
    long minimo;//arg 1, valor mínimo de las matrices
    if (sscanf(argv[ 1 ], "%li", &minimo) != 1)
    {
        fprintf(stderr, "FATAL: Argumento 1 no numérico.\n");
        exit(254);
    }
    long maximo; //arg 2, valor máximo de las matrices
    if (sscanf(argv[ 2 ], "%li", &maximo) != 1)
    {
        fprintf(stderr, "FATAL: Argumento 2 no numérico.\n");
        exit(253);
    }
    long paso;//arg 3, paso a aplicar entre cálculo y cálculo
    if (sscanf(argv[ 3 ], "%li", &paso) != 1)
    {
        fprintf(stderr, "FATAL: Argumento 3 no numérico.\n");
        exit(252);
    }
    
    if (maximo < minimo || maximo == 0 || paso <= 0)
    { // Si el mínimo es mayor al máximo o el máximo está declarado a 0
        fprintf(stderr, "Los parámetros establecidos son incorrectos.\n");
        exit(251);
    }
    
    FILE* resultadosSum = NULL;    //Archivo en el que se guardan los tiempos de las sumas
    FILE* resultadosMultMat = NULL; //Archivo en el que se guardan los tiempos de las multiplicaciones
    
    //assert(resultadosSum == NULL && resultadosMultMat == NULL); //Los ficheros NO existen
    
    resultadosSum = fopen("tiemposSumaMatrices.txt", "wt+");
    
    //assert(resultadosSum != NULL && resultadosMultMat != NULL); //Los ficheros EXISTEN
    if (resultadosSum == NULL)
    {
        perror("ERROR, apertura de archivos incorrecta... Finalizando programa.\n");
        exit(250);
    }
    resultadosMultMat = fopen("tiemposMultMatrices.txt", "wt+");
    if (resultadosMultMat == NULL)
    {
        perror("ERROR, apertura de archivos incorrecta... Finalizando programa.\n");
        exit(249);
    }
    
    clock_t inicio[] = {0, 0};
    clock_t fin[] = {0, 0};
    
    srand(time(NULL));  //creo la semilla de la función rand() en 0 del tiempo UNIX
    
    for (long tamanho = minimo; tamanho <= maximo; tamanho += paso)
    {
        if(tamanho==0)
        {
            continue;
        }
        
        fprintf(stdout, "Iniciando prueba para n = %li\n", tamanho);
        Matriz A;
        Matriz B;
        Matriz C;
        
        iniciarMatriz(&A, tamanho, tamanho);
        iniciarMatriz(&B, tamanho, tamanho);
        iniciarMatriz(&C, tamanho, tamanho);
        
        asignarValoresAleatoriosMatriz(&A);
        asignarValoresAleatoriosMatriz(&B);
        fprintf(stdout, "Iniciando suma para n = %li\n", tamanho);
    
        inicio[ SUMA ] = clock();
        sumaMatrices(&C, &A, &B);
        fin[ SUMA ] = clock();
        //       fprintf(stdout, "He sumado\n");
        //ipmt(A);
        //ipmt(B);
        //ipmt(C);
        fprintf(stdout, "Iniciando multiplicación para n = %li\n", tamanho);
    
        inicio[ MULTP ] = clock();
        multiplicaMatrices(&C, &A, &B);
        fin[ MULTP ] = clock();
        //ipmt(C);
//        fprintf(stdout, "He multiplicado\n");
        
        destruirMatriz(&A);
        destruirMatriz(&B);
        destruirMatriz(&C);
        
        fprintf(resultadosSum, "%li %lf\n", tamanho, (fin[ SUMA ] - inicio[ SUMA ]) / (double)CLOCKS_PER_SEC);
        fprintf(resultadosMultMat, "%li %lf\n", tamanho, (fin[ MULTP ] - inicio[ MULTP ]) / (double)CLOCKS_PER_SEC);
        //fprintf(resultadosSum, "%li %li %li %li %lf\n", tamanho, fin[ SUMA ], inicio[ SUMA ], CLOCKS_PER_SEC, (fin[ SUMA ] - inicio[ SUMA ]) / (double) CLOCKS_PER_SEC);
        //fprintf(resultadosMultMat, "%li %li %li %li %lf\n", tamanho, fin[ MULTP ], inicio[ MULTP ], CLOCKS_PER_SEC, (fin[ MULTP ] - inicio[ MULTP ]) / (double) CLOCKS_PER_SEC);
    }
    
    fprintf(stdout, "Prueba finalizada con éxito.\n");
    
    fclose(resultadosSum);
    fclose(resultadosMultMat);
    
    return 0;
}
/*
 * Errores críticos:
 * 0: Programa sin argumentos
 * 255: Numero de argumentos incorrecto (más o menos de 4)
 * 254: El argumento 1(mínimo) no es un número o está codificado en un formato no reconocido
 * 253, 252: "" "" 2,3(máximo y paso) "" "" "" "" "" "" "" "" "" "" ""
 * 251: El máximo establecido es mayor al mínimo, el máximo ha sido establecido a 0 o el paso ha sido puesto a 0 o es menor a 0
 * 250: Fallo de apertura del fichero tiemposSumaMatrices o equivalente
 * 249: "" "" "" "" "" resultadosMultMat "" ""
 */

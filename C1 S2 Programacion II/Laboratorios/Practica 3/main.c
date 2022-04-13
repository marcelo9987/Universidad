#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "matrices.h"

int main(int argc, char* argv[])
{
    if(argv[0]==NULL)
    {                    //Hago esta condición para evitar un data leak en las variables de entorno y evitar problemas de seguridad
        fprintf(stderr,"FALLO CRITICO: Argumento 1 a NULL, deteniendo programa para evitar acceso a VARIABLES DE ENTORNO");
        abort(); // Finaliza el programa sin miramientos(aborta el proceso)
    }
    if(argc==1)
    {           //si solo existe argv[0], que es el nombre del programa
        fprintf(stderr,"FATAL: No se han pasado argumentos");
        exit(455); // Sale del programa de forma segura. También indica un poco las intenciones del desarrollador.
    }else if(argc==2)
    { // si solo hay dos argumentos
        fprintf(stderr,"FATAL: No se han comunicado los argumentos requeridos para la ejecución del programa");
        exit(456);
    }
    
    long minimo =  atol(argv[1]); //arg 1, valor mínimo de las matrices
    long maximo = atol(argv[2]); //arg 2, valor máximo de las matrices
    long paso  = atol(argv[3]); //arg 3, paso a aplicar entre cálculo y cálculo
    
    if (maximo == minimo || maximo < minimo || maximo == 0)
    { // Si el mínimo es mayor al máximo o el máximo está declarado a 0
        fprintf(stderr,"Los parámetros establecidos son incorrectos");
        exit(-1);
    }
    
    FILE* resultadosMultMat = NULL; //Archivo en el que se guardan los tiempos de las multiplicaciones
    FILE* resultadosSum = NULL;    //Archivo en el que se guardan los tiempos de las sumas
    assert(resultadosSum ==NULL && resultadosMultMat == NULL); //Los ficheros NO existen
    
    resultadosMultMat = fopen("tiemposMultMatrices.txt", "wt+");
    resultadosSum = fopen("tiemposSumaMatrices.txt","w33t+");
    assert(resultadosSum !=NULL && resultadosMultMat!=NULL); //Los ficheros EXISTEN
    if(!(resultadosSum !=NULL && resultadosMultMat!=NULL))
    {
        fprintf(stderr,"ERROR, apertura de archivos incorrecta... Finalizando programa.");
        abort();//finalizo bruscamente para evitar escrituras indeseadas. Código de error: [Cerr] = 3
    }
    
    clock_t inicio[] = {0,0};
    clock_t fin[] = {0,0};
    
    srand(time(NULL));  //creo la semilla de la función rand() en 0 del tiempo UNIX

    for(long tamanho = minimo;tamanho<maximo;tamanho+=paso)
    {
       
       matriz m1;
       matriz m2;
       
       crearMatriz(&m1,tamanho,tamanho);
       crearMatriz(&m2,tamanho,tamanho);
       
       inicio[0]=clock();
       matriz m3 =sumaMatrices(m1,m2);
       fprintf(stdout,"He sumado\n");
       
       fin[0] = clock();
       
       inicio[1]=clock();
       matriz m4 = multiplicaMatrices(m1,m2);
       fprintf(stdout,"He multiplicado");
       fin[1] = clock();

       fprintf(stdout,"\n Op Nº: %li \n",tamanho);
       destruirMatriz(&m1);
       destruirMatriz(&m2);
       destruirMatriz(&m3);
       destruirMatriz(&m4);
        
        fprintf(resultadosSum,"%li,%li\n",tamanho,((fin[1]-inicio[1])/CLOCKS_PER_SEC));
        fprintf(resultadosMultMat, "%li %li\n", tamanho, ((fin[1] - inicio[1]) / CLOCKS_PER_SEC));
    }
    fprintf(stdout,"Prueba finalizada con éxito");
    fclose(resultadosSum);
    fclose(resultadosMultMat);
    return 0;
}
//Conclusiones a 08/04/2022: La suma es más rápida; la división es carísima a nivel computacional: ¿mejorar algoritmo?:: .,,.

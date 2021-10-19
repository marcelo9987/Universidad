///////////////////////////////// ZONA DE LIBRERÍAS
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include<windows.h>
#include<stdlib.h>
//////////////////////////////////VARIABLES GLOBALES Y CONSTANTES
//int de=1,de2=2;
//////////////////////////////////FUNCIONES
int pedirtamanosf();//devuelve un numero
int pedirtamanosc();//devuelve un numero
void llenarMatriz(int filas,int columnas,int matriz[filas][columnas]);
void imprimirMatriz(int filas,int columnas,int matriz[filas][columnas]);
//////////////////////////////////ESTRUCTURAS
struct tamanoMatriz
{
    unsigned int filas;
    int columnas;
};
/////////////////////////////////DEFINICIÓN DE FUNCIONES
int pedirtamanosf()
{
    int tamanof;
    wprintf(L"Número de filas de la matriz: ");
    scanf("%i",&tamanof);

    return tamanof;
}
int pedirtamanosc()
{
    int tamanoc;
    wprintf(L"Número de columnas de la matriz: ");
    scanf("%i",&tamanoc);

    return tamanoc;
}
void llenarMatriz(int filas,int columnas, int matriz[filas][columnas])
{
    for(int i =0;i<filas;i++)
    {
        for(int j=0;j<columnas;j++)
        {
            wprintf(L"Introduzca el elemento ");
            printf("%i",i);
            printf("%i",j);
            printf(": ");
            scanf("%i",&matriz[i][j]);
        }
        printf("\n");
    }
}
void imprimirMatriz(int filas,int columnas,int matriz[filas][columnas])
{
    for (int i = 0; i < filas; i++)
    {
                for (int j = 0; j < columnas; j++)
                {
                    printf("   %i", matriz[i][j]);
                }
                printf("\n");
            }
    }

/////////////////////////////////////////////////*******************////////////////////////////////////////////////////
/////////////////////////////////////////////////*******************////////////////////////////////////////////////////
int main()
{
    struct tamanoMatriz m1;
    struct tamanoMatriz m2;
    setlocale(LC_ALL,"Spanish");
    printf("Matriz 1: ");
    printf("\n");
    m1.columnas=pedirtamanosc();
    m1.filas=pedirtamanosf();
    printf("%i", m1.filas);
    printf("%i", m1.columnas);
    printf("\n");
    printf("\n");
    printf("Matriz 2: \n");
    m2.columnas=pedirtamanosc();
    m2.filas=pedirtamanosf();
    int matriz1[m1.filas][m1.columnas];
    int matriz2[m2.filas][m2.columnas];

    //de=m1.filas;
   // de2=m1.columnas;

    llenarMatriz(m1.filas,m1.columnas,matriz1);

    //de=m2.filas;
    //de2=m2.columnas;

    llenarMatriz(m2.filas,m2.columnas,matriz1);
    wprintf(L"\nMatriz 1: ");
    printf("\n");
    imprimirMatriz(m1.filas,m1.columnas,matriz2);
    wprintf(L"\nMatriz 2: ");
    printf("\n");
    imprimirMatriz(m2.filas,m2.filas,matriz2);
    system("pause");
    return 0;
}



#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
int main()
{
    setlocale(LC_ALL,"Spanish");
    float  matriz[4][4],matriz2[4][4],matrizRes[4][4];
    bool men4 = FALSE;
    bool men42=FALSE;

    bool sumrespos=FALSE,mulpos=FALSE;
    int filas, columnas,filas2,columnas2,sel,suma;
    do{
        system("cls");
        wprintf(L"------------------------------------------------MATRIZ 1------------------------------------------------");
        wprintf(L"------------------------------------------------Tamaño------------------------------------------------");
       wprintf(L"\n Introduzca el número de filas: ");
        scanf("%i",&filas);
        wprintf(L"\n Introduzca el número de columnas: ");
        scanf("%i",&columnas);
        if(filas<=4 && columnas<=4)
        {
            men4=TRUE;
        }
    } while(men4==FALSE);//declaración de tamaño de la matriz1
    system("cls");
    wprintf(L"------------------------------------------------MATRIZ 1------------------------------------------------");
    wprintf(L"------------------------------------------------Valores------------------------------------------------");
    for(int i =0;i<filas;i++)
   {
        for (int j = 0; j<columnas;j++)
        {
        printf("\n Valor %i",i);
        printf("%i",j);
        printf(": ");
        scanf("%f",&matriz[i][j]);
        }
   }



    do{
        system("cls");
        wprintf(L"------------------------------------------------MATRIZ 2------------------------------------------------");
        wprintf(L"------------------------------------------------Tamaño------------------------------------------------");
        wprintf(L"\n Introduzca el número de filas: ");
        scanf("%i",&filas2);
        wprintf(L"\n Introduzca el número de columnas: ");
        scanf("%i",&columnas2);
        if(filas2<=4 && columnas2<=4)
        {
            men42=TRUE;
        }
    } while(men42==FALSE);//declaración de tamaño de la matriz1
    system("cls");
    wprintf(L"------------------------------------------------MATRIZ 2------------------------------------------------");
    wprintf(L"------------------------------------------------Valores------------------------------------------------");
    for(int i =0;i<filas2;i++)
    {
        for (int j = 0; j<columnas2;j++)
        {
            printf("\n Valor %i",i);
            printf("%i",j);
            printf(": ");
            scanf("%f",&matriz2[i][j]);
        }
    }
    system("cls");
    if(filas==filas2 && columnas == columnas2)
    {
        sumrespos=TRUE;
    }else
    {
        sumrespos = FALSE;
    }

    if(columnas=filas2)
    {
        mulpos=TRUE;
    }else{
        mulpos=FALSE;
    }
    printf("-------------------------------------------OPERACIONES-------------------------------------------");
    if(sumrespos==true ||  mulpos==true){
        if(sumrespos==TRUE)
        {
            printf("\n           1.SUMA");
            printf("\n           2.RESTA");
        }
        if(mulpos==TRUE)
        {
            wprintf(L"\n            3.MULTIPLICACIóN");

        }
        wprintf(L"\n Selección: ");
        scanf("%i",&sel);
    }else
    {
        printf("MATRICES NO COMPATIBLES");
    }

    //////////////////////////////////SWITCH DE OPERACIONES////////////////////////////////////////////////

    switch (sel) {
        case 1:
            for(int i =0;i<filas;i++)
            {
                for (int j=0; j<columnas;j++)
                {
                    matrizRes[i][j]=matriz[i][j]+matriz2[i][j];
                }
            }


            for (int i = 0; i<filas;i++)
            {
                for (int j = 0; j<columnas;j++)
                {

                    printf("%.2f",matriz[i][j]);
                    printf("  ");
                }
                printf("\n");
            }
            printf("\n + \n");
            for (int i = 0; i<filas2;i++)
            {
                for (int j = 0; j < columnas2; j++)
                {

                    printf("%.2f", matriz2[i][j]);
                    printf("  ");
                }
                printf("\n");
            }

            printf("\n = \n ");

            for (int i = 0; i<filas2;i++)
            {
                for (int j = 0; j < columnas2; j++)
                {

                    printf("%.2f", matrizRes[i][j]);
                    printf("  ");
                }
                printf("\n");
            }
            break;




        case 2:
            for(int i =0;i<filas;i++)
            {
                for (int j=0; j<columnas;j++)
                {
                    matrizRes[i][j]=matriz[i][j]-matriz2[i][j];
                }
            }



            for (int i = 0; i<filas;i++)
            {
                for (int j = 0; j<columnas;j++)
                {

                    printf("%.2f",matriz[i][j]);
                    printf("  ");
                }
                printf("\n");
            }
            printf("\n - \n");
            for (int i = 0; i<filas2;i++)
            {
                for (int j = 0; j < columnas2; j++)
                {

                    printf("%.2f", matriz2[i][j]);
                    printf("  ");
                }
                printf("\n");
            }

            printf("\n = \n ");

            for (int i = 0; i<filas;i++)
            {
                for (int j = 0; j < columnas; j++)
                {

                    printf("%.2f", matrizRes[i][j]);
                    printf("  ");
                }
                printf("\n");
            }
            break;
            ////WIP
        case 3:
            suma =0;
            for(int i =0;i<filas;i++)
            {
                for(int j=0;j<columnas2;j++)
                {
                    suma = 0;
                    for (int k = 0;k<columnas; k++) {
                        suma += matriz[i][k] * matriz2[k][j];
                    }
                    matrizRes[i][j] = suma;
                }

            }
           /////WIP
            for (int i = 0; i<filas;i++)
            {
                for (int j = 0; j<columnas;j++)
                {

                    printf("%.2f",matriz[i][j]);
                    printf("  ");
                }
                printf("\n");
            }
            printf("\n * \n");
            for (int i = 0; i<filas2;i++)
            {
                for (int j = 0; j < columnas2; j++)
                {

                    printf("%.2f", matriz2[i][j]);
                    printf("  ");
                }
                printf("\n");
            }

            printf("\n = \n ");

            for (int i = 0; i<filas;i++)
            {
                for (int j = 0; j < columnas; j++)
                {

                    printf("%.2f", matrizRes[i][j]);
                    printf("  ");
                }
                printf("\n");
            }

           break;
        default:
            break;

    }

//////////////////////////////////////////IMPRESIÓN//////////////////////////////////////////
   /* for (int i = 0; i<filas;i++)
    {
        for (int j = 0; j<columnas;j++)
        {

            printf("%.2f",matriz[i][j]);
            printf("  ");
        }
        printf("\n");
    }

    for (int i = 0; i<filas2;i++)
    {
        for (int j = 0; j < columnas2; j++)
            {

                printf("%.2f", matriz2[i][j]);
                printf("  ");
            }
            printf("\n");
    }
*/

    system("pause");
    return 0;
}

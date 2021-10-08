#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
//DECLARACIÓN DE FUNCIONES Y ESTRUCTURA
struct array {
    float numero[15];
    float ordenado[15];
    float repeticiones[15];
};
float nm(float arrf1[15]);
float np(float arrf2[15]);
void entrada(float arr1[15]);
void asignacionAleatoria(float arr2[15]);
void ordenar(float arrdesord[15],float arrord[15]);
void repeticiones(float a1[15],float reps[15]);
//MAIN
int main()
{
    //DECLARACIÓN DE VARIABLES
    struct array datos;
    int sel;
    //AJUSTE DE FUNCIONES
    srand(time(NULL));
    setlocale(LC_ALL,"Spanish");
    //PROGRAMA PRINCIPAL
    for(int w=0;w<15;w++)
    {
        datos.repeticiones[w]=0;
    }
    do{
    system("cls");
    wprintf(L"Desea introducir la cadena manualmente(1) o que se genere automáticamente(0): ");
    scanf(" %i",&sel);
    }while(sel!=1 && sel!=0);
    if(sel==1)
    {
        entrada(datos.numero);

    }else if(sel==0)
    {
        asignacionAleatoria(datos.numero);
    }
    printf("\n Array original: ");
    for(int i =0;i<15;i++)
    {
        wprintf(L" \n %.2f",datos.numero[i]);
    }

    ordenar(datos.numero,datos.ordenado);
    repeticiones(datos.ordenado,datos.repeticiones);
//IMPRESIÓN DE RESULTADOS
    printf("\n Array ordenado: ");
    for(int i =0;i<15;i++)
    {
        wprintf(L" \n%.2f",datos.ordenado[i]);
    }
    printf("\n Repetciones: ");
    for(int i =0;i<15;i++)
    {
        if (datos.ordenado[i] != datos.ordenado[i-1])
        {
            wprintf(L" \n%.2f", datos.ordenado[i]);
            wprintf(L" Repeticiones: ");
            wprintf(L" %.2f", datos.repeticiones[i]);

        }
    }


    printf("\n");
    wprintf(L" Número más grande: %.2f",nm(datos.ordenado));
    printf("\n");
    wprintf(L" Número más pequeño: %.2f",np(datos.ordenado));
    printf("\n");
    system("pause");
    return 0;
}

//ESPECIFICACIÓN DE FUNCIONES
void entrada(float arr1[])
{
    for(int i =0;i<15;i++)
    {
        wprintf(L"\n Número %i",i);
        printf(": ");
        scanf("%f",&arr1[i]);
    }
}
void asignacionAleatoria(float arr2[15])
{
    for(int i =0;i<15;i++)
    {
        arr2[i]=rand()%100;
    }
}
void ordenar(float arrdesord[15],float arrord[15]) {
    // for(int j;j)
    float e;
    for (int i = 0; i < 15; i++)
    {
        arrord[i] = arrdesord[i];
    }
    for (int v = 0; v < 15; v++)
    {
        for (int h = 0; h < 15; h++)
        {
            if (arrord[h] < arrord[h + 1])
            {
                e = arrord[h];
                arrord[h] = arrord[h + 1];
                arrord[h + 1] = e;
            }
        }
    }
}

float nm(float arrf1[15])//se ha de poner después de ordenar el array, sino no funciona.
{

    float numMay=arrf1[0];
    return numMay;
}


float np(float arrf2[15])//se ha de poner después de ordenar, no funciona si se coloca antes
{
    float numMin;
    numMin=arrf2[14];
    return numMin;
}

void repeticiones(float a1[15],float reps[15])
{
    for(int i=0;i<15;i++)
    {
        for (int j=0;j<15;j++)
        {
            if(a1[i]==a1[j])
            {
                reps[i] +=1;
            }
        }
    }
}
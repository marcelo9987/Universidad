#define LONGITUD 12 //esto puede cambiarse para distintos vectores
#define TAMANOMAXIMO 100 //para el generado aleatorio
#include <stdio.h>
#include <locale.h>
#include<stdbool.h>
#include <windows.h>
#include<stdlib.h>
#include <time.h>
int obtenerMaximo(float vec[]);

int main() {
    int posloc,may,dec;
    float array[LONGITUD];
    srand(time(NULL));
    printf("Desea crear el array o generarlo(1|2): ");
    scanf("%d",&dec);
    switch(dec)
    {
        case 1:
            for(int i=0;i<LONGITUD;i++)
            {
                printf("\n Entrada %i",i);
                printf(": ");
                scanf("%f",&array[i]);
            }
            break;
        case 2:
            for(int i=0;i<LONGITUD;i++)
            {
                array[i]=rand()%TAMANOMAXIMO;
            }
            break;

    }

    printf("\n \n Array desordenado: ");
    for(int i=0;i<LONGITUD;i++)
    {
        printf("%.3f",array[i]);
        printf(" ");
    }

    posloc=obtenerMaximo(array)+1;
    may=array[posloc];

    for(int j=0;j<LONGITUD;j++)//burbuja para depuración de programa
    {
        for(int w=0;w<LONGITUD-1;w++)
        {
            int r=0;
            if(array[w]<array[w+1])
            {
             r= array[w];
             array[w]=array[w+1];
             array[w+1]=r;
            }
        }
    }

    printf("\n \n Array ordenado: ");
    for(int i=0;i<LONGITUD;i++)
    {
        printf("%.3f",array[i]);
        printf(" ");
    }

    printf("\n \n \n Numero mas grande: %d",may);
    printf("\n  Posicion: %d",posloc);
    return 0;
}

int obtenerMaximo(float vec[])
{
    int longi = LONGITUD;
    int mayor=0;
    int pos=0;
    for(int i =0;i<longi;i++)
    {
        if(mayor<vec[i])
        {
            mayor=vec[i];
            pos=i;
        }
    }
    return pos;
}

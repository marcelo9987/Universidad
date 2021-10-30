/*
 * Programador: Marcelo Fort Muñoz
 * Descripción: El ejercicio lee una serie de números y lleva a cabo una serie de operaciones en ellos además de ordenarlos.
 *  Una vez estos son ordenados, el ordenador procede a grabarlos en un fichero.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int max(int a[],int n);//encuentra el número más grande del vector params: a[](vector) n(tamaño del vector)
int min(int b[],int n);//busca el número más pequeño del vector params: b[](vector) n(tamaño del vector)
float med(int c[],int n); //busca la media del vector params: c[](vector) n(tamaño del vector)
void ordenarVector(int* vector,int n);//ordena el vector los parámetros son: vector(es un puntero a un vector) y n(su tamaño)
int main()
{
    int numex[50]={0},i=0,v,maxi,mini;
    float medi;
    setlocale(LC_ALL,"Spanish");
    FILE* ar;
    FILE* or;
    ar = fopen("datos.txt","r");
    or = fopen("datos_ordenados.txt","w");
    if(ar == NULL)
    {
        wprintf(L"Error al leer el archivo \n");
        exit(1);
    }else do
        {
            v = fscanf(ar,"%d",&numex[i]);
            i+=1;
        }while(v>0);

    for(int h =0;h<i-1;h++)
    {
        wprintf(L"%i",numex[h]);
        printf(" || ");
    }
    fclose(ar);
    maxi=max(numex,i-1);
    wprintf(L"\nMáximo: %i",max(numex,i-1));
    mini=min(numex,i-1);
    wprintf(L"\nMínimo: %i",min(numex,i-1));
    medi=med(numex,i-1);
    wprintf(L"\nMedia: %.2f",med(numex,i-1));
    printf("\n");
    ordenarVector(&numex,i-1);
    fwprintf(or,L"Números ordenados: \n");
    for(int h = 0;h<i-1;h++)
    {
       // printf(" %i",numex[h]);
        fprintf(or,"%i",numex[h]);
        if(h!=i-2)
        {
            fprintf(or," -- ");
        }
    }
    fwprintf(or,L"\n Número más grande: \n");
    fprintf(or,"%i",maxi);
    fwprintf(or,L"\n Número más pequeño: \n");
    fprintf(or,"%i",mini);
    fwprintf(or,L"\n Media: \n");
    fprintf(or,"%f",medi);
    fclose(or);
    system("pause");
    return 0;
}
int max(int a[],int n)
{
    int maximo=0;
    for(int i=0;i<n;i++)
    {
        if(maximo<a[i])
        {
            maximo=a[i];
        }
    }
    return maximo;
}

int min(int b[],int n)
{
    int minimo=222;
    for(int i=0;i<n;i++)
    {
        if(minimo>b[i])
        {
            minimo=b[i];
        }
    }
    return minimo;
}

float med(int c[],int n)
{
    float suma=0,media;
    for(int i=0;i<n;i++)
    {
        suma += (float)c[i];
    }
    media=suma/(float)n;
    return media;
}
void ordenarVector(int* vector,int n)
{
    for(int i=0; i<n;i++)
    {
        for(int j = 0;j<n-1;j++)
        {
            if(vector[j]<vector[j+1])
            {
                int rws = vector[j];
                vector[j]=vector[j+1];
                vector[j+1] = rws;
            }
        }
    }
}
/*Programador: marcelo
 * Descripción: Hace una serie de operaciones sobre un archivo llamado numbers.txt
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int max(int a[],int n);
int min(int b[],int n);
float med(int c[],int n);
int main()
{
    int numex[50]={0},i=0,v;
    setlocale(LC_ALL,"Spanish");
    FILE* ar;
    ar = fopen("numbers.txt","r");
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

    wprintf(L"\nMáximo: %i",max(numex,i-1));
    wprintf(L"\nMínimo: %i",min(numex,i-1));
    wprintf(L"\nMedia: %.2f",med(numex,i-1));
    printf("\n");
    system("pause");
    return 0;
}
int max(int a[],int n)//calcula el valor máximo
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

int min(int b[],int n)//calcula el valor mínimo
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

float med(int c[],int n)//calcula la media
{
    float suma=0,media;
    for(int i=0;i<n;i++)
    {
        suma += (float)c[i];
    }
    media=suma/(float)n;
    return media;
}
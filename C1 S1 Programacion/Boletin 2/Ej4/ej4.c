#include <stdio.h>
#include <locale.h>
#include<math.h>
/*
 * Creación a día 06 de octubre de 2021
 * Programador Marcelo Fort Muñoz
 * Descripción: Mejora del EJ 3
 */
int main()
{
    float array[101];
    float solucion = 0;
    setlocale(LC_ALL,"Spanish");
    for (int i=0;i<101;i++)
    {
        array[i]=(1/2) + (1/pow(2,i));
    }
    for (int i=0;i<101;i++)
    {
        solucion += array[i];
    }
    wprintf(L"La solución es : %f",solucion);
}
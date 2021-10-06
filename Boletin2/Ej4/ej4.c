#include <stdio.h>
#include <locale.h>
#include<math.h>

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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
 *  Programador: Marcelo Fort Muñoz
 *  Día de inicio: 06/10/2021
 *  Descripción:
 *  Día de finalización: 06/10/2021
 *
*/
#include <locale.h>
int main() {
    setlocale(LC_ALL,"Spanish");
    float s[101],solucion=0;
    for(int i = 0;i<101;i++)
    {
        s[i]=1/(pow(2,i));
    }
    for(int i = 0;i<101;i++)
    {
        solucion=solucion+s[i];
    }
    wprintf(L"La solución es: %f",solucion);
    printf("\n");
    system("Pause");
    return 0;
}

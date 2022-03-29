#include <stdio.h>
#include<locale.h>
#include <stdlib.h>
/*
 *  Programador: Marcelo Fort Muñoz
 *  Dia de creación: 06/10/2021 14:05
 *  Día de finalización:  06/10/2021 14:22
 * */
int main() {
    int ano;
    //float valor1;
    setlocale(LC_ALL,"Spanish");
    wprintf(L"Introduzca el año: ");
    scanf("%i",&ano);
   // anof=(float)ano;
   //valor1=ano%2;
    if(((ano%4==0)&&(ano%100 != 0)) ||(ano%400==0)){
    wprintf(L"El año %i",ano);
    wprintf(L" es bisiesto \n");
    }else
    {
        wprintf(L"El año %i",ano);
        wprintf(L" no es bisiesto \n");
    }
    system("pause");
    return 0;
}

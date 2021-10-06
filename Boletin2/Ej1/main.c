#include <stdio.h>
#include <stdlib.h>
/*  Programado el día 6/10/2021
 *  Programador: Marcelo Fort Muñoz
 *  El ejercicio consistirá en pedir un input entero y calcular su valor en "y" en base a la función dada.
 * */

int main() {
    float numero,y;
    int a=0;

    do{
        system("cls");
        if(a==1)
        {
            printf("Valor no definido \n");
        }
        printf("introduzca x: ");
        scanf("%f", &numero);
        a=1;
    }while( !( ((numero>=-1)&&(numero<1)) || ((numero>=1)&&(numero<2)) || ((numero>=2)&&(numero<=4)) ) );
    system("cls");
    printf("x= %f",numero);
    printf("\n");
    if((numero>=-1) &&(numero<1))
   {
       y = numero*numero;
       printf("y = %f",y);
   }else if((numero>=1) && (numero<2))
   {
       //printf("%f",numero);
       y= (2 * numero) - 1;
       printf("y = %f",y);
   }else if((numero>=2) && (numero<=4))
   {
       y= -2 * ( (numero - 2.5) * (numero - 2.5) ) + 3.5;
       printf("y = %f",y);
   }
    printf("\n");
    system("pause");
    return EXIT_SUCCESS;
}

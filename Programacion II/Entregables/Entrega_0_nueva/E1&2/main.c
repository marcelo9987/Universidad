#include <stdio.h>
#include <stdlib.h>

















int main(int argc,char** argcv)
{
    int a =-1,b=-1,c=-1;
    printf("Buenas tardes. Digame dos numeros: ");
    scanf("%d %d",&a,&b);
    c=a+b;
    printf("\n%d+%d=%d\n",a,b,c);
    return(EXIT_SUCCESS);
}
/*
 * Valores Antes de:
 *  Linea 22:
 *      a= No existe //aun no han sido declaradas
 *      b= No existe
 *      c= No existe
 *  Linea 23:
 *      a= -1 //han sido asignadas a -1 en su declaración
 *      b= -1
 *      c= -1
*   Linea 25:
 *      a= -1
 *      b= -1
 *      c= -1
 *  Linea 26:
 *      a= 5 //a y b han pasado por un scanf y se les ha asignado un nuevo valor, por lo que cambian y c no ha sido modificada
 *      b= 6
 *      c= -1
 */
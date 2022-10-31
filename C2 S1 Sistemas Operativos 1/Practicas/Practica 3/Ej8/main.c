#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <signal.h>
#include <limits.h>
#include <stdlib.h>

bool esPrimo(int numero);
void manejador(int senhal);
        double primo;
int main()
{
    signal(SIGALRM, manejador);
    signal(SIGUSR1,manejador);
    alarm(1);
    for(int i =0;i<INT_MAX;i++)
    {
        
        if(esPrimo(i)==true)
        {
            primo= i;//sqrt(i);
        }
 //       printf("salgo con %i.\n",i);
        
    }
    return 0;
}
bool esPrimo(int numero)
{
    int res=0;
    int divs=2;
    int mitad;
    if (numero>2)
    {
        /* Para ahorrar sólo comprobamos si un número es divisible hasta su mitad, ya que 7/2 = 3.xxx, 7/3=2.xxx, 7/4=0.xxx */
        /* cuando empezamos a obtener valores menores que 0, ya no encontraremos más divisores enteros */
        mitad=floor((double)numero/2);
        do
        {
            res=(numero%divs!=0);  /* ¿ El resto es 0 ? */
            //      printf("Divido %d entre %d. Resto %d. Res: %d\n", numero, divs, numero%divs, res);
            divs++;
        } while ((res!=0) && (divs<=mitad));
    }
    else
    {
        res=true;
    }
    
    return res;
}

void manejador(int senhal)
{
    switch(senhal)
    {
        case SIGALRM:
            printf("Numero primo = %lf\n",primo);
            alarm(1);
            break;
        case SIGUSR1:
            exit(0);
    }
}
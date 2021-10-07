#include <stdio.h>
#include<locale.h>
#include<math.h>
/*
 * Programador: Marcelo Fort Muñoz
 * Día: 07/10/2021
 * Propósito del programa: Cálculo del seno de un ángulo α
 */
float factorial(float n);
int main()
{
    float numerodevueltas;
    float n=1;
    float x,seno;
    float w,precision,v;
    setlocale(LC_ALL,"Spanish");
    printf("Introduzca un valor para x: ");
    scanf("%f",&x);

    printf("Introduzca un valor para p: ");
    scanf("%f",&precision);
    w = 99999;
    n=1;
    numerodevueltas=0;
    while(w>precision)
    {
        numerodevueltas+=1;
        w=(pow(x,n)/ factorial(n));
        v += w * pow((-1),(numerodevueltas+1));
        printf("\n w= %f",w);
        printf("\n n = %f",numerodevueltas);
        printf("\n v = %f",v);
        printf("\n ");
        n+=2;
    }
    //printf("Numero: %f",w);
    system("PAUSE");
    return 0;
}

float factorial(float n){
    float  i=0, res = 1;
    for ( i=1;i<=n;i++ )
    {
        res *= i;
    }
    return res;
}

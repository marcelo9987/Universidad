/*
 * Programa incompleto: Falta meter el algoritmo de euclides
 * Programador: Marcelo Fort Muñoz
 * Fecha de incio: 19.01.2021
 */
#define VERDADERO 1
#define FALSO 0
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
float encontprom(int num1, int num2)
{
    float promedio;
    promedio = (num1 + num2) /2.0;
    return(promedio);
}
int mcd(int num1,int num2);//definición de la función mcd
int main()
{
    int a,b;
    float resultado;
    printf("Dame dous valores enteiros:" );
    scanf("%d %d",&a,&b);
    resultado = encontprom(a, b);
    printf("Promedio=%.4f\n",resultado);
    printf("MCD: %d",mcd(a,b));
    printf("\n");
    system("pause");
}
int mcd(int num1,int num2)
{
    int res,a,b,r;
    a = num1;
    b= num2;
    if(b<a)
    {
        int w;
        w = a;
        a = b;
        b = w;
    }
    bool conseg=FALSO;
    while(!conseg)
    {
      //  r=a%b;
        if(a%b != 0)
        {
            r = a%b;
            a=b;
            b=r;
        }else if(a%b == 0) {
            res = b;
            conseg = VERDADERO;
        }
    }
    return res;
}
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
bool onoff = VERDADERO;
float encontprom(int num1, int num2)
{
    float promedio;
    promedio = (num1 + num2) /2.0;
    return(promedio);
}
int main()
{
    int a,b;
    float resultado;
    printf("Dame dous valores enteiros:" );
    scanf("%d %d",&a,&b);
    resultado = encontprom(a, b);
    printf("Promedio=%f\n",resultado);
}
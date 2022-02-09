#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 4
/*
 * Implementa un programa para elevar a la potencia b cada uno de los elementos de un array a:
 *  c=[a[0]b, a[1]b , a[2]b , a[3]b ] siendo a y b y c las variables siguientes: int a[4],c[4],b; de
 *  modo que cada componente del vector c se calcule mediante una función potencia().
 */

/*
 * [a0]=0x61ff04
 * [a1]=0x61ff08
 * [a2]=0x61ff0c
 * [a3]=0x61ff10
 * en el caso de a y b, como ambos son de tipo int, la distancia entre cada sujeto es de 4...
 * b= 0x61ff00
 * c=
    [0] = 0x61fef0
    [1] = 0x61fef4
    [2] = 0x61fef8
    [3] = 0x61fefc
    ... mientras que la distancia entre los de tipo float(como son los miembros de c), es de 4 también. Esto se debe al tamaño que ocupan tanto los int como los float que es de 4 bits
 */
float potencia(int base, int exp);

int main()
{
    int a[4], b;
    float c[4];
    printf("Introuzca los valores de a: ");
    for (int i = 0; i < TAMANHO; i++)
    {
        scanf("%i", &a[ i ]);
    }
    printf("\nIntrouzca el valor de b: ");
    scanf("%i", &b);
    for (int i = 0; i < 4; i++)
    {
        c[ i ] = potencia(a[ i ], b);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO; i++)
    {
        printf("\nc[%i] = %f", i, c[ i ]);
    }
    
    return 0;
}

float potencia(int base, int exp)
{
    float resultado = 1;
    if (exp != 0)
    {
        for (int i = 0; i < abs(exp); i++)
        {
            resultado *= (float) base;
        }
        if (exp < 0 && base != 0)
        {
            resultado = 1 / resultado;
        }
    } else
    {
        resultado = 1;
    }
    
    return resultado;
}

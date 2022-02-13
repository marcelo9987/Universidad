/*
 * PROGRAMA PARA CALCULAR EL FACTORIAL Y LA POTENCIA DE DOS NÚMEROS ENTEROS
 * PEDIDOS AL USUARIO/A POR TECLADO.
 *
 * OBJETIVO: DEPURAR USANDO LAS HERRAMIENTAS DE NETBEANS. 
 * EL PROGRAMA TIENE COMO MÍNIMO SEIS ERRORES. DOCUMENTAR LAS CORRECCIONES 
 * INTRODUCIDAS, PONIENDO UN COMENTARIO CON LA SENTENCIA INCORRECTA AL
 * LADO DE LA SENTENCIA CORREGIDA
 * 
 * PRUEBAS: USAR LOS CASOS
 * 10 2 (factorial=3628800, potencia=100)
 * 2 10 (factorial=2, potencia=1024)
 * -5 1 (factorial no existe por ser negativo, potencia=-5)
 * -5 -3 (factorial no existe por ser negativo, potencia=-0.008)
 * 3 0  (factorial=6, potencia=1)
 * 0 10 (factorial=1, potencia=0)
 * 0 -2 (factorial=1, potencia=1/0=infinito)
 * 0 0  (factorial=1, potencia=0^0, indeterminación)
 */

/* a) Corregir los errores comentando la línea incorrecta y poniendo la correcta a continuación
 * b) Fija un breakpoint e inicia la ejecución en modo depuración ¿Qué sucede al ejecutar paso a paso
 *    (botón “Step into” [F7]) la sentencia donde se invoca la función factorial()?
 *    RESPUESTA: 
 * 
 * c) Al llegar a la función potencia(), utiliza el botón “STEP OVER” [F8]  en  lugar  del  botón  “Step into” [F7]
 *   ¿Qué  diferencias observas frente a la ejecución del apartado b?
 *   RESPUESTA: 
 * 
 * d) Repite la ejecución en modo depuración visualizando todas las variables. 
 *    Indica qué sucede con la ventana de variables cuando el flujo del programa continúa DENTRO de la función
 *    Justifica la información que aparece en la solapa "Call Stack"
 *    RESPUESTA:
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include "operaciones.h"

int main(int argc, char** argv)
{
    
    int a, b;
    int f;
   // int p;
    float p;
    
    //printf("Introduce dos números enteros: ");
    printf("Introduce dos numeros enteros: ");//printf no permite acentos, para acentos usar locale.h con wprintf()
    //scanf("%f%d", a, &b);
    scanf("%d%d", &a, &b);//a es int || el formato de scanf es &a no a
    
    //f = factorial(a);
    if (a > 0)
    {
        f = factorial(a);
        printf("Factorial(%d) = %d\n", a, f);
    } else
    
        printf("Error factorial: el parámetro (%d) no es un entero positivo\n",a);
    
    p = potencia(a, b);
    printf("Potencia(%d,%d) = %f\n", a, b, p);
    
    return (EXIT_SUCCESS);
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long fibonacciIterativo(unsigned char n) {
    unsigned long a = 1, b = 1, c = 0, k = 0;
    for (k = 2; k <= n; k++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

unsigned long fibonacciRecursivo(unsigned char n) {
    if (n > 1)
        return fibonacciRecursivo(n - 1) + fibonacciRecursivo(n - 2);
    else
        return (unsigned long) 1;
}


int main(int argc, char **argv) {
    unsigned long f;    //El mayor rango de representación en enteros positivos
    unsigned char n;    //El menor rango de representación en enteros positivos
    
    FILE *fp;
    
    fp = fopen("tiemposFibonacci.txt", "w"); //Fichero para los datos de salida
    
    for (n = 0; n < 45; n++) {      //Los 45 primeros términos de la sucesión
        clock_t inicio=clock();     //TOMAMOS LA PRIMERA REFERENCIA
        
        // AQUÍ SE INICIA EL BLOQUE DE INSTRUCCIONES CUYO TIEMPO DE EJECUCIÓN QUEREMOS MEDIR
        f = fibonacciRecursivo(n);
        // f = fibonacciIterativo(n);
        
        clock_t fin=clock(); //TOMAMOS LA SEGUNDA REFERENCIA
        
        //IMPRIMIMOS EL RESULTADO
        printf("n:%u\tf(n):%lu\t\tini.:%d\tfin:%d\t\ttiempo:%.4lf\n", n, f, (int) fin, (int) inicio,
               (fin - inicio) / (double) CLOCKS_PER_SEC);
        fprintf(fp, "%u\t%.4lf\n", n, (fin - inicio) / (double) CLOCKS_PER_SEC); //Salida de los datos n, t(n) a fichero
    }
    fclose(fp);
    return (EXIT_SUCCESS);
}

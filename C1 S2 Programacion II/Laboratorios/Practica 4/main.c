#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool cambio(int importeDevolver, int numTiposMonedas, int valor[], int solucion[]);

int main(int argc, char* argv[])
{
    int numTiposMonedas;
    int* valor;
    //int importeDevolver = 123456789;
    int numTiposMonedas_eur = 15;
    int numTiposMonedas_usd = 17;
    int valor_eur[] = {500 * 100, 200 * 100, 100 * 100, 50 * 100, 20 * 100, 10 * 100, 5 * 100, 2 * 100, 1 * 100, 50, 20, 10, 5, 2, 1};
    int valor_usd[] = {100000 * 100, 10000 * 100, 5000 * 100, 1000 * 100, 500 * 100, 100 * 100, 50 * 100, 20 * 100, 10 * 100, 5 * 100, 2 * 100, 1 * 100, 50, 25, 10, 5, 1};
    int solucion[100];
    
    char seleccion;
    do
    {
        fprintf(stdout, "En que divisa desea operar(E:€ D:$): ");
        fscanf(stdin, "%c", &seleccion);
    } while (seleccion != 'E' && seleccion != 'D');
    
    if (seleccion == 'E')
    {
        numTiposMonedas = numTiposMonedas_eur;
        valor = valor_eur;
    } else if (seleccion == 'D')
    {
        numTiposMonedas = numTiposMonedas_usd;
        valor = valor_usd;
    }
    
    int importeDevolver;
    do
    {
        do
        {
            fprintf(stdout, "Introduzca el valor a cambiar (0 para salir): ");
            if (fscanf(stdin, "%i", &importeDevolver) < 1)
            {
                importeDevolver = -1;
                while(getchar()!='\n');
            }
        } while (importeDevolver < 0);
        
        if (importeDevolver > 0)
        {
            bool ok = cambio(importeDevolver, numTiposMonedas, valor, solucion);
            if (ok)
            {
                for (int pos = 0; pos < numTiposMonedas_eur; pos++)
                {
                    fprintf(stdout, "valor %5i es: %5i\n", valor[pos], solucion[pos]);//formatear
                }
                
            } else
            {
                fprintf(stdout, "No se ha podido calcular el cambio\n");
            }
        }
    } while (importeDevolver != 0);
    
    return 0;
}

bool cambio(int importeDevolver, int numTiposMonedas, int valor[], int solucion[])
{
    
    for (int pos = 0; pos < numTiposMonedas; pos++)
    {
        solucion[pos] = 0;
    }
    
    int suma = 0;
    for (int pos = 0; suma < importeDevolver && pos < numTiposMonedas;)
    {
        if (suma + valor[pos] <= importeDevolver)
        {
            solucion[pos]++;
            suma += valor[pos];
        } else
        {
            pos++;
        }
    }
    
    if (suma == importeDevolver)
    {
        return true;
    } else
    {
        for (int pos = 0; pos < numTiposMonedas; pos++)
        {
            solucion[pos] = 0;
        }
        
        return false;
    }
}



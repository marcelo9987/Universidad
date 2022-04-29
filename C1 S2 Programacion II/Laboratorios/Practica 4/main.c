#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vectordinamico.h"

bool cambio(int importeDevolver, int numTiposMonedas, vectorD vectorValoresDivisas, int solucion[])
{
    
    for (int pos = 0; pos < numTiposMonedas; pos++)
    {
        solucion[pos] = 0;
    }
    
    int suma = 0;
    for (short pos = 0; suma < importeDevolver && pos < numTiposMonedas;)
    {
        if (suma + recuperar(vectorValoresDivisas, pos) <= importeDevolver)
        {
            solucion[pos]++;
            suma += recuperar(vectorValoresDivisas, pos);
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

int main(int argc, char* argv[])
{
    vectorD vectorValoresDivisas;
    short numTiposMonedas;
    int* valor = NULL;
    //int importeDevolver = 123456789;
    short numTiposMonedas_eur = 15;
    short numTiposMonedas_usd = 17;
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
    
    crear(&vectorValoresDivisas, numTiposMonedas);
    
    for (short indice = 0; indice < numTiposMonedas; indice++)
    {
        asignar(&vectorValoresDivisas, indice, valor[indice]);
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
                while (getchar() != '\n');
            }
        } while (importeDevolver < 0);
        
        if (importeDevolver > 0)
        {
            fprintf(stdout,"valor a devolver: %i\n",importeDevolver);
            bool ok = cambio(importeDevolver, numTiposMonedas, vectorValoresDivisas, solucion);
            if (ok)
            {
                for (short pos = 0; pos < numTiposMonedas; pos++)
                {
                    fprintf(stdout, "valor %5i es: %5i\n", recuperar(vectorValoresDivisas, pos), solucion[pos]);//formatear
                }
                
            } else
            {
                fprintf(stdout, "No se ha podido calcular el cambio\n");
            }
        }
    } while (importeDevolver != 0);
    
    return 0;
}


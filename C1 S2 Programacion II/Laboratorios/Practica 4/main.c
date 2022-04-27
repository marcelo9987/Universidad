#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool cambio(int importeDevolver, int numTiposMonedas, int valor[], int solucion[]);

int main(int argc, char* argv[])
{
    int importeDevolver = 123456789;
    int numTiposMonedas = 15;
    int valor[] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    int solucion[numTiposMonedas];
    
    bool ok = cambio(importeDevolver, numTiposMonedas, valor, solucion);
    if (ok)
    {
        
        
        for (int pos = 0; pos < numTiposMonedas; pos++)
        {
            fprintf(stdout, "valor %5i es: %5i\n", valor[ pos ], solucion[ pos ]);//formatear
        }
    } else
    {
        fprintf(stdout, "No se ha podido calcular el cambio\n");
    }
    return 0;
}

bool cambio(int importeDevolver, int numTiposMonedas, int valor[], int solucion[])
{
    
    for (int pos = 0; pos < numTiposMonedas; pos++)
    {
        solucion[ pos ] = 0;
    }
    
    int suma = 0;
    for (int pos = 0; suma < importeDevolver && pos < numTiposMonedas;)
    {
        if (suma + valor[ pos ] <= importeDevolver)
        {
            solucion[ pos ]++;
            suma += valor[ pos ];
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
            solucion[ pos ] = 0;
        }
        
        return false;
    }
}



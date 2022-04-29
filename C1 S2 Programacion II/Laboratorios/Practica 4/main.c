#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vectordinamico.h"

enum enumModosOperacion
{
    Limitado, Ilimitado
};

bool cambio(int importeDevolver, vectorD vectorValoresDivisas, vectorD vectorSolucion, vectorD vectorStock, enum enumModosOperacion modoOperacion)
{
    
    for (short pos = 0; pos < longitudVector(vectorSolucion); pos++)
    {
        asignar(&vectorSolucion, pos, 0);
    }
    
    int suma = 0;
    for (short pos = 0; suma < importeDevolver && pos < longitudVector(vectorSolucion);)
    {
        bool hayMonedasDisponibles = true;
        if (modoOperacion == Limitado)
        {
            if (recuperar(vectorStock, pos) <= 0)
            {
                hayMonedasDisponibles = false;
            }
            
        }
        
        if (hayMonedasDisponibles && suma + recuperar(vectorValoresDivisas, pos) <= importeDevolver)
        {
            asignar(&vectorSolucion, pos, recuperar(vectorSolucion, pos) + 1);
            suma += recuperar(vectorValoresDivisas, pos);
            if (modoOperacion == Limitado)
            {
                asignar(&vectorStock, pos, recuperar(vectorStock, pos) - 1);
            }
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
        for (short pos = 0; pos < longitudVector(vectorSolucion); pos++)
        {
            asignar(&vectorStock, pos, recuperar(vectorStock, pos) + recuperar(vectorSolucion, pos));
            asignar(&vectorSolucion, pos, 0);
        }
        
        return false;
    }
}

int main(int argc, char* argv[])
{
    vectorD vectorValoresDivisas, vectorSolucion, vectorStock;
    short numTiposMonedas;
    int* valor = NULL;
    //int importeDevolver = 123456789;
    short numTiposMonedas_eur = 15;
    short numTiposMonedas_usd = 17;
    int valor_eur[] = {500 * 100, 200 * 100, 100 * 100, 50 * 100, 20 * 100, 10 * 100, 5 * 100, 2 * 100, 1 * 100, 50, 20, 10, 5, 2, 1};
    int valor_usd[] = {100000 * 100, 10000 * 100, 5000 * 100, 1000 * 100, 500 * 100, 100 * 100, 50 * 100, 20 * 100, 10 * 100, 5 * 100, 2 * 100, 1 * 100, 50, 25, 10, 5, 1};
    int arrayStock[] = {1, 2, 0, 4, 6, 9, 8, 7, 1, 2, 0, 0, 1, 5, 6, 0, 1};
    //--//
    
    char seleccion;
    enum enumModosOperacion modoOperacion;
    do
    {
        fprintf(stdout, "¿En que modo desea operar? (L: Unidades limitadas | I: Unidades infinitas): ");
        fscanf(stdin, "%c", &seleccion);
        while (getchar() != '\n');
    } while (seleccion != 'I' && seleccion != 'L');
    
    if (seleccion == 'I')
    {
        modoOperacion = Ilimitado;
    } else
    {
        modoOperacion = Limitado;
    }
    
    //--//
    
    //char seleccion;
    
    do
    {
        fprintf(stdout, "En que divisa desea operar(E:€ D:$): ");
        fscanf(stdin, "%c", &seleccion);
        while (getchar() != '\n');
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
    
    //--//
    
    crear(&vectorValoresDivisas, numTiposMonedas);
    
    for (short indice = 0; indice < numTiposMonedas; indice++)
    {
        asignar(&vectorValoresDivisas, indice, valor[indice]);
    }
    
    //--//
    
    if (modoOperacion == Limitado)
    {
        crear(&vectorStock, numTiposMonedas);
        for (short indice = 0; indice < numTiposMonedas; indice++)
        {
            asignar(&vectorStock, indice, arrayStock[indice]);
        }
    } else
    {
        vectorStock = NULL;
    }
    
    //--//
    
    crear(&vectorSolucion, numTiposMonedas);
    
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
            
            if (modoOperacion == Limitado)
            {
                fprintf(stdout, "---- MODO LIMITADO: Valores iniciales disponibles ----\n");
                fprintf(stdout, "    Valor | Disponibles\n");
                for (short pos = 0; pos < numTiposMonedas; pos++)
                {
                    fprintf(stdout, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorStock, pos));//formatear
                }
                fprintf(stdout, "\n");
            }
            
            fprintf(stdout, "---- Importe a devolver: %i ----\n", importeDevolver);
            
            bool ok = cambio(importeDevolver, vectorValoresDivisas, vectorSolucion, vectorStock, modoOperacion);
            if (ok)
            {
                fprintf(stdout, "    Valor | Devuelto\n");
                
                for (short pos = 0; pos < numTiposMonedas; pos++)
                {
                    fprintf(stdout, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorSolucion, pos));//formatear
                }
                //  }
            } else
            {
                fprintf(stdout, "No se ha podido calcular el cambio\n");
            }
        }
    } while (importeDevolver != 0);
    
    if (modoOperacion == Limitado)
    {
        fprintf(stdout, "---- MODO LIMITADO: Valores finales disponibles ----\n");
        fprintf(stdout, "    Valor | Disponibles\n");
        for (short pos = 0; pos < numTiposMonedas; pos++)
        {
            fprintf(stdout, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorStock, pos));//formatear
        }
        fprintf(stdout, "\n");
    }
    
    //--//
    
    liberar(&vectorValoresDivisas);
    liberar(&vectorSolucion);
    if (modoOperacion == Limitado)
    {
        liberar(&vectorStock);
    }
    
    //--//
    
    return 0;
}


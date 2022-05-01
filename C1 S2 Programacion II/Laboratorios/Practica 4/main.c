#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "config.h"
#include "vectordinamico.h"
#include  "leerStock.c"

#define K_MAX_NOMBRE_ARCHIVO 128

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

vectorD leerStock(short numTiposMonedas, char* nombreArchivo)
{
    vectorD vectorStock = NULL;
    crear(&vectorStock, numTiposMonedas);
    
    
    FILE* archivoStock = fopen(nombreArchivo, "r");
    
    if (archivoStock == NULL)
    {
        fprintf(STDERR, "Error en la lectura del archivo del stock para esta moneda. Razón: %s\n", strerror(errno));
        fprintf(STDOUT, "Se procederá con stock inicial = 0.\nSe recomienda recargar el saldo antes de proceder.\n");
        
    } else
    {
        
        for (short pos = 0; pos < numTiposMonedas; pos++)
        {
            int tempValStock;
            if(fscanf(archivoStock, "%i,", &tempValStock)!=1)
            {
                fprintf(STDERR,"Error en lectura del archivo de stock. Formato incorrecto\n");
                break;
            }
            asignar(&vectorStock, pos, tempValStock);
        }
        fclose(archivoStock);
    }
    return vectorStock;
}

void guardarStock(vectorD vectorStock, char* nombreArchivo)
{
    FILE* archivoStock = fopen(nombreArchivo, "w");
    if (archivoStock == NULL)
    {
        fprintf(STDERR, "Error en la apertura del archivo para guardado del stock final de esta moneda. Razón: %s\n", strerror(errno));
        fprintf(STDOUT, "NO se ha podido realizar el guardado del stock final.\n");
    } else
    {
        short longVectMenos1 = longitudVector(vectorStock) -1;
        for (short pos = 0; pos <= longVectMenos1; pos++)
        {
            fprintf(archivoStock, "%i", recuperar(vectorStock, pos));
            if (pos < longVectMenos1)
            {
                fprintf(archivoStock, ", ");
            }
        }
        fputc('\n',archivoStock);
    }
    fclose(archivoStock);
}

int main(int argc, char* argv[])
{
    vectorD vectorValoresDivisas, vectorSolucion;
    short numTiposMonedas;
    int* valor = NULL;
    
    //int importeDevolver = 123456789;
    short numTiposMonedas_eur = 15;
    short numTiposMonedas_usd = 17;
    int valor_eur[] = {500 * 100, 200 * 100, 100 * 100, 50 * 100, 20 * 100, 10 * 100, 5 * 100, 2 * 100, 1 * 100, 50, 20, 10, 5, 2, 1};
    int valor_usd[] = {100000 * 100, 10000 * 100, 5000 * 100, 1000 * 100, 500 * 100, 100 * 100, 50 * 100, 20 * 100, 10 * 100, 5 * 100, 2 * 100, 1 * 100, 50, 25, 10, 5, 1};
    //int arrayStock[] = {1, 2, 0, 4, 6, 9, 8, 7, 1, 2, 0, 0, 1, 5, 6, 0, 1};
    //--//
    
    char seleccion;
    enum enumModosOperacion modoOperacion;
    do
    {
        fprintf(STDOUT, "¿En que modo desea operar? (L: Unidades limitadas | I: Unidades infinitas): ");
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
        fprintf(STDOUT, "En que divisa desea operar(E:€ D:$): ");
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
    char nombreArchivoStock[K_MAX_NOMBRE_ARCHIVO] = "";
    vectorD vectorStock = NULL;
    
    if (modoOperacion == Limitado)
    {
        sprintf(nombreArchivoStock, "%s.stock", "euro");
        vectorStock = leerStock(numTiposMonedas, nombreArchivoStock);
    }
    
    //--//
    
    crear(&vectorSolucion, numTiposMonedas);
    
    int importeDevolver;
    do
    {
        do
        {
            fprintf(STDOUT, "Introduzca el valor a cambiar (0 para salir): ");
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
                fprintf(STDOUT, "---- Stock inicial disponible ----\n");
                fprintf(STDOUT, "    Valor | Disponible\n");
                for (short pos = 0; pos < numTiposMonedas; pos++)
                {
                    fprintf(STDOUT, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorStock, pos));//formatear
                }
                fprintf(STDOUT, "\n");
            }
            
            fprintf(STDOUT, "---- Importe a devolver: %i ----\n", importeDevolver);
            
            bool ok = cambio(importeDevolver, vectorValoresDivisas, vectorSolucion, vectorStock, modoOperacion);
            if (ok)
            {
                fprintf(STDOUT, "    Valor |   Devuelto\n");
                
                for (short pos = 0; pos < numTiposMonedas; pos++)
                {
                    fprintf(STDOUT, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorSolucion, pos));//formatear
                }
                fprintf(STDOUT, "\n");
                
            } else
            {
                fprintf(STDOUT, "No se ha podido calcular el cambio\n\n");
            }
        }
        
        if (modoOperacion == Limitado)
        {
            fprintf(STDOUT, "---- Stock disponible:----\n");
            fprintf(STDOUT, "    Valor | Disponible\n");
            for (short pos = 0; pos < numTiposMonedas; pos++)
            {
                fprintf(STDOUT, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorStock, pos));//formatear
            }
            fprintf(STDOUT, "\n");
        }
        
    } while (importeDevolver != 0);
    
    //--//
    if (modoOperacion == Limitado)
    {
        guardarStock(vectorStock, nombreArchivoStock);
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


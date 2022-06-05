#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "config.h"
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
            if (fscanf(archivoStock, "%i,", &tempValStock) != 1)
            {
                fprintf(STDERR, "Error en lectura del archivo de stock. Formato incorrecto\n");
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
        short longVectMenos1 = longitudVector(vectorStock) - 1;
        for (short pos = 0; pos <= longVectMenos1; pos++)
        {
            fprintf(archivoStock, "%i", recuperar(vectorStock, pos));
            if (pos < longVectMenos1)
            {
                fprintf(archivoStock, ", ");
            }
        }
        fputc('\n', archivoStock);
    }
    fclose(archivoStock);
}

void mostrarSolucionCambio(vectorD vectorValoresDivisas, vectorD vectorSolucion)
{
    fprintf(STDOUT, "    Valor |   Devuelto\n");
    for (short pos = 0; pos < longitudVector(vectorValoresDivisas); pos++)
    {
        fprintf(STDOUT, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorSolucion, pos));
    }
    fprintf(STDOUT, "\n");
}

void mostrarStockActual(vectorD vectorValoresDivisas, vectorD vectorStock)
{
    fprintf(STDOUT, "    Valor | Disponible\n");
    for (short pos = 0; pos < longitudVector(vectorValoresDivisas); pos++)
    {
        fprintf(STDOUT, "%9i : %9i\n", recuperar(vectorValoresDivisas, pos), recuperar(vectorStock, pos));
    }
    fprintf(STDOUT, "\n");
}

void recuperarValoresDivisas(vectorD* vectorValoresDivisas, char* nombreDivisa)
{
    FILE* archivoValores = fopen("divisas.data", "r");
    
    if (archivoValores == NULL)
    {
        fprintf(STDERR, "Error en la lectura del archivo de divisas. Razón: %s\n", strerror(errno));
        exit(-1);
    }
    /*
    do
    { // Se pide y almacena el nombre de la divisa con la que se va a tratar.
        fprintf(STDOUT, "Escriba el nombre de la divisa: ");
        fscanf(stdin, "%s", nombreDivisa);
        
        while (getchar() != '\n');
        
        if (strcmp(nombreDivisa, "") == 0)
        {
            fprintf(STDERR, "Nombre no válido.\n");
        }
    } while (strcmp(nombreDivisa, "") == 0);
    */
    char nombreDivisaLeido[K_MAX_NOMBRE_DIVISA];
    short numTiposMonedas;
    do
    {
        do
        { // Se pide y almacena el nombre de la divisa con la que se va a tratar.
            fprintf(STDOUT, "Escriba el nombre de la divisa: ");
            fscanf(stdin, "%s", nombreDivisa);
            
            while (getchar() != '\n');
            
            if (strcmp(nombreDivisa, "") == 0)
            {
                fprintf(STDERR, "Nombre no válido.\n");
            }
        } while (strcmp(nombreDivisa, "") == 0);
        
        bool encontrado = false;
        while (fscanf(archivoValores, "%s", nombreDivisaLeido) == 1)
        {
            if (strcmp(nombreDivisaLeido, nombreDivisa) == 0)//se ha encontrado la divisa solicitada
            {
                
                if (fscanf(archivoValores, "%hi", &numTiposMonedas) != 1)
                {
                    fprintf(STDERR, "Error, formato incorrecto.\n");
                    exit(-1);
                }
                if (numTiposMonedas <= 0)
                {
                    fprintf(STDERR, "El número de tipos faciales ha de ser mayor o igual a 1.\n");
                    exit(-1);
                }
                encontrado = true;
                break;
            }
        }
        
        if (encontrado == true)
        {
            break;
        }
        
        
        {
            fclose(archivoValores);//reiniciamos el puntero al inicio del archivo
            archivoValores = fopen("divisas.data", "r");
            if (archivoValores == NULL)
            {
                fprintf(STDERR, "Error en la lectura del archivo de divisas. Razón: %s\n", strerror(errno));
                exit(-1);
            }
            fprintf(STDOUT, "No se ha encontrado la divisa, introduzca otra divisa. \n");
            
        }
        
    } while (true);
    
    crear(vectorValoresDivisas, numTiposMonedas);
    
    for (short pos = 0; pos < numTiposMonedas; pos++)
    {
        int tempValDivisa;
        if (fscanf(archivoValores, "%i,", &tempValDivisa) != 1)
        {
            fprintf(STDERR, "Error en lectura del archivo de valores faciales. Formato incorrecto\n");
            exit(-1);
        }
        asignar(vectorValoresDivisas, pos, tempValDivisa);
    }
    
    fclose(archivoValores);
}

int main(int argc, char* argv[])
{
    
    //--//
    enum enumModosOperacion modoOperacion;
    
    {
        char seleccion;
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
    }
    //--//
    vectorD vectorValoresDivisas;
    
    //! \brief Variable con el nombre de la divisa utilizada. Usada para los ficheros (Valores faciales y stock).
    char nombreDivisa[K_MAX_NOMBRE_DIVISA];
    
    recuperarValoresDivisas(&vectorValoresDivisas, nombreDivisa);
    
    short numTiposMonedas = longitudVector(vectorValoresDivisas);
    //--//
    char nombreArchivoStock[K_MAX_NOMBRE_ARCHIVO] = "";
    vectorD vectorStock = NULL;
    
    if (modoOperacion == Limitado)
    {
        sprintf(nombreArchivoStock, "%s.stock", nombreDivisa);
        vectorStock = leerStock(numTiposMonedas, nombreArchivoStock);
    }
    
    //--//
    vectorD vectorSolucion;
    crear(&vectorSolucion, numTiposMonedas);
    
    int importeDevolver;
    
    do
    {
        if (modoOperacion == Limitado)
        {
            fprintf(STDOUT, "---- Stock disponible:----\n");
            mostrarStockActual(vectorValoresDivisas, vectorStock);
            
            char opcion = '\0';
            do
            {
                fprintf(STDOUT, "Desea obtener cambio(a), aumentar el stock(b) o salir(c): ");
                fscanf(stdin, "%c", &opcion);
                
                while (getchar() != '\n');
                
                if (opcion == 'b')
                {
                    
                    for (short pos = 0; pos < numTiposMonedas; pos++)
                    {
                        asignar(&vectorStock, pos, recuperar(vectorStock, pos) + 10);
                    }
                    
                    fprintf(STDOUT, "---- Stock disponible:----\n");
                    mostrarStockActual(vectorValoresDivisas, vectorStock);
                }
                
            } while (opcion != 'a' && opcion != 'c');
            
            if (opcion == 'c')
            {
                break;
            }
        }
        
        do
        {
            fprintf(STDOUT, "Introduzca el valor a cambiar (0 para salir): ");
            if (fscanf(stdin, "%i", &importeDevolver) < 1)
            {
                importeDevolver = -1;
            }
            while (getchar() != '\n');
        } while (importeDevolver < 0);
        
        if (importeDevolver > 0)
        {
            
            /*if (modoOperacion == Limitado)
            {
                fprintf(STDOUT, "---- Stock inicial disponible ----\n");
                mostrarStockActual(vectorValoresDivisas, vectorStock);
            }*/
            
            fprintf(STDOUT, "---- Importe a devolver: %i ----\n", importeDevolver);
            
            bool ok = cambio(importeDevolver, vectorValoresDivisas, vectorSolucion, vectorStock, modoOperacion);
            if (ok)
            {
                mostrarSolucionCambio(vectorValoresDivisas, vectorSolucion);
                
            } else
            {
                fprintf(STDOUT, "No se ha podido calcular el cambio\n\n");
            }
        }
        
        /* if (modoOperacion == Limitado)
         {
             fprintf(STDOUT, "---- Stock disponible:----\n");
             mostrarStockActual(vectorValoresDivisas, vectorStock);
         }*/
        
    } while (importeDevolver != 0);
    
    //--//
    if (modoOperacion == Limitado)
    {
        guardarStock(vectorStock, nombreArchivoStock);
        liberar(&vectorStock);
    }
    //--//
    
    liberar(&vectorValoresDivisas);
    liberar(&vectorSolucion);
    //--//
    
    return 0;
}

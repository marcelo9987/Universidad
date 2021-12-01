#include "meteo.h"
#include <stdio.h>
#include <stdlib.h>

bool esBisiesto(int ano)
{//idc
    if (ano % 4 == 0 && ano % 100 != 0)
    {
        return 1;
    } else if (ano % 4 == 0 && ano % 100 == 0 && ano % 400 == 0)
    {
        return 1;
    } else
    {
        return 0;
    }// fdc
}

WeatherData *leerArchivo(FILE *archivo)
{
    WeatherData *vectorSalida;
    
    char* dump;
    dump=(char*)malloc(200*sizeof(char));
    bool linea1 = true;
    do
    {
        if (linea1)
        {
            fgets(dump,200,archivo);
            linea1 = false;
        }
        
    }while(feof(archivo));
    free(dump);
    return vectorSalida;
}



/*
 * Se define la siguiente nomenclatura:
 * fdc: fin de declaración
 * idc: inicio de declaración
 */
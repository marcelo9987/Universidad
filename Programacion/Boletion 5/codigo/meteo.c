#include "meteo.h"
#include <stdio.h>
#include <stdlib.h>
/* VERSIÓN 0:1.1.3*/
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
    char *dump;
    bool linea1 = true;
    char lineaNueva = 'e';
    int lineas = 0;
    linea1 = true;
    dump = (char *) malloc(129 *
                           sizeof(char));//las cabeceras de los archivos de datos siempre miden 128 caracteres(para evitar fallos, declaro un bit más de los que necesito)
    //se busca cuantas lineas tiene el archivo de texto
    do
    {
        if (linea1)
        {
            fgets(dump, 128, archivo);
            linea1 = false;
        } else
        {
            lineaNueva = getc(archivo);
            if (lineaNueva == '\n')
            {
                lineas += 1;
            }
        }
        
        
    } while (lineaNueva != EOF);
    vectorSalida = (WeatherData *) malloc(lineas * sizeof(WeatherData));
    printf("Numero de lineas: /%i/", lineas);
    fseek(archivo, 130 * sizeof(char), SEEK_SET);
   // fgets(dump, 129, archivo);
    //printf("Texto recogido por dump: [%s]", dump);
    
    for (int i = 0; i < lineas; i++)
    {
        getc(archivo);
        fscanf(archivo, "%i[^/]", &vectorSalida[i].fecha.mes);
        getc(archivo);
        fscanf(archivo, "%i[^/]", &vectorSalida[i].fecha.dia);
        getc(archivo);
        fscanf(archivo, "%i", &vectorSalida[i].fecha.ano);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%f", &vectorSalida[i].longitude);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%f", &vectorSalida[i].latitude);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%i", &vectorSalida[i].elevation);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%lf", &vectorSalida[i].max_temperature);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%lf", &vectorSalida[i].min_temperature);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%lf", &vectorSalida[i].precipitation);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%lf", &vectorSalida[i].wind);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%lf", &vectorSalida[i].relativeHumidity);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        fscanf(archivo, "%lf", &vectorSalida[i].solar);
        getc(archivo);
        getc(archivo);
        getc(archivo);
        printf("Linea: %i",i);
    }
    
    
    while (feof(archivo));
    free(dump);
    vectorSalida = malloc(lineas * sizeof(WeatherData));
    return vectorSalida;
}



/*
 * Se define la siguiente nomenclatura:
 * fdc: fin de declaración
 * idc: inicio de declaración
 */
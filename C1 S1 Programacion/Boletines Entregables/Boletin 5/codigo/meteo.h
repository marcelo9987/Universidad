#ifndef LASNUBES_LIB_METEO_H
#define LASNUBES_LIB_METEO_H

#include <stdio.h>
#include <stdbool.h>
#include "fechas.h"

#pragma once

typedef struct
{
    Date fecha;
    float longitude;
    float latitude;
    int elevation;
    double max_temperature;
    double min_temperature;
    double precipitation;
    double wind;
    double relativeHumidity;
    double solar;
} WeatherData;


bool esBisiesto(int ano);

WeatherData *leerArchivo(FILE *archivo);


#endif //LASNUBES_LIB_METEO_H
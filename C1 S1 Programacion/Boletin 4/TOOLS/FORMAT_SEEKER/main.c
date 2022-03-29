#include <stdio.h>
#include "../../../Boletin3/Ej 9/fechas.h"
typedef struct{
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
}WeatherData;

int main()
{
    FILE* a12dccs;
    WeatherData dvis[4018];
    a12dccs=fopen("../../../dtb/weatherdata-420-72.dat","rb");
    int numstruct;
    scanf("%i",&numstruct);
    numstruct -=1;
    fseek(a12dccs,sizeof (WeatherData)*numstruct,SEEK_SET);
    WeatherData punto;

    fread(&punto,sizeof(WeatherData),1,a12dccs);
    printf("La fecha es: D:%i M:%i A:%i",punto.fecha.dia,punto.fecha.mes,punto.fecha.ano);
    system("pause");
}
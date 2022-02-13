#include <stdio.h>
#include "../../../Boletin3/Ej 9/fechas.h"
// Se intentará crear este programa de forma que sea lo más fácil posible de reconvertir en una librería posteriormente

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
}WeatherData;


int main() {
    FILE* a12dccs;
    WeatherData dvis[4018];
    a12dccs=fopen("../../../dtb/weatherdata-420-72.dat","rb");
    fread(dvis,sizeof(WeatherData),4018,a12dccs);
    for(int i = 0; i<4018;i++)
    {
        printf("\n\nDIA %i MES %i ANO %i",dvis[i].fecha.dia,dvis[i].fecha.mes,dvis[i].fecha.ano);
    }


    return 0;
}

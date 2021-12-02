#include <stdio.h>
#include <locale.h>
#include "meteo.h"
int main()
{
    FILE* archivor;
    archivor=fopen("D:/github/Universidad/Programacion/Boletion 5/codigo/weatherdata-420-72.csv","r");
    setlocale(LC_ALL,"Spanish");
    WeatherData* test= leerArchivo(archivor);
    return 0;
}

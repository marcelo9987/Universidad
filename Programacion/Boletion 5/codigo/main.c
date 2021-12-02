#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>
#include "meteo.h"
int main()
{
    FILE* archivor;
    int tamanho=0;
    WeatherData* datos;
    archivor=fopen("D:/github/Universidad/Programacion/Boletion 5/codigo/arch_2.csv","rt");
    setlocale(LC_ALL,"Spanish");
    WeatherData* test;
    test = leerArchivo(archivor);
    tamanho= sizeof(test)/sizeof(WeatherData*);
    wprintf(L"El tamaño es: %i",tamanho);
    free(test);
    return 0;
}

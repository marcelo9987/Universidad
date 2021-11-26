/*
 * Programador: Marcelo Fort Muñoz
 * Fecha de finalización: 23.11.2021
 * Descripción: lee un archivo. Luego te permite hacer búsquedas(1: por fecha y 2: por 2 fechas y dá la precipitación)
 */
#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>//sin uso
#include <locale.h>
//#include <windows.h>//sin uso
//#include <time.h>//no se usa
#include "../../Boletin3/Ej 9/fechas.h"
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
Date fijo;
WeatherData* entreFechas( FILE* elarchivo,Date fechar1,Date fechar2 );
int main()
{
    setlocale( LC_ALL,"Spanish" );
    FILE* archivo;
    int longit;
    WeatherData* aRr;
    archivo=fopen( "../../dtb/weatherdata-420-72.dat","rb" );
    if(archivo==NULL)
    {
        wprintf(L"Error de lectura,\n ¿Existe el archivo al que intentas acceder?");
    }else
    {
        fijo.ano = 2000;
        fijo.mes = 1;
        fijo.dia = 1;
        ler(&fecha1);
        ler(&fecha2);
        longit = (int) CalcularDistancia(&fecha1, &fecha2);
        //aRr=( WeatherData* )malloc(longit*sizeof( WeatherData ) );
        aRr = entreFechas(archivo, fecha1, fecha2);


        wprintf(L"Primera Entrada: \n Dia:%i\nMes: %i\nAño: %i\n\n Segunda Entrada: \n Dia:%i\nMes: %i\nAño: %i\n",
                aRr[0].fecha.dia, aRr[0].fecha.mes, aRr[0].fecha.ano, aRr[longit].fecha.dia, aRr[longit].fecha.mes,
                aRr[longit].fecha.ano);


        //  wprintf(L"La dirección de memoria de aRr es :%p",aRr);
        fclose(archivo);

        free(aRr);//Problema Solucionado a 23//11/2021: Al liberar espacio, se había deformado el malloc, al tener más espacio declarado que el real


    }
    system("pause");
    return 0;
}

WeatherData* entreFechas( FILE* elarchivo,Date fechar1,Date fechar2 )
{
    WeatherData *elVector;
    /*! @var a1 @var a2 @brief Posiciones el número de cada fecha respecto al 1/1/2000  */
    int a1,a2;
    int leng;
    a1= ( int )CalcularDistancia( &fijo,&fechar1 );
    a2= ( int )CalcularDistancia( &fijo,&fechar2 );
    if( a2>a1 )
    {
        fseek(elarchivo,(int)sizeof(WeatherData )*(a1),SEEK_SET);
        if( a2!=a1+1 )
        {
            leng = a2-a1 +1;
        }
        if( a2==a1+1 )
        {
            leng = 2;
        }

    }
    if( a2<a1 )
    {
        fseek(elarchivo,(int)sizeof(WeatherData )*(a2),SEEK_SET);
        if (a2!=a1+1 )
        {
            leng = a1-a2 +1;
        }
        if( a2==a1+1 )
        {
            leng = 2;
        }
    }

    elVector = malloc( leng  * sizeof( WeatherData ) );

    fread( elVector,sizeof( WeatherData ),leng,elarchivo );
    return elVector;

}





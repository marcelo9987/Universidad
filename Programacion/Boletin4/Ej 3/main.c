#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
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
    fijo.ano=2000;
    fijo.mes=1;
    fijo.dia=1;
    ler( &fecha1 );
    ler( &fecha2 );
    longit= ( int )CalcularDistancia( &fecha1,&fecha2 );
    //aRr=( WeatherData* )malloc(longit*sizeof( WeatherData ) );
    aRr=entreFechas( archivo,fecha1,fecha2 );


    wprintf( L"Primera Entrada: \n Dia:%i\nMes: %i\nAño: %i\n\n Segunda Entrada: \n Dia:%i\nMes: %i\nAño: %i\n",aRr[0].fecha.dia,aRr[0].fecha.mes,aRr[0].fecha.ano,aRr[longit].fecha.dia,aRr[longit].fecha.mes,aRr[longit].fecha.ano );


  //  wprintf(L"La dirección de memoria de aRr es :%p",aRr);
    system( "pause" );
    fclose( archivo );

    free( aRr );//Problema Solucionado a 23//11/2021: Al liberar espacio, se había deformado el malloc, al tener más espacio declarado que el real



    return 0;
}
WeatherData* entreFechas( FILE* elarchivo,Date fechar1,Date fechar2 )
{
    int rr=0;
    WeatherData VectorDesechable[4018];
    WeatherData *elVector;
    int a1,a2;
    int leng;
    a1= ( int )CalcularDistancia( &fijo,&fechar1 );
    a2= ( int )CalcularDistancia( &fijo,&fechar2 );
    if( a2>a1 )
    {
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
        if (a2!=a1+1 )
        {
            leng = a1-a2 +1;
        }
        if( a2==a1+1 )
        {
            leng = 2;
        }
    }
    elVector=malloc( leng  * sizeof( WeatherData ) );
    fread( &VectorDesechable,sizeof(WeatherData),4018,elarchivo );
    for( int i = a1;i<a2+1;i++ )
    {
        *( elVector+rr )= VectorDesechable[i];
        //wprintf(L"PRUEBA PRE-DEPURACIÓN: d:%i m:%i a:%i\n",(elVector+rr)->fecha.dia,(elVector+rr)->fecha.mes,(elVector+rr)->fecha.ano);
        rr+=1;
    }
    //system( "pause" );
   // wprintf(L"La dirección de memoria de elVector es :%p",elVector);
    system( "pause" );
    return elVector;

}





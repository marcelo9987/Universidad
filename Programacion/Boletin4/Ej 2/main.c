#define VERDADERO 1
#define FALSO     0
/*
 *  Programador: Marcelo Fort Muñoz
 *  Descripción: El ejercicio repite el ej9 pero con punteros.
 *  Fecha de inicio: 19/11/2021
 *      Hora de inicio: 9:20
 *  Fecha de finalización:
 *  Version: DEV.0.0.1
 *      Subversión: 0.0.5
 */
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <stdbool.h>
#include "../../Boletin3/Ej 9/fechas.h"
                        ///////////////*****Declaración de estructuras y variables*****///////////////

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
Date* fijo;//de momento no sé si lo usaré
WeatherData* result;
                            ///////////////*****Declaración de funciones*****///////////////
void menuprincipal(FILE* tallin);
WeatherData* Consulta_por_data(FILE* file, Date* d);/*A esta función pásaselle unha data e devolve unha estrutura cos datos recollidos dese día*/
float Consulta_precip_media(FILE* file, Date* d1, Date* d2); /*A esta función pásaselle dúas datas e devolve a precipitación media*/

                                    ///////////////*****MAIN*****///////////////
int main()
{
    FILE* ensaladillaRusa;

    SetConsoleTitle("GESTION DE DATOS 2.0 LAS NUBES S.A.");
    setlocale(LC_ALL,"Spanish");
    ensaladillaRusa=fopen("../../dtb/weatherdata-420-72.dat","rb");
    if(ensaladillaRusa==NULL)
    {
        wprintf(L"ERROR DE LECTURA\n¿Existe el directorio al que pretendes acceder?\n \n");
    }else
    {
        menuprincipal(ensaladillaRusa);
    }
    printf("\n");
    fclose(ensaladillaRusa);
   // fclose(tortillaPatatas);
    system("pause");
    return EXIT_SUCCESS;
}


                    ///////////////*****Definición de funciones*****//////////////

void menuprincipal(FILE* tallin)
{

    int isel1;
    char sel1,sel2;
    bool bsel1,bsel2;
    bool terminar=0;

    fijo = malloc(sizeof(Date));
    do
    {
        system("cls");
        wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
        wprintf(L"                  Bienvenido al nuevo programa de gestión de archivos del centro meteorológico LasNubes S.A. \n");
        wprintf(L"                  Actualmente solo se pueden realizar búsquedas.\n¿Desea realizar una consulta? (s/n):");
        do
        {
            scanf("%c",&sel1);

        }while(sel1!='s' && sel1!='n');
        if(sel1 =='s')bsel1=0;
        if(sel1 =='n')bsel1=1;
        if(bsel1==0)
        {
            do
            {
                system("cls");
                wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
                wprintf(L"              Bienvenido al panel de búsqueda. Desde aquí podrá seleccionar que tipo de búsqueda desea hacer.");
                wprintf(L"\n Actualmente hay dos tipos de búsqueda disponibles (Datos por fecha(1) y precipitación media (2))\nSelección: ");
                scanf("%i", &isel1);
            }while(isel1<0 || isel1>2);
            if (isel1 == 1) {
                bsel2 = 0;
            }
            if (isel1 == 2) {
                bsel2 = 1;
            }
            if (bsel2 == 0) {     //Búsqueda simple
                ler(&fecha2);//ver doc de la librería
                fijo->dia = 1;
                fijo->mes = 1;
                fijo->ano = 2000;
              //  free(Consulta_por_data(tallin, &fecha2));

                result = Consulta_por_data(tallin, &fecha2);
                system("cls");
                wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");//esta sección representa los datos recabados gracias a la función de
                wprintf(L"Fecha: %i / %i / %i", result->fecha.dia, result->fecha.mes, result->fecha.ano);
                wprintf(L"\n Longitud: %.12f", result->longitude);
                wprintf(L"\n Latitud: %.12f", result->latitude);
                wprintf(L"\n Elevación: %i", result->elevation);
                wprintf(L"\n Temperatura máxima: %.12lf", result->max_temperature);
                wprintf(L"\n Temperatura mínima: %.12lf", result->min_temperature);
                wprintf(L"\n Precipitación: %.12lf", result->precipitation);
                wprintf(L"\n Viento: %.12lf", result->wind);
                wprintf(L"\n Humedad relativa: %.12lf", result->relativeHumidity);
                wprintf(L"\n Radiación Solar: %.12lf", result->solar);
                printf("\n");
                free(result);
                system("pause");
                //continuar = 0;
            }
            if(bsel2==1)
            //búsqueda por precipitaciones
            {
                ler(&fecha1);//preguntar por la fecha(I)
                printf("\n\n");
                ler(&fecha2);//preguntar por la fecha(II)
                fijo->dia = 1;
                fijo->mes = 1;
                fijo->ano = 2000;
                system("cls");
                wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
                wprintf(L"La precipitación media entre las fechas introducidas es: %f",Consulta_precip_media(tallin, &fecha1, &fecha2));


            printf("\n");
            system("pause");
            }

        }
        if(bsel1==1)
        {

            terminar =1;
        }
    }while(terminar==0);


}



WeatherData* Consulta_por_data(FILE* file, Date* d)
{

    int empanadilla;//"índice"
            //WeatherData* resultados;
    WeatherData resultados[4018];
    WeatherData* resultado=(WeatherData*)malloc(sizeof(WeatherData));

    fread(resultados,sizeof(WeatherData),4018,file);//Error anterior depurado en 22/11/2021 :: No se detectaba como *;
    empanadilla= (int)CalcularDistancia(fijo,d);
            // return(resultados+empanadilla);
            // devuelve los datos meteorológicos;
    *resultado = resultados[empanadilla];
   return(resultado);//devuelve los datos meteorológicos;
}
float Consulta_precip_media(FILE* file, Date *d1, Date *d2)//WIP
{
    //
    float centolla,percebes;
    float media=0;
    float sel=0;
    bool SCANERR=FALSO;
    WeatherData muestra[4018];
    fread(&muestra,sizeof(WeatherData),4018,file);
    centolla= CalcularDistancia(fijo,d1);
    percebes= CalcularDistancia(fijo,d2);
    if(centolla!=percebes)
    {
        if(centolla<percebes){
            for(int i = (int)centolla;i<(int)percebes;i++)
            {
             media+=(float)muestra[i].precipitation;
             sel+=1;
            }
        }else if(centolla>percebes)
        {
            for(int i = (int)percebes;i<(int)centolla;i++)
            {
                media+=(float)muestra[i].precipitation;
                sel+=1;
            }
        }
        SCANERR=FALSO;
    }else if(centolla==percebes){
        wprintf(L"\nError, ha introducido la misma fecha 2 veces.\n");
        wprintf(L"\nPara hacer una búsqueda simple puede usar la herramienta de búsqueda por fecha.");
        SCANERR=VERDADERO;
    }
    if(!SCANERR)
    {
        media = media / sel;
        return media;
    }else
    {
        return 1;
    }
}
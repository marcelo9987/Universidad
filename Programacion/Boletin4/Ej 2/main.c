#define VERDADERO 1
#define FALSO     0
/*
 *  Programador: Marcelo Fort Muñoz
 *  Descripción: El ejercicio repite el ej9 pero con punteros.
 *  Fecha de inicio: 19/11/2021
 *      Hora de inicio: 9:20
 *  Fecha de finalización:
 *  Version: DEV.0.0.0
 *      Subversión: 0.0.2
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
                            ///////////////*****Declaración de funciones*****///////////////
void menuprincipal(FILE* tallin);
WeatherData Consulta_por_data(FILE* file, Date* d);/*A esta función pásaselle unha data e devolve unha estrutura cos datos recollidos dese día*/
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
    char atun;
    bool ensalada;
    bool terminar=0;
    do
    {
        wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
        wprintf(L"                  Bienvenido al nuevo programa de gestión de archivos del centro meteorológico LasNubes S.A. \n");
        wprintf(L"                  Actualmente solo se pueden realizar búsquedas.\n¿Desea realizar una consulta? (s/n):");
        do
        {
            wscanf(L"%c",atun);
        }while(atun!='s' && atun!='n');
        if(atun =='s')ensalada=0;
        if(atun =='n')ensalada=1;
        if(ensalada==0)
        {

        }
        if(ensalada==1)
        {
            terminar =1;
        }
    }while(terminar==0);


}
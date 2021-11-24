#define VERDADERO 1
#define FALSO     0
/*
 *  Programador: Marcelo Fort Muñoz
 *  Descripción: El ejercicio repite el ej9 pero con punteros.
 *  Fecha de inicio: 19/11/2021
 *      Hora de inicio: 9:20
 *  Fecha de finalización:24/11/2021
 *  Version: DEV.0.0.2
 *      Subversión: 0.1.1
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
}WeatherData;/*! Estructura con los campos del archivo, tiene dependencia del .h asociado */
WeatherData* result;
Date* fijo; /*!Es usado en ambas funciones, por lo que lo declaro de forma global y lo defino de forma local.(La definición está justo encima de cada uso. En un caso está declarada en la función y en el otro no)*/

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
/*!
 *
 * @param tallin  es el archivo que se maneja durante todo el programa
 */
void menuprincipal(FILE* tallin)//Función que gestiona las pantallas del programa
{

    int isel1; /*! Es responsable de la selección en términos del tipo de búsqueda */
    char sel1;/*! Determina si seguir adelante con la consulta */
    bool bsel1,bsel2; /*! Convierten los valores obtenidos a booleanos (Es más fácil comparar con variables tipo bool) */
    bool terminar=0; /*! Flag de inicio/fin del programa*/

    fijo = malloc(sizeof(Date));
    do
    {
        do
        {
            system("cls");
            wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
            wprintf(L"                  Bienvenido al nuevo programa de gestión de archivos del centro meteorológico LasNubes S.A. \n");
            wprintf(L"                  Actualmente solo se pueden realizar búsquedas.\n¿Desea realizar una consulta? (s/n):");

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


/*!
 * @brief Busca los datos meteorológicos partiendo de una fecha específica
 * @param file Este es el archivo que da el usuario o la función administradora de esta función
 * @param d Es la fecha a buscar
 * @return devuelve la estructura WeatherData de la función
 */
WeatherData* Consulta_por_data(FILE* file, Date* d)
{

    int empanadilla;//"índice"
            //WeatherData* resultados;
    //WeatherData resultados[4018];
    WeatherData* resultado=(WeatherData*)malloc(sizeof(WeatherData));
    empanadilla= (int)CalcularDistancia(fijo,d);
    fseek(file,(int)sizeof(WeatherData)*empanadilla,SEEK_SET);//Mejora introducida a 24/11/2021:: fseek
    fread(resultado,sizeof(WeatherData),1,file);//Error anterior depurado en 22/11/2021 :: No se detectaba como *;

            // return(resultados+empanadilla);
            // devuelve los datos meteorológicos;
   return(resultado);//devuelve los datos meteorológicos;
}

/*!
 * @brief Calcula el promedio de precipitación entre dos fechas
 * @param file "same as" Consulta_por_data
 * @param d1 En esta función cambia un poco. En este caso es la primera / última fecha a "sumar"
 * @param d2 ídem d1
 * @return devuelve la media
 * @retval 0 Esto ocurre cuando el programa detecta que se ha introducido la misma fecha dos veces, lo que no tiene sentido
 */
float Consulta_precip_media(FILE* file, Date *d1, Date *d2)//WIP
{
    //
    float centolla,percebes;
    int ostra;
    float media=0;
    float sel=0;
    bool SCANERR=FALSO;
    WeatherData* muestra;
    centolla= CalcularDistancia(fijo,d1);
    percebes= CalcularDistancia(fijo,d2);
    ostra=abs((int)(percebes-centolla))+1;
    muestra= (WeatherData *)malloc(ostra*sizeof(WeatherData));
    fseek(file,sizeof(WeatherData )*centolla,SEEK_SET);
    fread(muestra,sizeof(WeatherData),ostra,file);

    if(centolla!=percebes)
    {
        if(centolla!=percebes){
            for(int i = 0;i<(int)ostra;i++)
            {
             media+=(float) (muestra+i)->precipitation;
             sel+=1;
            }
        }
        SCANERR=FALSO;
        free(muestra);
    }else if(centolla==percebes){
        wprintf(L"\nError, ha introducido la misma fecha 2 veces.\n");
        wprintf(L"\nPara hacer una búsqueda simple puede usar la herramienta de búsqueda por fecha.\n");
        SCANERR=VERDADERO;
        system("pause");
    }
    if(!SCANERR)
    {
        media = media / sel;
        return media;
    }else
    {
        return 0;
    }
}
//PROGRAMA FINALIZADO Y DEPURADO.
/*
 * POSIBLES PUNTOS PROBLEMÁTICOS:
 *          1. Búsqueda por fecha
 *          2. Depuración(poco probable)
 *          3.
 *          4.
 *
 */
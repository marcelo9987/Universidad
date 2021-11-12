
/*
 * EJ 9 FINALIZACIÓN DEL BOLETÍN 3:
 *  Programador: Marcelo Fort Muñoz
 *  Licencia: MIT
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fechas.h"
//---------------Variables & Estructuras---------------//
int numdbus;//esta es la fecha seleccionada por el usuario(podría ser local, pero para que complicarnos)
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
WeatherData result;
Date fijo; //ídem L11 ↓
//---------------funciones---------------//
void MenuPrincipal(FILE* archivo);
WeatherData Consulta_por_data(FILE* file, Date d);//Ver boletín de ejs
float Consulta_precip_media(FILE* file, Date d1, Date d2);//ídem L25
//---------------MAIN---------------//
int main()
{

    setlocale(LC_ALL,"Spanish");
    FILE* dtb;//un archivo normal y corriente... nada que mirar aquí :)
    dtb=fopen("../../dtb/weatherdata-420-72.dat","rb");
    if(dtb!=NULL)
    {
        MenuPrincipal(dtb);
    }else
    {
     wprintf(L"ERROR DE LECTURA\n¿Existe el directorio al que pretendes acceder?\n \n");
    }
    wprintf(L"\n");
    system("pause");
    return 0;
}




//---------------DEFINICIÓN DE FUNCIONES---------------//
void MenuPrincipal(FILE* archivo)//Esta función hace de "telonero" en el programa, maneja todo el flujo de datos y funciones.Siendo así la más importante del programa
{
    bool entrada_usuario=0,continuar=1;
    char conv='a';
    int sel=-3;
    while(continuar==1) {
        do {
            system("cls");
            wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
            wprintf(L"                  Bienvenido al programa de gestión de archivos del centro meteorológico LasNubes S.A. \n");
            wprintf(L"                  Actualmente solo se pueden realizar búsquedas.\n¿Desea realizar una consulta? (s/n):");
            scanf("%c", &conv);
        } while (conv != 's' &&
                 conv != 'n');//PRIMERA ENTRADA DE DECISIÓN(y-->1--> Seguir programa // n -->0-->Salir del programa)
        if (conv == 's') {
            entrada_usuario = 1;
        } else if (conv == 'n') {
            entrada_usuario = 0;
            continuar = 0;
        }
        if (entrada_usuario == 1) //menú de búsqueda
        {
            system("cls");
            wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
            wprintf(L"              Bienvenido al panel de búsqueda. Desde aquí podrá seleccionar que tipo de búsqueda desea hacer.");
            wprintf(L"\n Actualmente hay dos tipos de búsqueda disponibles (Datos por fecha(1) y precipitación media (2))\nSelección: ");
            wscanf(L"%i", &sel);//es como "scanf", pero reporta errores de conversión
            if (sel == 1) {    //segunda selección
                entrada_usuario = 0;
            }
            if (sel == 2) {
                entrada_usuario = 1;
            }
            if (entrada_usuario == 0) {     //Búsqueda simple
                ler(&fecha2);//ver doc de la librería
                fijo.dia = 1;
                fijo.mes = 1;
                fijo.ano = 2000;

                result = Consulta_por_data(archivo, fecha2);
                system("cls");
                wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");//esta sección representa los datos recabados gracias a la función de
                wprintf(L"Fecha: %i / %i / %i", result.fecha.dia, result.fecha.mes, result.fecha.ano);
                wprintf(L"\n Longitud: %.12f", result.longitude);
                wprintf(L"\n Latitud: %.12f", result.latitude);
                wprintf(L"\n Elevación: %i", result.elevation);
                wprintf(L"\n Temperatura máxima: %.12lf", result.max_temperature);
                wprintf(L"\n Temperatura mínima: %.12lf", result.min_temperature);
                wprintf(L"\n Precipitación: %.12lf", result.precipitation);
                wprintf(L"\n Viento: %.12lf", result.wind);
                wprintf(L"\n Humedad relativa: %.12lf", result.relativeHumidity);
                wprintf(L"\n Radiación Solar: %.12lf", result.solar);
                system("pause");
                //continuar = 0;
            }
            if (entrada_usuario == 1) { //Búsqueda por precipitaciones
                wprintf(L"                                  Gallega de meteorología LAS NUBES S.A. \n");
                ler(&fecha1);
                ler(&fecha2);
                fijo.dia = 1;
                fijo.mes = 1;
                fijo.ano = 2000;
                wprintf(L"La precipitación media de las fechas introducidas es: %f",
                        Consulta_precip_media(archivo, fecha1, fecha2));
                //continuar = 0;
            }
        }
    }


        wprintf(L"\n Operación finalizada con éxito, puede cerrar el programa");

    //system("cls");

}
WeatherData Consulta_por_data(FILE* file, Date d)//Ver Bol. de ejs.
{

    WeatherData resultados[4018];
    file=fopen("../../dtb/weatherdata-420-72.dat","rb");
    numdbus = (int) CalcularDistancia(&fijo, &d);//ídem l10
    fread(&resultados,sizeof(WeatherData),4018,file);
    return resultados[numdbus];
}

float Consulta_precip_media(FILE* file, Date d1, Date d2)
{
    //La función ha de acceder a las fechas posicionadas entre %fecha1% y %fecha2%, sumar todos los .precipitations y después hacer una división de estos entre el número de entradas
    float entrada1,entrada2;
    float media =0;
    float  sel=0;
    WeatherData muestra[4018];
    file=fopen("../../dtb/weatherdata-420-72.dat","rb");
    fread(&muestra,sizeof(WeatherData),4018,file);
    entrada1= CalcularDistancia(&fijo,&d1);
    entrada2= CalcularDistancia(&fijo,&d2);
    wprintf(L" PRUEBA %.f //// %.f",entrada1,entrada2);

    for (int i = (int)entrada1;i!=(int)entrada2+1;i++)
    {
        wprintf(L"\n ENTRADA: %.10f",(float) muestra[i].precipitation);
        media+=(float)muestra[i].precipitation;
        sel+=1;
    }
    media=media/sel;
    return media;
}//Y he aquí el final del maravilloso boletín 3. :)
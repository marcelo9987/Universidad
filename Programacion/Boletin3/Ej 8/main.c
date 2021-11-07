#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#define VERDADERO 1
#define FALSO 0
////////////////////////////////////////////////////////////////////////////////////////////////////////
bool primeraVuelta = VERDADERO;
/*-------------------------------*/
typedef struct
{
    int dia;
    int mes;
    int ano;
}Date;

typedef struct
{
    Date fecha;
    int longitude;
    int latitude;
    int elevation;
    int max_temperature;
    int min_temperatura;
    int precipitation;
    int wind;
    int relativeHumidity;
    int solar;
}WeatherData;

///////////////////////////////-----------FUNCIONES----------////////////////////////////////
void reestructurar(char ent[],WeatherData estructura);
//////////////////////////////--------------MAIN------------////////////////////////////////
WeatherData s;
int main()
{

    char entrada[200];
    FILE* csv;
    FILE* texto;
    csv= fopen("weatherdata-420-72.csv","r");
    texto= fopen("weatherdata-420-72.dat","wb");
    if(csv==NULL)
    {
        printf("ERROR DE LECTURA");
    }else
    {
        do
        {

            if(primeraVuelta==VERDADERO)
            {
                fgets(entrada,200,csv);
                primeraVuelta = FALSO;
            }


        }while(feof(csv));
        printf("LECTURA CORRECTA");

    }
    char w[6]={"abcde"};
    reestructurar(w,s);
    printf("\n");
    system("pause");
    return 0;
}

void reestructurar(char ent[],WeatherData estructura)
{
    int longit =strlen(ent);
    int pasada=0;
    char nombre[7];
    bool grab = FALSO;//en grabación
    for(int i = 0; i<longit;i++)
    {
        if(ent[i]=',')
        {

        }else if(ent[i]=='"')
        {pasada +=1;
            grab=!grab;
        }else if(grab==VERDADERO)
        {
            switch(pasada)
            {
                case 1:
                    int d,m,a;
                    if(ent[i]!='/')
                    {
                      //  if(d!)
                    }
                    estructura.fecha.dia=;
                    estructura.fecha.mes=;
                    estructura.fecha.ano=;

                    break;

            }

        }
    }
}
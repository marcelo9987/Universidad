#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#define VERDADERO 1
#define FALSO 0
//#define R 2 //posición de lectura para pruebas internas(Ignorar en fase de evaluación)
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
///////////////////////////////-----------VARIABLES(globales)-----------///////////////////////////////
WeatherData s[4018]; //estructura de datos

///////////////////////////////-----------FUNCIONES----------////////////////////////////////
/*void reestructurar(char ent[200],WeatherData *estructura); // NO IMPLEMENTADO/OBSOLETO
int elevar(int num,int potencia);*/ //NO IMPLEMENTADO/OBSOLETO

void leer(WeatherData estructura[],FILE* rea);//función que asigna valores a las estructuras(valores de entrada: ARCHIVO(*) y ESTRUCTURA WEATHERDATA)

//////////////////////////////--------------MAIN------------////////////////////////////////

int main()
{
    FILE* csv;
    FILE* texto;
    csv= fopen("../../dtb/weatherdata-420-72.csv","r"); //inicialización archivo
    texto= fopen("../../dtb/weatherdata-420-72.dat","wb"); //inicialización archivo
    if(csv==NULL)
    {
        wprintf(L"ERROR DE LECTURA\n ¿Existe el directorio/archivo al que desea acceder?\n");
    }else
    {
        printf("LECTURA CORRECTA \n");
        leer(s,csv);
        
    }

    fwrite(&s,sizeof(WeatherData),4018,texto);//escribe en el binario todos los elementos del vector de structs

    fclose(csv);
    fclose(texto);
    system("pause");
    return 0;
}

////////////////////////////////-----------------ESPECIFICACIÓN DE FUNCIONES(GLOBALES)-----------------////////////////////////////////-
void leer(WeatherData estructura[],FILE* rea)
{
    char entrada[200];//desecha la primera entrada
    primeraVuelta=VERDADERO;
    rea= fopen("../../dtb/weatherdata-420-72.csv","r");
    for(int i = 0;i<4018;i++) {

            if (primeraVuelta == VERDADERO)//descarta la primera línea
            {
                fgets(entrada, 130, rea);
                primeraVuelta = FALSO;
            }
            getc(rea);
            fscanf(rea, "%i[^/]", &estructura[i].fecha.dia);
            getc(rea);
            fscanf(rea, "%i[^/]", &estructura[i].fecha.mes);
            getc(rea);
            fscanf(rea, "%i", &estructura[i].fecha.ano);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%f", &estructura[i].longitude);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%f", &estructura[i].latitude);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%i", &estructura[i].elevation);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%lf", &estructura[i].max_temperature);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%lf", &estructura[i].min_temperature);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%lf", &estructura[i].precipitation);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%lf", &estructura[i].wind);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%lf", &estructura[i].relativeHumidity);
            getc(rea);
            getc(rea);
            getc(rea);
            fscanf(rea, "%lf", &estructura[i].solar);
            getc(rea);
            getc(rea);
            getc(rea);


    }
}


























/*
int elevar(int num,int potencia)//NO IMPLEMENTADO/OBSOLETO
{
    int salida=1;
    if(potencia==0)
    {
        salida=1;
    }else
    {
        salida = 1;
        for(int i = 0; i<potencia;i++)
        {
             salida = salida*num;
        }
    }
    return salida;
}

void reestructurar(char ent[200],WeatherData *estructura)//NO IMPLEMENTADO/OBSOLETO
{

    int longit = strlen(ent);
    int numero,numero2,numero3,numero4;
    int pasada=0;
    int vueltasen2=0;
    int pas = 0;
    int r =1;
    bool grab = FALSO;//en grabación
    for(int i = 0; i<longit;i++) {

        if (ent[i] == ',')
        {

        } else if (ent[i] == '"')
        {
            pasada += 1;
            grab = !grab;
        } else if (grab == VERDADERO)
        {
            switch (pasada)
            {

                case 1:
                    if (ent[i] == '/')
                    {
                        r+=1;
                       pas =0;
                    }else if((ent[i] != '/' && ent[i+1]!= '/') || ((ent[i-1]=='"' || ent[i-1]=='/')  && ent[i]!='/' && ent[i+1]=='/'))
                    {
                    switch (r) {

                        case 1:
                            numero = ent[i] - 48;
                           if(ent[i+1]!='/')
                            {
                                numero2 = ent[i + 1] - 48;
                            }
                           // printf("\n %i", numero);
                           // printf("\n %i", numero2);
                            if(ent[i+1]!='/')
                            {
                                estructura->fecha.dia += numero2 * elevar(10, pas);
                                pas += 1;
                            }

                            estructura->fecha.dia += numero * elevar(10, pas);
                        //    printf("\n %i \n", s.fecha.dia);
                        //    system("pause");
                            //r += 1;
                            break;

                        case 2:
                            numero = ent[i] - 48;
                            if(ent[i+1]!='/')
                            {
                                numero2 = ent[i + 1] - 48;
                            }
                            //printf("\n %i", numero);
                           // printf("\n %c", ent[i+1]);
                            if(ent[i+1]!='/')
                            {
                                estructura->fecha.mes += numero2 * elevar(10, pas);
                                pas += 1;
                            }
                            estructura->fecha.mes += numero * elevar(10, pas);
                           // printf("\n %i \n", s.fecha.mes);
                           // system("pause");
                            //r += 1;
                            break;

                        case 3:

                        //          system("cls");
                                numero = ent[i] - 48;
                                numero2 = ent[i + 1] - 48;
                                numero3 = ent[i + 2] - 48;
                                numero4 = ent[i + 3] - 48;
                        //        printf("Num1: %i",numero);
                        //        printf("Num2: %i",numero2);
                        //        printf("Num3: %i",numero3);
                        //        printf("Num4: %i",numero4);
                        //        system("pause");
                                estructura->fecha.ano += numero4 * elevar(10, pas);
                                pas += 1;
                                estructura->fecha.ano += numero3 * elevar(10, pas);
                                pas += 1;
                                estructura->fecha.ano += numero2 * elevar(10, pas);
                                pas += 1;
                                estructura->fecha.ano += numero * elevar(10, pas);
                                r += 1;

                            break;


                        default:
                            // printf("\n NULO \n");
                            break;

                    }


                    break;

                }
                case 2:
                    vueltasen2=0;
                    if(ent[i]=='-')
                    {
                        numero*=-1;
                    }else
                    {
                        numero+=  ent[i];
                    }


            }
        }
    }
}*/
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
///////////////////////////////-----------VARIABLES-----------///////////////////////////////
WeatherData s;
char entrada[200];
///////////////////////////////-----------FUNCIONES----------////////////////////////////////
/*void reestructurar(char ent[200],WeatherData *estructura);
int elevar(int num,int potencia);*/
//////////////////////////////--------------MAIN------------////////////////////////////////

int main()
{

    char r;
    FILE* csv;
    FILE* texto;
    csv= fopen("weatherdata-420-72.csv","r");
    texto= fopen("weatherdata-420-72.dat","wb");
    if(csv==NULL)
    {
        printf("ERROR DE LECTURA");
    }else
    {
        int i = 0;
        do
        {
            i+=1;

            if(primeraVuelta==VERDADERO)
            {
                fgets(entrada,200,csv);
                primeraVuelta = FALSO;
                getc(csv);
                //getc(csv);
            }
            //

            fscanf(csv,"%i[^/]",&s.fecha.dia);
            getc(csv);
            fscanf(csv,"%i[^/]",&s.fecha.mes);
            getc(csv);
            fscanf(csv,"%i",&s.fecha.ano);
            getc(csv);
            getc(csv);
            getc(csv);
            fscanf(csv,"%i[^.]",&s.longitude);
            getc(csv);

        }while(primeraVuelta==TRUE);
        printf("LECTURA CORRECTA \n");

    }

    //char w[6]={"abcde"};
    //printf("%s",entrada);
    system("pause");
    //reestructurar(entrada,&s);
                                    system("cls");
                                    printf("\nFECHA: %i",s.fecha.dia);
                                    printf(" // %i",s.fecha.mes);
                                    printf(" // %i",s.fecha.ano);
                                    printf("\n Longitud %i"),s.longitude;
    printf("\n");
    system("pause");
    return 0;
}
/*
int elevar(int num,int potencia)
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

void reestructurar(char ent[200],WeatherData *estructura)
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
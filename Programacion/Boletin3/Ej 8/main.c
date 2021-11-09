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
void reestructurar(char ent[200],WeatherData estructura);
int elevar(int num,int potencia);
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

            fgets(entrada,200,csv);

        }while(!feof(csv));
        printf("LECTURA CORRECTA");

    }
    //char w[6]={"abcde"};
    printf("%s",entrada);
    system("pause");
    reestructurar(entrada,s);
                                    system("cls");
                                    printf("\nFECHA: %i",s.fecha.dia);
                                    printf(" // %i",s.fecha.mes);
    printf("\n");
    system("pause");
    return 0;
}

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

void reestructurar(char ent[200],WeatherData estructura)
{
    int longit = 200;//strlen(ent);
    int numero,numero2;
    int pasada=0;
    int pas = 0;
    int r =1;
    bool grab = FALSO;//en grabación
    for(int i = 0; i<longit;i++) {

        if (ent[i] == ',')
        {

        } else if (ent[i] == '"') {
            pasada += 1;
            grab = !grab;
        } else if (grab == VERDADERO) {
            char d[2], m[2], a[2];
            switch (pasada) {
                case 1:
                    if (ent[i] == '/')
                    {
                        r+=1;
                       pas =0;
                    }else if(ent[i] != '/' && ent[i+1]!= '/')
                    {

                    switch (r) {

                        case 1:


                            numero = ent[i] - 48;
                            numero2 = ent[i + 1] - 48;

                            printf("\n %i", numero);
                            printf("\n %i", numero2);
                            s.fecha.dia += numero2 * elevar(10, pas);
                            pas += 1;
                            s.fecha.dia += numero * elevar(10, pas);
                            printf("\n %i \n", s.fecha.dia);
                            system("pause");
                            //r += 1;
                            break;

                        case 2:
                            numero = ent[i] - 48;
                            numero2 = ent[i + 1] - 48;
                            printf("\n %i", numero);
                            printf("\n %c", ent[i+1]);
                            s.fecha.mes += numero2 * elevar(10, pas);
                            pas += 1;
                            s.fecha.mes += numero * elevar(10, pas);
                            printf("\n %i \n", s.fecha.mes);
                            system("pause");
                            //r += 1;
                            break;

                        default:
                            // printf("\n NULO \n");
                            break;

                    }


                    break;

            }
            }
        }
    }
}
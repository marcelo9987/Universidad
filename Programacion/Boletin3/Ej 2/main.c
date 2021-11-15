#define VERDADERO           1
#define FALSO               0
#define EJ_SATISFACTORIA    0
/////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <locale.h>
/////////////////////////////
struct mes
{
    bool febBis;
    int dias;
    int diasFeb;
};

struct mes ano[12];
/////////////////////////////
bool esBisiesto(int a1);//determina si el año es bisiesto
int determinacion(bool sino,int dia,int mes,struct mes abc[12]);
/////////////////////////////
int main()
{
    int dia,mes,anro;
    ano[0].dias = 31;
    ano[1].dias = 28;
    ano[2].dias = 31;
    ano[3].dias = 30;
    ano[4].dias = 31;
    ano[5].dias = 30;
    ano[6].dias = 31;
    ano[7].dias = 31;
    ano[8].dias = 30;
    ano[9].dias = 31;
    ano[10].dias= 30;
    ano[11].dias = 31;
    ano->diasFeb=29;
    ////
    setlocale(LC_ALL,"SPANISH");
    //////// INICIO INTERACCIÓN CON USUARIO (ENTRADA)
    system("cls");
    do
    {
        wprintf(L"Introduzca el día(dd):");
        scanf("%d", &dia);
    }while(dia>30||dia<1);
    do
    {
        wprintf(L"\nIntroduzca el mes(mm):");
        scanf("%d", &mes);
    }while(mes>12||mes<1);
    do
    {
        wprintf(L"\nIntroduzca el año(aa):");
        scanf("%d", &anro);
    }while(anro<1);
    //////// FIN INTERACCIÓN CON USUARIO (ENTRADA)
    wprintf(L"\nEs el día: %i \n",determinacion(esBisiesto(anro),dia,mes,ano));
    system("pause");
    return EJ_SATISFACTORIA;
}
bool esBisiesto(int a1)
{
    bool bisiesto = FALSO;
    if((a1%4==0)&&(a1%100 != 0))
    {
        bisiesto = VERDADERO;
    }
    else if(a1%100 == 0)
    {
        if(a1%400 ==0)
        {
            bisiesto = VERDADERO;
        }
    }
    return bisiesto;
}
int determinacion(bool sino, int dia, int mes,struct mes abc[12]){
    int b = 0;

    //
   // printf("%i :mes %i:dias %i",dia,mes,abc->dias);
   // system("pause");
///

    if (sino == VERDADERO)
    {
        abc[1].febBis = VERDADERO;
    }else if(sino == FALSO)
    {
        abc[1].febBis=FALSO;
    }
    for(int i =0;i<mes-1;i++)
    {

        if(i==1)
        {
            if(abc[1].febBis)
            {
                b += 29;
            }else if(abc[1].febBis==0)
            {
                b+=28;
            }
        }else
        {
            b += abc[i].dias;
        }
    }



    b+= dia;
    return b;
}
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
/////////////////////////////
bool esBisiesto(int a1);
int determinacion(bool sino,int dia,int mes,struct mes abc[12]);
/////////////////////////////
int main()
{
    int dia,mes,anro;
    struct mes ano[12];
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
    ////
    setlocale(LC_ALL,"SPANISH");
    //////// INICIO INTERACCIÓN CON USUARIO (ENTRADA)
    wprintf(L"Introduzca el día(dd):");
    scanf("%d",&dia);
    wprintf(L"\nIntroduzca el mes(mm):");
    scanf("%d",&mes);
    wprintf(L"\nIntroduzca el año(aa):");
    scanf("%d",&anro);
    //////// FIN INTERACCIÓN CON USUARIO (ENTRADA)
    wprintf(L"\nEs el día: %d",determinacion(esBisiesto(anro),dia,mes,ano));
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
    if (sino == VERDADERO)
    {
        abc[1].febBis = VERDADERO;
        return b;
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
                b += abc[1].diasFeb;
            }else if(!abc[1].febBis)
            {
                b+=abc[1].dias;
            }
        }else
        {
            b += abc[i].dias;
        }
    }
    b+= dia;
    return b;
}
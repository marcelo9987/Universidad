/*
 * Programador: Marcelo Fort Muñoz
 * Descripción: Pide dos fechas,
 */
#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include <locale.h>
//#include <bis.h>



  struct mes2
    {
    int dias;
    };

struct mes2 pipeta[12];

typedef struct
{
    int dia;
    int mes;
    int ano;
}Date;

void ler(/*Date fechaf*/Date *fechaf);
void Mostrar (Date fechaf, char f);
float CalcularDistancia (Date* d1, Date* d2);
//bool esBisiesto(int a1);

int main() {

    pipeta[0].dias = 31;
    pipeta[1].dias = 28;
    pipeta[2].dias = 31;
    pipeta[3].dias = 30;
    pipeta[4].dias = 31;
    pipeta[5].dias = 30;
    pipeta[6].dias = 31;
    pipeta[7].dias = 31;
    pipeta[8].dias = 30;
    pipeta[9].dias = 31;
    pipeta[10].dias= 30;
    pipeta[11].dias = 31;

    setlocale(LC_ALL,"Spanish");
    Date fecha1;
    Date *vec1=&fecha1;
    Date fecha2;
    Date *vec2=&fecha2;
    printf("---------------- FECHA 1 ----------------\n");
    ler(vec1);
    printf("\n---------------- FECHA 2 ----------------\n");
    ler(vec2);
    printf("\nLa fecha 1 es : ");
    Mostrar(fecha1,'1');
    printf("\nLa fecha 2 es : ");
    Mostrar(fecha2,'1');
    printf("\n %f ",CalcularDistancia(&fecha1, vec2));

    system("pause");
    return 0;
}
void ler(Date *fechaf)
{
    Date entrada;
    printf("Introduzca el dia: ");
    scanf(" %i", &entrada.dia);
    printf("\nIntroduzca el mes: ");
    scanf(" %i", &entrada.mes);
    wprintf(L"\nIntroduzca el año: ");
    scanf( "%i", &entrada.ano);
    *fechaf = entrada;

}


void Mostrar (Date fechaf, char f)
{
    switch(f)
    {
        case '1':
            wprintf(L"\n Dia: %i",fechaf.dia);
            wprintf(L" Mes: %i",fechaf.mes);
            wprintf(L" Año %i",fechaf.ano);
            break;
        case '2':
            wprintf(L"\n Mes/Dia/Año: %i %i %i",fechaf.mes,fechaf.dia,fechaf.ano);
            break;
        default:
            break;
    }


}


float CalcularDistancia (Date* d1, Date* d2)
{
    Date nd1;
    nd1= (*d1);
    Date nd2;
    nd2 = (*d2);
    nd1.ano -= 1;
    nd2.ano -= 1;
    int diasan,diames,/*dias,*/tot;
    int mes1=0,mes2=0;//,mes2;
   diasan = (((nd1.ano-nd1.ano/4)*365+(nd1.ano/4)*366)-((nd2.ano-nd2.ano/4)*365+(nd2.ano/4)*366));
    nd1.ano += 1;
    nd2.ano += 1;
    for(int i = 0;i<nd1.mes-1;i++)
    {

        if(i==1 && ( (nd1.ano%4==0 && nd1.ano%100!=0) || (nd1.ano%4==0 && nd1.ano%100==0 && nd1.ano%400==0) ) )
        {
            mes1 +=29;
        }else if(i==1)
        {
            mes1 +=28;
        }else
        {
            mes1 += pipeta[i].dias;
        }
    }

    for(int h = 0;h<nd2.mes-1;h++)
    {

        if(h==1 && nd2.ano%4==0 && nd2.ano%10!=0)
        {
            mes2 +=29;
        }else if(h==1)
        {
            mes2 +=28;
        }else
        {
            mes2 += pipeta[h].dias;
        }
    }
    diames=mes1-mes2;
   int dias=nd1.dia-nd2.dia;
    tot=diasan+diames+dias;

   // printf("DIas mes %i",d1.mes);


 return (float)tot;
}
/*
bool esBisiesto(int a1)
{
    bool bisiesto = 0;
    if((a1%4==0)&&(a1%100 != 0))
    {
        bisiesto = 1;
    }
    else if(a1%100 == 0)
    {
        if(a1%400 ==0)
        {
            bisiesto = 1;
        }
    }
    return bisiesto;
}*/
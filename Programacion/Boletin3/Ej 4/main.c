#define ESTILO '1' //dia mes año
/*
 * Programador: Marcelo Fort Muñoz
 * Descripción: Calcula la distancia (en días) entre dos fechas y su formato se puede poner a modo anglosajón o europeo
 */
#include <stdio.h>
#include<stdlib.h>
#include <locale.h>
//#include <bis.h>
//#include<stdbool.h>



  struct mes2
    {
    int dias;
    };

struct mes2 pipeta[12];//necesita ser global porque se accede a ella desde varias funciones

typedef struct
{
    int dia;
    int mes;
    int ano;
}Date;

Date Ler()
{

    Date entrada;
    do
    {
        printf("Introduzca el dia: ");
        scanf(" %i", &entrada.dia);
    }while(entrada.dia>31 || entrada.dia<0);

    do
    {
        printf("\nIntroduzca el mes: ");
        scanf(" %i", &entrada.mes);
    }while(entrada.mes>12 || entrada.mes<0);

    do
    {
        wprintf(L"\nIntroduzca el año: ");
        scanf("%i", &entrada.ano);
    }while(entrada.ano<0);
    return entrada;
}
void Mostrar (Date fechaf, char f[]);
float CalcularDistancia (Date d1, Date d2);





int main() {
    Date fecha1;
    Date fecha2;
    char est[1];
    est[0]=ESTILO;

    pipeta[0].dias = 31;  //aquí se describen cuantos dias tiene cada mes
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

    printf("---------------- FECHA 1 ----------------\n");
    fecha1=Ler();
    printf("\n---------------- FECHA 2 ----------------\n");
    fecha2=Ler();
    printf("\nLa fecha 1 es: ");
    Mostrar(fecha1,est);
    printf("\nLa fecha 2 es: ");
    Mostrar(fecha2,est);
    printf("\n %f ",CalcularDistancia(fecha1, fecha2));
    printf("\n");
    system("pause");
    return 0;
}

void Mostrar (Date fechaf, char f[])
{
    switch(f[0])
    {
        case '1':
            wprintf(L"\n Dia/Mes/Año: %i %i %i",fechaf.dia,fechaf.mes,fechaf.ano);
            break;
        case '2':
            wprintf(L"\n Mes/Dia/Año: %i %i %i",fechaf.mes,fechaf.dia,fechaf.ano);
            break;
        default:
            break;
    }
}

float CalcularDistancia (Date d1, Date d2)
{
    Date nd1;
    nd1= d1;
    Date nd2;
    nd2 = d2;
    nd1.ano -= 1;
    nd2.ano -= 1;
    int diasan,diames,/*dias,*/tot;
    int mes1=0,mes2=0;//,mes2;
   diasan = (((nd1.ano-nd1.ano/4)*365+(nd1.ano/4)*366)-((nd2.ano-nd2.ano/4)*365+(nd2.ano/4)*366)); //usa una fórmula para calcular los días en años normales más años bisiestos
    nd1.ano += 1;
    nd2.ano += 1;
    for(int i = 0;i<nd1.mes-1;i++) //suma los dias de los meses
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
    tot=diasan+diames+dias;//puesta en común

    tot=abs(tot); //eliminación del signo
 return (float)tot;
}

#include "fechas.h"
#include <stdio.h>//wscanf,fscanf,scanf,printf...
#include <stdlib.h>
#include <locale.h>//poner letras no standard


void ler(Date *fechaf) {
    Date entrada;
    setlocale(LC_ALL, "Spanish");
    do {
        printf("Introduzca el dia: ");
        scanf(" %i", &entrada.dia);
    } while (entrada.dia > 31 || entrada.dia < 0);
    do {
        printf("\nIntroduzca el mes: ");
        scanf(" %i", &entrada.mes);
    } while (entrada.mes > 12 || entrada.mes < 0);
    do {
        wprintf(L"\nIntroduzca el año: ");
        scanf("%i", &entrada.ano);
    } while (entrada.ano > 2010 || entrada.ano < 2000);

    *fechaf = entrada;

}


void Mostrar(Date fechaf, char f) {
    setlocale(LC_ALL, "Spanish");
    switch (f) {
        case '1':
            wprintf(L"\n Dia/Mes/Año: %i %i %i", fechaf.dia, fechaf.mes, fechaf.ano);
            break;
        case '2':
            wprintf(L"\n Mes/Dia/Año: %i %i %i", fechaf.mes, fechaf.dia, fechaf.ano);
            break;
        default:
            break;
    }


}


float CalcularDistancia(Date *desde, Date *hasta) {
    setlocale(LC_ALL, "Spanish");
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
    pipeta[10].dias = 30;
    pipeta[11].dias = 31;

    Date desde_local;
    desde_local = (*desde);
    Date hasta_local;
    hasta_local = (*hasta);
    desde_local.ano -= 1;
    hasta_local.ano -= 1;
    int diasan, diames,/*dias,*/tot;
    int dias_desde = 0, dias_hasta = 0;//,dias_hasta;
    diasan = (((desde_local.ano - desde_local.ano / 4) * 365 + (desde_local.ano / 4) * 366) - ((hasta_local.ano - hasta_local.ano / 4) * 365 + (hasta_local.ano / 4) *
                                                                                                                                               366)); //usa una fórmula para calcular los días en años normales más años bisiestos
    desde_local.ano += 1;
    hasta_local.ano += 1;
    for (int mes = 0; mes < desde_local.mes - 1; mes++) //suma los dias de los meses
    {

        if (mes == 1 && ((desde_local.ano % 4 == 0 && desde_local.ano % 100 != 0) ||
                         (desde_local.ano % 4 == 0 && desde_local.ano % 100 == 0 && desde_local.ano % 400 == 0))) {
            dias_desde += 29;
        } else if (mes == 1) {
            dias_desde += 28;
        } else {
            dias_desde += pipeta[mes].dias;
        }
    }

    for (int mes = 0; mes < hasta_local.mes - 1; mes++) {

      //  if (mes == 1 && hasta_local.ano % 4 == 0 && hasta_local.ano % 10 != 0) {
        if (mes == 1 && ((hasta_local.ano % 4 == 0 && hasta_local.ano % 100 != 0) ||
           (hasta_local.ano % 4 == 0 && hasta_local.ano % 100 == 0 && hasta_local.ano % 400 == 0))) {
            dias_hasta += 29;
        } else if (mes == 1) {
            dias_hasta += 28;
        } else {
            dias_hasta += pipeta[mes].dias;
        }
    }
    diames = dias_desde - dias_hasta;
    int dias = desde_local.dia - hasta_local.dia;
    tot = diasan + diames + dias;//puesta en común

    // printf("DIas mes %i",d1.mes);

    tot = abs(tot); //eliminación del signo
    return (float) tot;
}

#include "meteo.h"
#include <stdio.h>

bool esBisiesto(int ano)
{//idc
    if (ano % 4 == 0 && ano % 100 != 0)
    {
        return 1;
    }else if(ano%4==0 && ano%100==0 && ano%400==0)
    {
        return 1;
    }else
    {
        return 0;
    }// fdc
}




/*
 * Se define la siguiente nomenclatura:
 * fdc: fin de declaración
 * idc: inicio de declaración
 */
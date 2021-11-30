////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Programador: Marcelo Fort Muñoz
 *  Licencia: MIT
 */

#pragma once
#define ESTILO '1' //dia mes año

struct mes2{
    int dias;
};

struct mes2 pipeta[12];//Contiene los días que tiene cada més

typedef struct {
    int dia;
    int mes;
    int ano;
} Date;

void ler(/*Date fechaf*/Date *fechaf);//pide 2 fechas
void Mostrar(Date fechaf, char f);//muestra 2 fechas
float CalcularDistancia(Date *d1, Date *hasta); //calcula la distancia (en días) entre dos fechas
/*
Date fecha1;
Date *vec1 = &fecha1;
Date fecha2;
Date *vec2 = &fecha2;
*/

//fin del archivo
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#include "./vacunodromo.h"
//TODO ¿Puedo usar vacunodromo.h?
//#error .

#include "./TAD/cola.h"

#define MAX_NOMBREVACUNODROMO_LEN 40

typedef struct
{
    char nombreVacunodromo[MAX_NOMBREVACUNODROMO_LEN];
    int numPacientesCola;
    TCOLA pacientes;
} VACUNODROMO;

typedef VACUNODROMO* PVACUNODROMO;


void crear_vacunodromo(PVACUNODROMO* vacunodromo, char nombreVacunodromo[])
{
    * vacunodromo = (PVACUNODROMO) malloc(sizeof(VACUNODROMO));

    strcpy((* vacunodromo)->nombreVacunodromo, nombreVacunodromo);
    (* vacunodromo)->numPacientesCola = 0;
    crearCola((* vacunodromo)->pacientes);
}


void destruir_paciente(PVACUNODROMO* vacunodromo)
{
    suprimirElementoCola((* vacunodromo)->pacientes);
    --(* vacunodromo)->numPacientesCola;
}

void destruir_vacunodromo(PVACUNODROMO* vacunodromo)
{

    while ((* vacunodromo)->numPacientesCola != 0)
    {
        destruir_paciente((* vacunodromo)->pacientes);
    }
    destruirCola((* vacunodromo)->pacientes);

    free (*vacunodromo);
    *vacunodromo = NULL;

}

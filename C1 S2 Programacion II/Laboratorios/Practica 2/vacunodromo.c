#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
    crearCola(& (* vacunodromo)->pacientes);
}


void destruir_paciente(PVACUNODROMO* vacunodromo)
{
    TIPOELEMENTOCOLA primeroCola;
    consultarPrimerElementoCola((*vacunodromo)->pacientes, &primeroCola);
    destruirLista(&primeroCola.listaVacunas);

    suprimirElementoCola(& (* vacunodromo)->pacientes);
    --(* vacunodromo)->numPacientesCola;
}

void destruir_vacunodromo(PVACUNODROMO* vacunodromo)
{

    while (esColaVacia((* vacunodromo)->pacientes) == false)
    {
        destruir_paciente(vacunodromo);
    }

    destruirCola(& (* vacunodromo)->pacientes);

    free(* vacunodromo);
    * vacunodromo = NULL;

}

void anadir_paciente(PVACUNODROMO* vacunodromo)
{
    TIPOELEMENTOCOLA paciente;

    TIPOELEMENTOLISTA vacuna;

    printf("Introduzca el nombre del paciente: ");
    scanf("%s", paciente.nombrePaciente);

    crearLista(& paciente.listaVacunas);

    do
    {
        bool nombreErroneo;
        printf("Introduzca el nombre de la vacuna (fin para terminar): ");
        do
        {
            scanf("%s", vacuna.nombreVacuna);
            if (strcmp(vacuna.nombreVacuna, "") == 0)
            {
                nombreErroneo = true;
                printf("El nombre de la vacuna no puede ser nulo, vuelva a introducir el nombre de la vacuna: ");
            } else
            {
                //TODO: comprobar que el nombre de la vacuna no exista
                nombreErroneo = false;
            }
        } while (nombreErroneo == true);

        if (strcmp(vacuna.nombreVacuna, "fin") != 0)
        {
            printf("Introduzca el numero maximo de dosis: ");
            scanf("%hd", & vacuna.numMaxDosis);
            vacuna.numDosisAdministradas = 0;
            insertarElementoLista(& paciente.listaVacunas, finLista(paciente.listaVacunas), vacuna); // + &
        }
    } while (strcmp(vacuna.nombreVacuna, "fin") != 0);  //mientras que strcmp sea distinto de 0(Distinta cadena)
    anadirElementoCola(& (* vacunodromo)->pacientes, paciente);
    ++(* vacunodromo)->numPacientesCola;
    //printf("DEBUG : %i", longitudLista(paciente.listaVacunas));
}

void imprimir_paciente(PVACUNODROMO vacunodromo)
{
    if (vacunodromo != NULL)
    {
        TIPOELEMENTOCOLA paciente1;

        consultarPrimerElementoCola((* vacunodromo).pacientes, & paciente1);
        printf("Paciente: %s \n", paciente1.nombrePaciente);
        printf("Vacunas: \n");

        int i = 0;
        int max;

        max = longitudLista(paciente1.listaVacunas);
        TPOSICION pos = primeroLista(paciente1.listaVacunas);

        TIPOELEMENTOLISTA vacunas;
        do
        {

            recuperarElementoLista(paciente1.listaVacunas, pos, & vacunas);
            printf("    Vacuna: %s\n", vacunas.nombreVacuna);
            printf("    Maximas dosis: %hi\n", vacunas.numMaxDosis);
            printf("    Dosis administradas: %hi\n \n", vacunas.numDosisAdministradas);
            ++i;

            pos = siguienteLista(paciente1.listaVacunas, pos);

        } while (i < max);
    } else
    {
        printf("El vacunódromo seleccionado no existe");
    }
}

void imprimir(PVACUNODROMO vacunodromo)
{
    printf(" Pacientes restantes: %i\n", vacunodromo->numPacientesCola);
    printf("Primer paciente en cola: \n");
    imprimir_paciente(vacunodromo);
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
#include "./TAD/cola.h"

#define DEBUG 0

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
    consultarPrimerElementoCola((* vacunodromo)->pacientes, & primeroCola);
    destruirLista(& primeroCola.listaVacunas);

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
    fflush(stdin);
    TIPOELEMENTOCOLA paciente;

    TIPOELEMENTOLISTA nuevaVacuna;

    printf("Introduzca el nombre del paciente: ");
    scanf("%s", paciente.nombrePaciente);

    crearLista(& paciente.listaVacunas);

    do
    {
        bool nombreErroneo;
        printf("Introduzca el nombre de la vacuna (fin para terminar): ");
        do
        {
            nombreErroneo = false;
            scanf("%s", nuevaVacuna.nombreVacuna);

            if (strcmp(nuevaVacuna.nombreVacuna, "") == 0)
            {
                nombreErroneo = true;
                printf("El nombre de la vacuna no puede ser nulo, vuelva a introducir el nombre de la vacuna: ");
            } else
            {
                int numElemLista = longitudLista(paciente.listaVacunas);

                TPOSICION posEnLista;
                TIPOELEMENTOLISTA vacuna;
                for (int indice = 0; indice < numElemLista; ++indice)
                {
                    if (indice == 0)
                    {
                        posEnLista = primeroLista(paciente.listaVacunas);
                    } else
                    {
                        posEnLista = siguienteLista(paciente.listaVacunas, posEnLista);
                    }

                    recuperarElementoLista(paciente.listaVacunas, posEnLista, & vacuna);
                    if (strcmp(vacuna.nombreVacuna, nuevaVacuna.nombreVacuna) == 0)
                    {
                        printf("Error, ya existe una vacuna con el mismo nombre para este paciente. Introduzca otra vacuna: ");
                        nombreErroneo = true;
                        break;
                    }
                }

            }
        } while (nombreErroneo == true);

        if (strcmp(nuevaVacuna.nombreVacuna, "fin") != 0)
        {
            printf("Introduzca el numero maximo de dosis: ");
            scanf("%hd", & nuevaVacuna.numMaxDosis);
            nuevaVacuna.numDosisAdministradas = 0;
            insertarElementoLista(& paciente.listaVacunas, finLista(paciente.listaVacunas), nuevaVacuna); // + &
        }
    } while (strcmp(nuevaVacuna.nombreVacuna, "fin") != 0);  //mientras que strcmp sea distinto de 0(Distinta cadena)
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

        printf("  Paciente: %s \n", paciente1.nombrePaciente);
        printf("  Vacunas: \n");


        int numElemLista = longitudLista(paciente1.listaVacunas);


        if (numElemLista == 0)
        {
            printf("No existen vacunas pendientes para este paciente\n");
        } else
        {

            TPOSICION posEnLista;
            TIPOELEMENTOLISTA vacuna;
            for (int indice = 0; indice < numElemLista; ++indice)
            {
                if (indice == 0)
                {
                    posEnLista = primeroLista(paciente1.listaVacunas);
                } else
                {
                    posEnLista = siguienteLista(paciente1.listaVacunas, posEnLista);
                }

                recuperarElementoLista(paciente1.listaVacunas, posEnLista, & vacuna);
                printf("    Vacuna: %s\n", vacuna.nombreVacuna);
                printf("    Maximas dosis: %hi\n", vacuna.numMaxDosis);
                printf("    Dosis administradas: %hi\n \n", vacuna.numDosisAdministradas);
            }
        }
    } else
    {
        printf("El vacunódromo seleccionado no existe");
    }

}

void imprimir(PVACUNODROMO vacunodromo)
{
    if (vacunodromo->numPacientesCola > 0)
    {
        printf(" Pacientes restantes: %i\n", vacunodromo->numPacientesCola);
        printf("Primer paciente en cola: \n");
        imprimir_paciente(vacunodromo);
    } else
    {
        printf("No hay ningún paciente en este momento");
    }
}

void vacunar_paciente(PVACUNODROMO* vacunodromo)
{
    if (vacunodromo != NULL && (* vacunodromo)->numPacientesCola > 0)
    {
        TIPOELEMENTOCOLA paciente;
        consultarPrimerElementoCola((* vacunodromo)->pacientes, & paciente);
        TPOSICION posVacunas = primeroLista(paciente.listaVacunas);

        int numeroVacunas = longitudLista(paciente.listaVacunas);
        TIPOELEMENTOLISTA vacunaActual;

        for (int i = 0; i < numeroVacunas; i++)
        {
            recuperarElementoLista(paciente.listaVacunas, posVacunas, & vacunaActual);


            printf("Vacunando a %s con %s:\n  Vacuna %i de %i\n", paciente.nombrePaciente, vacunaActual.nombreVacuna, vacunaActual.numDosisAdministradas + 1, vacunaActual.numMaxDosis);
            if (++vacunaActual.numDosisAdministradas == vacunaActual.numMaxDosis)
            {
                if (DEBUG == 1)
                {
                    printf("\n¡ESTOY AQUÍ! (I)\n");
                }
                suprimirElementoLista(& paciente.listaVacunas, posVacunas);
            } else
            {
                suprimirElementoLista(& paciente.listaVacunas, posVacunas);
                insertarElementoLista(& paciente.listaVacunas, posVacunas, vacunaActual);
                posVacunas = siguienteLista(paciente.listaVacunas, posVacunas);
                if (DEBUG == 1)
                {
                    printf("¡ESTOY AQUÍ! (II)");
                }
            }

        }

        suprimirElementoCola(& (* vacunodromo)->pacientes);
        if (longitudLista(paciente.listaVacunas) != 0)
        {
            anadirElementoCola(& (* vacunodromo)->pacientes, paciente);
        } else
        {
            destruirLista(&paciente.listaVacunas);
            (* vacunodromo)->numPacientesCola--;
        }
    } else if (vacunodromo == NULL)
    {
        printf("El vacunódromo seleccionado no existe");
    } else
    {
        printf("No hay pacientes en este vacunódromo");
    }
}

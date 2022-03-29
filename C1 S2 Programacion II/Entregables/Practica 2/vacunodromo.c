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
    consultarPrimerElementoCola((* vacunodromo)->pacientes, & primeroCola);
    destruirLista(& primeroCola.listaVacunas);

    suprimirElementoCola(& (* vacunodromo)->pacientes);
    --(* vacunodromo)->numPacientesCola;
}

void destruir_vacunodromo(PVACUNODROMO* vacunodromo)
{

    while (esColaVacia((* vacunodromo)->pacientes) == false) //mientras la cola pacientes no sea vacía
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
            do
            {
                scanf("%hd", & nuevaVacuna.numMaxDosis);
                if (nuevaVacuna.numMaxDosis <= 0)
                {
                    printf("EL numero ha de ser mayor a 0: ");
                }
            } while (nuevaVacuna.numMaxDosis <= 0);
            nuevaVacuna.numDosisAdministradas = 0;
            insertarElementoLista(& paciente.listaVacunas, finLista(paciente.listaVacunas), nuevaVacuna);
        }
    } while (strcmp(nuevaVacuna.nombreVacuna, "fin") != 0);  //mientras que strcmp sea distinto de 0(Distinta cadena)
    anadirElementoCola(& (* vacunodromo)->pacientes, paciente);
    ++(* vacunodromo)->numPacientesCola;
}

void imprimir_paciente(PVACUNODROMO vacunodromo)
{
    if (vacunodromo != NULL)
    {
        TIPOELEMENTOCOLA paciente1;
        if (esColaVacia((* vacunodromo).pacientes) == 1)
        {
            printf("No hay pacientes pendientes en esta cola.\n");
            return;
        }

        consultarPrimerElementoCola((* vacunodromo).pacientes, & paciente1);

        printf("  Paciente: %s\n", paciente1.nombrePaciente);
        printf("  Vacunas:\n");


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

void vacunar_paciente_v1(PVACUNODROMO* vacunodromo)
{
    if (vacunodromo != NULL && (* vacunodromo)->numPacientesCola > 0)
    {
        TIPOELEMENTOCOLA paciente;
        consultarPrimerElementoCola((* vacunodromo)->pacientes, & paciente);

        if (esListaVacia(paciente.listaVacunas) == 1)
        {
            printf("No hay vacunas pendientes para este paciente.\n");
            destruir_paciente(vacunodromo);
            return;
        }

        TIPOELEMENTOLISTA vacunaActual;
        TPOSICION posVacunas = primeroLista(paciente.listaVacunas);

        int numeroVacunas = longitudLista(paciente.listaVacunas);

        for (int indice = 0; indice < numeroVacunas; ++indice)
        {
            recuperarElementoLista(paciente.listaVacunas, posVacunas, & vacunaActual);


            printf("Vacunando a %s con %s:\n  Vacuna %i de %i\n", paciente.nombrePaciente, vacunaActual.nombreVacuna, vacunaActual.numDosisAdministradas + 1, vacunaActual.numMaxDosis);
            if (++vacunaActual.numDosisAdministradas >= vacunaActual.numMaxDosis)
            {
                suprimirElementoLista(& paciente.listaVacunas, posVacunas);
            } else
            {
                modificarElementoLista(& paciente.listaVacunas, posVacunas, vacunaActual);
                posVacunas = siguienteLista(paciente.listaVacunas, posVacunas);
            }

        }


        if (longitudLista(paciente.listaVacunas) != 0)
        {
            suprimirElementoCola(& (* vacunodromo)->pacientes);
            anadirElementoCola(& (* vacunodromo)->pacientes, paciente);
        } else
        {
            destruir_paciente(vacunodromo);
        }
    } else if (vacunodromo == NULL)
    {
        printf("El vacunódromo seleccionado no existe");
    } else
    {
        printf("No hay pacientes en este vacunódromo");
    }
}

void vacunar_paciente_v2(PVACUNODROMO* vacunodromo)
{
    if (vacunodromo != NULL && (* vacunodromo)->numPacientesCola > 0)
    {
        TIPOELEMENTOCOLA paciente;
        consultarPrimerElementoCola((* vacunodromo)->pacientes, & paciente);
        if (esListaVacia(paciente.listaVacunas) == 1)
        {
            printf("No hay vacunas pendientes para este paciente.\n");
            destruir_paciente(vacunodromo);
            return;
        }

        TIPOELEMENTOLISTA vacunaActual;

        bool borrarVacuna = false;
        bool quedanVacunas = false;

        TPOSICION posVacunas = primeroLista(paciente.listaVacunas);

        do
        {
            recuperarElementoLista(paciente.listaVacunas, posVacunas, & vacunaActual);


            printf("Vacunando a %s con %s:\n  Vacuna %i de %i\n", paciente.nombrePaciente, vacunaActual.nombreVacuna, vacunaActual.numDosisAdministradas + 1, vacunaActual.numMaxDosis);
            if (++vacunaActual.numDosisAdministradas >= vacunaActual.numMaxDosis) //++x primero hace x = x+1 y luego evalúa la expresión posterior
            {
                borrarVacuna = true; //pongo esto a true cuando hay que borrar por lo menos una vacuna
                //suprimirElementoLista(& paciente.listaVacunas, posVacunas);
            } else
            {
                quedanVacunas = true;
            }

            modificarElementoLista(& paciente.listaVacunas, posVacunas, vacunaActual);

            posVacunas = siguienteLista(paciente.listaVacunas, posVacunas);

        } while (posVacunas != finLista(paciente.listaVacunas));

        if (quedanVacunas == false)
        {
            destruir_paciente(vacunodromo);
        } else
        {

            if (borrarVacuna == true)
            {
                //borrar las vacunas que haya que borrar
                TLISTA nuevaLista;
                crearLista(& nuevaLista);

                do
                {
                    posVacunas = primeroLista(paciente.listaVacunas);
                    recuperarElementoLista(paciente.listaVacunas, posVacunas, & vacunaActual);

                    if (vacunaActual.numDosisAdministradas < vacunaActual.numMaxDosis)
                    {
                        insertarElementoLista(& nuevaLista, finLista(nuevaLista), vacunaActual);
                    }

                    suprimirElementoLista(& paciente.listaVacunas, posVacunas);

                } while (posVacunas != finLista(paciente.listaVacunas));
                destruirLista(&paciente.listaVacunas);
                paciente.listaVacunas = nuevaLista;
            }

            // Muevo al paciente al final de la cola.
            suprimirElementoCola(& (* vacunodromo)->pacientes);
            anadirElementoCola(& (* vacunodromo)->pacientes, paciente);
        }
    } else if (vacunodromo == NULL)
    {
        printf("El vacunódromo seleccionado no existe");
    } else
    {
        printf("No hay pacientes en este vacunódromo");
    }
}

void vacunar_paciente(PVACUNODROMO* vacunodromo)
{
    vacunar_paciente_v1(vacunodromo);
}

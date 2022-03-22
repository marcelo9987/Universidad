#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wchar.h>
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

    TIPOELEMENTOLISTA nuevaVacuna;

    wprintf(L"Introduzca el nombre del paciente: ");
    scanf("%s", paciente.nombrePaciente);

    crearLista(& paciente.listaVacunas);

    do
    {
        bool nombreErroneo;
        wprintf(L"Introduzca el nombre de la vacuna (fin para terminar): ");
        do
        {
            nombreErroneo = false;
            scanf("%s", nuevaVacuna.nombreVacuna);

            if (strcmp(nuevaVacuna.nombreVacuna, "") == 0)
            {
                nombreErroneo = true;
                wprintf(L"El nombre de la vacuna no puede ser nulo, vuelva a introducir el nombre de la vacuna: ");
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
                    if(strcmp(vacuna.nombreVacuna, nuevaVacuna.nombreVacuna)==0)
                    {
                        wprintf(L"Error, ya existe una vacuna con el mismo nombre para este paciente. Introduzca otra vacuna: ");
                        nombreErroneo = true;
                        break;
                    }
                }

            }
        } while (nombreErroneo == true);

        if (strcmp(nuevaVacuna.nombreVacuna, "fin") != 0)
        {
            wprintf(L"Introduzca el numero maximo de dosis: ");
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

        wprintf(L"Paciente: %s \n", paciente1.nombrePaciente);
        wprintf(L"Vacunas: \n");


        int numElemLista = longitudLista(paciente1.listaVacunas);


        if (numElemLista == 0)
        {
            wprintf(L"No existen vacunas pendientes para este paciente\n");
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
                wprintf(L"    Vacuna: %s\n", vacuna.nombreVacuna);
                wprintf(L"    Maximas dosis: %hi\n", vacuna.numMaxDosis);
                wprintf(L"    Dosis administradas: %hi\n \n", vacuna.numDosisAdministradas);
            }
        }
    } else
    {
        wprintf(L"El vacunódromo seleccionado no existe");
    }

}

void imprimir(PVACUNODROMO vacunodromo)
{
    wprintf(L" Pacientes restantes: %i\n", vacunodromo->numPacientesCola);
    wprintf(L"Primer paciente en cola: \n");
    imprimir_paciente(vacunodromo);
}

void vacunar_paciente(PVACUNODROMO* vacunodromo)
{
       if(vacunodromo!=NULL)
       {
           TIPOELEMENTOCOLA paciente;
           consultarPrimerElementoCola((*vacunodromo)->pacientes,&paciente);
           TPOSICION posVacunas = primeroLista(paciente.listaVacunas);

           int numeroVacunas = longitudLista(paciente.listaVacunas);
           TIPOELEMENTOLISTA vacunaActual;

           for(int i = 0;i<numeroVacunas;i++)
           {
               recuperarElementoLista(paciente.listaVacunas,posVacunas,&vacunaActual);




               if(++vacunaActual.numDosisAdministradas == vacunaActual.numMaxDosis)
               {
                   wprintf(L"¡ESTOY AQUÍ! (I)");
                   suprimirElementoLista(&paciente.listaVacunas,posVacunas);
               }else
               {
                   suprimirElementoLista(&paciente.listaVacunas,posVacunas);
                   insertarElementoLista(&paciente.listaVacunas,posVacunas,vacunaActual);
                   posVacunas = siguienteLista(paciente.listaVacunas,posVacunas);
                   wprintf(L"¡ESTOY AQUÍ! (II)");
               }

               }
           suprimirElementoCola(&(*vacunodromo)->pacientes);
           if(longitudLista(paciente.listaVacunas)!=0)
           {
               anadirElementoCola(&(*vacunodromo)->pacientes, paciente);
           }
       }else
       {
           wprintf(L"El vacunódromo seleccionado no existe");
       }
}

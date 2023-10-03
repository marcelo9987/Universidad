/*
 * Archivo: vacunodromo.c
 * Autor: Marcelo Fort Muñoz
 */


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "vacunodromo.h"

#define CADENADECONTROL "$$NOEXISTE$$"

void _leerVacunas(TLISTA listaVacunas)
{
    TPOSICION posActual = primeroLista(listaVacunas);
    while (posActual != finLista(listaVacunas))
    {
        TIPOELEMENTOLISTA elementoActual;
        recuperarElementoLista(listaVacunas, posActual, &elementoActual);
        fprintf(stdout, "\tVacuna: %s  dosis administradas: %d de %d\n", elementoActual.nombreVacuna, elementoActual.i_dosisAdministradas, elementoActual.i_dosisMaximas);
        posActual = siguienteLista(listaVacunas, posActual);
    }
}

void anhadirPaciente(TABB *arbolPacientes)
{
    if (arbolPacientes == NULL)
    {
        fprintf(stdout, "ERR: anhadirPaciente --> El arbol no existe.\n");
        return;
    }

    TIPOELEMENTOABB elementoArbolInsertar;

    fprintf(stdout, "Introduzca: Apellido1 Apellido2, Nombre: ");
//    char nombre[MAXNOMBRE];


    fscanf(stdin, "%[^\n]s", elementoArbolInsertar.apellidosNombre);
    getchar(); // Elimino el \n que ha quedado

//    strcpy(elementoArbolInsertar.apellidosNombre, nombre);

    TLISTA listaVacunas;
    crearLista(&listaVacunas);
//    int primeraVez = 1;
    for (;;)
    {
        char nombreVacunaActual[MAXNOMBREVACUNA];
        int dosisMaximaVacunaActual;

        fprintf(stdout, "Introduzca nombre de vacuna: ");

        fscanf(stdin, "%[^\n]s", nombreVacunaActual);
        getchar(); // Elimino el \n que ha quedado// Eliminar el salto de linea del final

        if (strcmp(nombreVacunaActual, "fin") == 0)
        {
            break;
        }

//        fprintf(stdout, "Introduzca dosis de vacuna: ");
//        fscanf(stdin, "%d", &dosisVacunaActual);



        fprintf(stdout, "Introduzca dosis maxima de vacuna: ");
        fscanf(stdin, "%d", &dosisMaximaVacunaActual);
        while (getchar() != '\n')
        {}// Limpiar buffer

        TIPOELEMENTOLISTA elementoListaInsertar;
        strcpy(elementoListaInsertar.nombreVacuna, nombreVacunaActual);

        elementoListaInsertar.i_dosisAdministradas = 0;
        elementoListaInsertar.i_dosisMaximas = dosisMaximaVacunaActual;

        insertarElementoLista(&listaVacunas, finLista(listaVacunas), elementoListaInsertar);
    }


    elementoArbolInsertar.vacunas = listaVacunas;


    insertarElementoAbb(arbolPacientes, elementoArbolInsertar);
}

void listadoPacientes(TABB arbolPacientes, bool primeraIteracion)
{
    if (esAbbVacio(arbolPacientes))
    {
        if (primeraIteracion)
        {
            fprintf(stdout, "INFO: listadoPacientes --> El arbol está vacío.\n");
        }
        return;
    }

    listadoPacientes(izqAbb(arbolPacientes), false);

    TIPOELEMENTOABB elementoActual;
    leerElementoAbb(arbolPacientes, &elementoActual);

    fprintf(stdout, "%s\n", elementoActual.apellidosNombre);
    _leerVacunas(elementoActual.vacunas);

    fprintf(stdout, "\n");

    listadoPacientes(derAbb(arbolPacientes), false);


}

void eliminarPaciente(TABB *arbolPacientes)
{
    if (esAbbVacio(*arbolPacientes))
    {
        fprintf(stdout, "ERR: eliminarPaciente --> No hay pacientes en el sistema.\n");
        return;
    }

    fprintf(stdout, "Introduzca el nombre del paciente a eliminar: ");

    char nombre[MAXNOMBRE];
    fscanf(stdin, "%[^\n]s", nombre);
    getchar(); // Elimino el \n que ha quedado// Eliminar el salto de linea del final

    TIPOELEMENTOABB pacienteAeliminar;
    strcpy(pacienteAeliminar.apellidosNombre, CADENADECONTROL);


    buscarNodoAbb(*arbolPacientes, nombre, &pacienteAeliminar);
    if (strcmp(pacienteAeliminar.apellidosNombre, CADENADECONTROL) == 0)
    {
        fprintf(stdout, "ERR: eliminarPaciente --> El paciente no existe.\n");
        return;
    }

    suprimirElementoAbb(arbolPacientes, pacienteAeliminar);
    fprintf(stdout, "INFO: eliminarPaciente --> Paciente eliminado.\n");
}

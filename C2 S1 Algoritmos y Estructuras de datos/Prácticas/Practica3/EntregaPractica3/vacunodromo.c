/*
 * Archivo: vacunodromo.c
 * Autor: Marcelo Fort Muñoz
 */


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vacunodromo.h"

// #define CADENADECONTROL "$$NOEXISTE$$"
#define MAXLINEA 100

/// Funciones privadas

void _imprimirVacunas(TLISTA listaVacunas)
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

void _imprimirPaciente(TIPOELEMENTOABB *paciente)
{
    fprintf(stdout, "%s\n", (*paciente).apellidosNombre);
    _imprimirVacunas((*paciente).vacunas);
}

void _strip_line(char *linea)
{
    linea[strcspn(linea, "\r\n")] = 0;
}


void _recorridoPostOrdenGuardar(TABB arbolPacientes, FILE *fichero)
{
    if (esAbbVacio(arbolPacientes))
    {
//        fprintf(stdout, "ERR: _recorridoPostOrdenGuardar --> El arbol está vacío.\n");
        return;
    }

    _recorridoPostOrdenGuardar(izqAbb(arbolPacientes), fichero);
    _recorridoPostOrdenGuardar(derAbb(arbolPacientes), fichero);

    TIPOELEMENTOABB elementoActual;
    leerElementoAbb(arbolPacientes, &elementoActual);

    fprintf(fichero, "%s|", elementoActual.apellidosNombre);
//    fprintf(stdout, "%s|", elementoActual.apellidosNombre);

    //imprimo las vacunas
    TPOSICION posActual = primeroLista(elementoActual.vacunas);
    while (posActual != finLista(elementoActual.vacunas))
    {
        TIPOELEMENTOLISTA vacunaActual;
        recuperarElementoLista(elementoActual.vacunas, posActual, &vacunaActual);
        fprintf(fichero, "%s;%d;%d;", vacunaActual.nombreVacuna, vacunaActual.i_dosisAdministradas, vacunaActual.i_dosisMaximas);
//        fprintf(stdout, "\tVacuna: %s  dosis administradas: %d de %d\n", vacunaActual.nombreVacuna, vacunaActual.i_dosisAdministradas, vacunaActual.i_dosisMaximas);
        posActual = siguienteLista(elementoActual.vacunas, posActual);
    }
    fprintf(fichero, "\n");

}

/**
 * @brief Guarda en cola los pacientes que tienen pendientes dosis de la vacuna solicitada.
 */
void _llenarColaVacunacion(TCOLA *cola, TABB arbolPacientes, char *nombreVacunaSolicitada)
{
    if (esAbbVacio(arbolPacientes))
    {
        return;
    }

    TIPOELEMENTOABB elementoActual;
    leerElementoAbb(arbolPacientes, &elementoActual);

    TPOSICION posActualListaVacunasPaciente = primeroLista(elementoActual.vacunas);
    while (posActualListaVacunasPaciente != finLista(elementoActual.vacunas))
    {
        TIPOELEMENTOLISTA vacunaActual;
        recuperarElementoLista(elementoActual.vacunas, posActualListaVacunasPaciente, &vacunaActual);
        if (vacunaActual.i_dosisAdministradas < vacunaActual.i_dosisMaximas && strcmp(vacunaActual.nombreVacuna, nombreVacunaSolicitada) == 0)
        {
            anadirElementoCola(cola, elementoActual);
            break;
        }
        posActualListaVacunasPaciente = siguienteLista(elementoActual.vacunas, posActualListaVacunasPaciente);
    }

    _llenarColaVacunacion(cola, izqAbb(arbolPacientes), nombreVacunaSolicitada);
    _llenarColaVacunacion(cola, derAbb(arbolPacientes), nombreVacunaSolicitada);
}

bool _existeVacuna(TABB arbolPacientes, char nombreVacuna[MAXNOMBREVACUNA])
{
    if (esAbbVacio(arbolPacientes))
    {
        return false;
    }

    TIPOELEMENTOABB elementoActual;
    leerElementoAbb(arbolPacientes, &elementoActual);

    TPOSICION posActual = primeroLista(elementoActual.vacunas);
    while (posActual != finLista(elementoActual.vacunas))
    {
        TIPOELEMENTOLISTA vacunaActual;
        recuperarElementoLista(elementoActual.vacunas, posActual, &vacunaActual);
        if (strcmp(vacunaActual.nombreVacuna, nombreVacuna) == 0)
        {
            return true;
        }
        posActual = siguienteLista(elementoActual.vacunas, posActual);
    }

    if (_existeVacuna(izqAbb(arbolPacientes), nombreVacuna))
    {
        return true;
    }
    if (_existeVacuna(derAbb(arbolPacientes), nombreVacuna))
    {
        return true;
    }

    return false;
}

void _listadoPacientes(TABB arbolPacientes, bool primeraIteracion)
{
    if (esAbbVacio(arbolPacientes))
    {
        if (primeraIteracion)
        {
            fprintf(stdout, "INFO: listadoPacientes --> El arbol está vacío.\n");
        }
        return;
    }

    _listadoPacientes(izqAbb(arbolPacientes), false);

    TIPOELEMENTOABB elementoActual;
    leerElementoAbb(arbolPacientes, &elementoActual);

    _imprimirPaciente(&elementoActual);

    fprintf(stdout, "\n");

    _listadoPacientes(derAbb(arbolPacientes), false);


}

/// Funciones públicas

void anhadirPaciente(TABB *arbolPacientes)
{
    if (arbolPacientes == NULL)
    {
        fprintf(stdout, "ERR: anhadirPaciente --> El arbol no existe.\n");
        return;
    }

    TIPOELEMENTOABB elementoArbolInsertar;

    fprintf(stdout, "Introduzca: Apellido1 Apellido2, Nombre:");

    fscanf(stdin, " %[^\n\r]", elementoArbolInsertar.apellidosNombre);

    if (esMiembroAbb(*arbolPacientes, elementoArbolInsertar) == true)
    {
        fprintf(stdout, "ERR: anhadirPaciente --> El paciente ya existe.\n");
        return;
    }

    crearLista(&elementoArbolInsertar.vacunas);

    TIPOELEMENTOLISTA elementoListaVacunas;

    for (;;)
    {
        //todo: ver si se debe permitir que haya varias vacunas con el mismo nombre para un mismo paciente.
        fprintf(stdout, "Introduzca nombre de vacuna:");

        fscanf(stdin, " %[^\n\r]s", elementoListaVacunas.nombreVacuna);

        if (strcmp(elementoListaVacunas.nombreVacuna, "fin") == 0)
        {
            break;
        }


        fprintf(stdout, "Introduzca dosis maxima de vacuna:");
        fscanf(stdin, " %d", &elementoListaVacunas.i_dosisMaximas);


        elementoListaVacunas.i_dosisAdministradas = 0;

        insertarElementoLista(&elementoArbolInsertar.vacunas, finLista(elementoArbolInsertar.vacunas), elementoListaVacunas);
    }


    insertarElementoAbb(arbolPacientes, elementoArbolInsertar);
}

void listadoPacientes(TABB arbolPacientes)
{
    _listadoPacientes(arbolPacientes, true);
}

void eliminarPaciente(TABB *arbolPacientes)
{
    if (esAbbVacio(*arbolPacientes))
    {
        fprintf(stdout, "ERR: eliminarPaciente --> No hay pacientes en el sistema.\n");
        return;
    }

    fprintf(stdout, "Introduzca el nombre del paciente a eliminar: ");

    TIPOELEMENTOABB pacienteAeliminar;

    fscanf(stdin, " %[^\n]s", pacienteAeliminar.apellidosNombre);

    if (esMiembroAbb(*arbolPacientes, pacienteAeliminar) == false)
    {
        fprintf(stdout, "ERR: eliminarPaciente --> El paciente no existe.\n");
        return;
    }

    suprimirElementoAbb(arbolPacientes, pacienteAeliminar);
    fprintf(stdout, "INFO: eliminarPaciente --> Paciente eliminado.\n");
}

void cargarArchivo(TABB *arbolPacientes, int argc, char *argv[])
{
    if ((argc != 3) || (strncmp(argv[1], "-f\0", 3) != 0)) //0 // Si el número de argumentos o el formato de los argumentos son incorrectos
    {
        fprintf(stdout, "Los argumentos no son correctos.\nUso: %s [opciones] [fichero]\n\tOpciones:\n\t-f (opcional) fichero\n", argv[0]);
        return;
    }

    enum camposListaVacunas
    {
        nombreVacuna = 0, dosisAdministradas = 1, dosisMaximas = 2
    };

    FILE *fichero = fopen(*(argv + 2), "r");
    if (fichero == NULL) //Si el fichero no existe o no se ha podido abrir:
    {
        fprintf(stdout, "ERR: cargarArchivo --> El fichero no existe o no se ha podido abrir.\n");
        return;
    }

    char linea[MAXLINEA]; // variable temporal para almacenar una linea completa del archivo

    while ((fgets(linea, MAXLINEA, fichero) != NULL) /*&& !feof(fichero)*/)
    {
        _strip_line(linea);

        TIPOELEMENTOABB elementoArbolInsertar;

        char *nombrePaciente = strtok(linea, "|");
        strcpy(elementoArbolInsertar.apellidosNombre, nombrePaciente);
        fprintf(stdout, "Nombre paciente: %s\n", elementoArbolInsertar.apellidosNombre);

        char *listaVacunas = strtok(NULL, "|");
        //   fprintf(stdout, "Lista vacunas: %s\n", listaVacunas);

        TIPOELEMENTOLISTA vacunaActual;
        crearLista(&elementoArbolInsertar.vacunas);

        char *campo = strtok(listaVacunas, ";");
        while (campo != NULL)
        {
            for (int campoActual = 0; campoActual < 3; campoActual++)
            {
                switch (campoActual)
                {
                    case nombreVacuna:
                        strcpy(vacunaActual.nombreVacuna, campo);
                        fprintf(stdout, "Nombre vacuna: %s\n", vacunaActual.nombreVacuna);
                        break;
                    case dosisMaximas:
                        vacunaActual.i_dosisMaximas = atoi(campo);
                        fprintf(stdout, "Dosis maximas: %d\n", vacunaActual.i_dosisMaximas);
                        break;
                    case dosisAdministradas:
                        vacunaActual.i_dosisAdministradas = atoi(campo);
                        fprintf(stdout, "Dosis administradas: %d\n", vacunaActual.i_dosisAdministradas);
                        break;
                    default:
                        fprintf(stdout, "ERR: cargarArchivo --> Campo no reconocido.\n");
                        break;
                }
                campo = strtok(NULL, ";");
            }
            insertarElementoLista(&elementoArbolInsertar.vacunas, finLista(elementoArbolInsertar.vacunas), vacunaActual);
        }
        insertarElementoAbb(arbolPacientes, elementoArbolInsertar);
    }

    if (fclose(fichero) != 0)
    {
        fprintf(stdout, "ERR: cargarArchivo --> No se ha podido cerrar el fichero.\n");
    }


}

void guardarArchivo(TABB arbolPacientes, char *nombreArchivo)
{
    FILE *fichero = fopen(nombreArchivo, "w");

    if (fichero == NULL)//Si no se ha podido abrir y crear el fichero:
    {
        fprintf(stdout, "ERR: guardarArchivo --> No se ha podido crear el fichero.\n");
        return;
    }

    _recorridoPostOrdenGuardar(arbolPacientes, fichero);

    if (fclose(fichero) != 0)
    {
        fprintf(stdout, "ERR: guardarArchivo --> No se ha podido cerrar el fichero.\n");
    }

}

void inicializarVacundromo(VACUNODROMO *vacunodromo)
{
    if (vacunodromo == NULL)
    {
        fprintf(stdout, "ERR: inicializarVacundromo --> El vacunódromo no existe.\n");
        return;
    }

    vacunodromo->i_numeroPacientes = 0;
    vacunodromo->nombreVacun[0] = '\0';
//    crearCola(&vacunodromo->colaPacientes);
    vacunodromo->colaPacientes = NULL;
}

void crearColaVacunacion(VACUNODROMO *vacunodromo, TABB arbolPacientes)
{
    char nombreVacuna[MAXNOMBREVACUNA];

    fprintf(stdout, "Introduzca el nombre de la vacuna a administrar: ");
    fscanf(stdin, " %[^\n]s", nombreVacuna);
    if (_existeVacuna(arbolPacientes, nombreVacuna) == false)
    {
        fprintf(stdout, "ERR: crearColaVacunacion --> La vacuna no existe.\n");
        return;
    }

    strncpy(vacunodromo->nombreVacun, nombreVacuna, MAXNOMBREVACUNA);

    fprintf(stdout, "Nombre del vacunódromo: %s\n", vacunodromo->nombreVacun);

    if (vacunodromo->colaPacientes != NULL)
    {
        destruirCola(&vacunodromo->colaPacientes);
        vacunodromo->colaPacientes = NULL;
    }

    crearCola(&vacunodromo->colaPacientes);

    _llenarColaVacunacion(&vacunodromo->colaPacientes, arbolPacientes, nombreVacuna);
}

void vacunarPrimerPaciente(VACUNODROMO *vacunodromo, TABB *arbolPacientes)
{
    if (vacunodromo == NULL)
    {
        fprintf(stdout, "ERR: vacunarPrimerPaciente --> El vacunódromo no existe.\n");
        return;
    }
    if (esColaVacia(vacunodromo->colaPacientes))
    {
        fprintf(stdout, "ERR: vacunarPrimerPaciente --> No hay pacientes en la cola.\n");
        return;
    }

    bool pacienteConDosisPendientesDeEstaVacuna = true;

    TIPOELEMENTOCOLA pacienteActual;
    consultarPrimerElementoCola(vacunodromo->colaPacientes, &pacienteActual);

    fprintf(stdout, "Paciente: %s\n", pacienteActual.apellidosNombre);

    suprimirElementoCola(&vacunodromo->colaPacientes);

    TIPOELEMENTOLISTA vacunaActual;
    // Busco la vacuna que se va a administrar al paciente.
    TPOSICION posActualListaVacunasPaciente = primeroLista(pacienteActual.vacunas);
    do
    {
        recuperarElementoLista(pacienteActual.vacunas, posActualListaVacunasPaciente, &vacunaActual);

        posActualListaVacunasPaciente = siguienteLista(pacienteActual.vacunas, posActualListaVacunasPaciente);

        if (posActualListaVacunasPaciente == finLista(pacienteActual.vacunas))
        {
            fprintf(stdout, "ERR: vacunarPrimerPaciente --> El paciente no tiene pendiente ninguna dosis de esta vacuna.\n");
            pacienteConDosisPendientesDeEstaVacuna = false;
            break;
        }

    } while (strcmp(vacunaActual.nombreVacuna, vacunodromo->nombreVacun) != 0);

    if (pacienteConDosisPendientesDeEstaVacuna)
    {
        fprintf(stdout, "Voy a actualizar la vacuna %s con valor previo %d y nuevo valor %d\n", vacunaActual.nombreVacuna, vacunaActual.i_dosisAdministradas, vacunaActual.i_dosisAdministradas + 1);

        vacunaActual.i_dosisAdministradas++;

        if (vacunaActual.i_dosisAdministradas < vacunaActual.i_dosisMaximas)
        {
            fprintf(stdout, "INFO: vacunarPrimerPaciente --> El paciente no ha sido vacunado completamente. Se volverá a añadir al final de la cola.\n");
            anadirElementoCola(&vacunodromo->colaPacientes, pacienteActual);
        }
    }

    if (esListaVacia(pacienteActual.vacunas))
    {
        fprintf(stdout, "INFO: vacunarPrimerPaciente --> La lista de vacunas del paciente está vacía. Se eliminará de la base de datos\n");
        suprimirElementoAbb(arbolPacientes, pacienteActual);
    } else
    {
        fprintf(stdout, "INFO: vacunarPrimerPaciente --> El paciente ha sido vacunado completamente de esta vacuna. Como tiene otras vacunas pendientes, no se eliminará de la base de datos.\n");
    }

//    fprintf(stdout, "El paciente ha sido vacunado.\n");

}

/*
 * Archivo: vacunodromo.c
 * Autor: Marcelo Fort Muñoz
 */


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vacunodromo.h"

#define MAXLINEA 1000

/// Funciones privadas

void _imprimirVacunas(TLISTA listaVacunas)
{
    TPOSICION contenedorInfoVacuna = primeroLista(listaVacunas);
    while (contenedorInfoVacuna != finLista(listaVacunas))
    {
        TIPOELEMENTOLISTA infoVacunaEnLista;
        recuperarElementoLista(listaVacunas, contenedorInfoVacuna, &infoVacunaEnLista);
        fprintf(stdout, "\tVacuna: %s  dosis administradas: %d de %d\n", infoVacunaEnLista.nombreVacuna, infoVacunaEnLista.i_dosisAdministradas, infoVacunaEnLista.i_dosisMaximas);
        contenedorInfoVacuna = siguienteLista(listaVacunas, contenedorInfoVacuna);
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

    TIPOELEMENTOABB datosPacienteEnBd;
    leerElementoAbb(arbolPacientes, &datosPacienteEnBd);

    fprintf(fichero, "%s|", datosPacienteEnBd.apellidosNombre);

    //imprimo las vacunas
    TPOSICION posicionInfoDosis = primeroLista(datosPacienteEnBd.vacunas);
    while (posicionInfoDosis != finLista(datosPacienteEnBd.vacunas))
    {
        TIPOELEMENTOLISTA infoDosis;
        recuperarElementoLista(datosPacienteEnBd.vacunas, posicionInfoDosis, &infoDosis);
        fprintf(fichero, "%s;%d;%d;", infoDosis.nombreVacuna, infoDosis.i_dosisAdministradas, infoDosis.i_dosisMaximas);
//        fprintf(stdout, "\tVacuna: %s  dosis administradas: %d de %d\n", infoDosis.nombreVacuna, infoDosis.i_dosisAdministradas, infoDosis.i_dosisMaximas);
        posicionInfoDosis = siguienteLista(datosPacienteEnBd.vacunas, posicionInfoDosis);
    }
    fprintf(fichero, "\n");

}

/**
 * @brief Guarda en cola los pacientes que tienen pendientes dosis de la vacuna solicitada.
 */
void _llenarColaVacunacion(VACUNODROMO *vacunodromo, TABB arbolPacientes)
{
    if (esAbbVacio(arbolPacientes))
    {
        return;
    }

    TIPOELEMENTOABB datosPacienteEnBd;
    leerElementoAbb(arbolPacientes, &datosPacienteEnBd);

    TPOSICION posicionInfoDosis = primeroLista(datosPacienteEnBd.vacunas);
    while (posicionInfoDosis != finLista(datosPacienteEnBd.vacunas))
    {
        TIPOELEMENTOLISTA infoDosis;
        recuperarElementoLista(datosPacienteEnBd.vacunas, posicionInfoDosis, &infoDosis);

        if (infoDosis.i_dosisAdministradas < infoDosis.i_dosisMaximas && strcmp(infoDosis.nombreVacuna, vacunodromo->nombreVacun) == 0)
        {
            anadirElementoCola(&vacunodromo->colaPacientes, datosPacienteEnBd);
            vacunodromo->i_numeroPacientes++;
            fprintf(stdout, "        %d: %s\n", vacunodromo->i_numeroPacientes, datosPacienteEnBd.apellidosNombre);
            break;
        }

        posicionInfoDosis = siguienteLista(datosPacienteEnBd.vacunas, posicionInfoDosis);
    }

    _llenarColaVacunacion(vacunodromo, izqAbb(arbolPacientes));
    _llenarColaVacunacion(vacunodromo, derAbb(arbolPacientes));
}

bool _existeVacuna(TABB arbolPacientes, char nombreVacuna[])
{
    if (esAbbVacio(arbolPacientes))
    {
        return false;
    }

    TIPOELEMENTOABB datosPacienteEnBd;
    leerElementoAbb(arbolPacientes, &datosPacienteEnBd);

    TPOSICION posicionInfoDosis = primeroLista(datosPacienteEnBd.vacunas);
    while (posicionInfoDosis != finLista(datosPacienteEnBd.vacunas))
    {
        TIPOELEMENTOLISTA infoDosis;
        recuperarElementoLista(datosPacienteEnBd.vacunas, posicionInfoDosis, &infoDosis);
        if (strcmp(infoDosis.nombreVacuna, nombreVacuna) == 0)
        {
            return true;
        }

        posicionInfoDosis = siguienteLista(datosPacienteEnBd.vacunas, posicionInfoDosis);
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

    TIPOELEMENTOABB datosPacienteEnBd;
    leerElementoAbb(arbolPacientes, &datosPacienteEnBd);

    _imprimirPaciente(&datosPacienteEnBd);

    fprintf(stdout, "\n");

    _listadoPacientes(derAbb(arbolPacientes), false);


}

bool _eliminarPaciente(TABB *arbolPacientes, TIPOELEMENTOABB pacienteAeliminar)
{
    if (esMiembroAbb(*arbolPacientes, pacienteAeliminar) == false)
    {
        fprintf(stdout, "ERR: eliminarPaciente --> El paciente no existe.\n");
        return false;
    }

    suprimirElementoAbb(arbolPacientes, pacienteAeliminar);

    return true;
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

    if (_eliminarPaciente(arbolPacientes, pacienteAeliminar))
    {
        fprintf(stdout, "INFO: eliminarPaciente --> Paciente '%s' eliminado.\n", pacienteAeliminar.apellidosNombre);
    } else
    {
        fprintf(stdout, "ERR: eliminarPaciente --> NO se ha encontrado ningún paciente llamado '%s'.\n", pacienteAeliminar.apellidosNombre);
    }
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

    FILE *fichero = fopen(argv[2], "r");
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
        fprintf(stdout, "\nNombre paciente: %s\n", elementoArbolInsertar.apellidosNombre);

        char *listaVacunas = strtok(NULL, "|");
        //   fprintf(stdout, "Lista vacunas: %s\n", listaVacunas);

        TIPOELEMENTOLISTA infoDosis;
        crearLista(&elementoArbolInsertar.vacunas);

        char *campo = strtok(listaVacunas, ";");
        while (campo != NULL)
        {
            for (int campoActual = 0; campoActual < 3; campoActual++)
            {
                switch (campoActual)
                {
                    case nombreVacuna:
                        strcpy(infoDosis.nombreVacuna, campo);
                        fprintf(stdout, "Nombre vacuna: %s\n", infoDosis.nombreVacuna);
                        break;
                    case dosisMaximas:
                        infoDosis.i_dosisMaximas = atoi(campo);
                        fprintf(stdout, "Dosis maximas: %d\n", infoDosis.i_dosisMaximas);
                        break;
                    case dosisAdministradas:
                        infoDosis.i_dosisAdministradas = atoi(campo);
                        fprintf(stdout, "Dosis administradas: %d\n", infoDosis.i_dosisAdministradas);
                        break;
                    default:
                        fprintf(stdout, "ERR: cargarArchivo --> Campo no reconocido.\n");
                        break;
                }
                campo = strtok(NULL, ";");
            }
            insertarElementoLista(&elementoArbolInsertar.vacunas, finLista(elementoArbolInsertar.vacunas), infoDosis);
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
    vacunodromo->colaPacientes = NULL;
}

void crearColaVacunacion(VACUNODROMO *vacunodromo, TABB arbolPacientes)
{
    char nombreVacuna[MAXNOMBREVACUNA];

    fprintf(stdout, "    Introduzca el nombre de la vacuna a administrar: ");
    fscanf(stdin, " %[^\n]s", nombreVacuna);

    if (!_existeVacuna(arbolPacientes, nombreVacuna))
    {
        fprintf(stdout, "ERR: crearColaVacunacion --> La vacuna no existe.\n");
        return;
    }

    strncpy(vacunodromo->nombreVacun, nombreVacuna, MAXNOMBREVACUNA);

    fprintf(stdout, "    Nombre del vacunódromo: %s\n", vacunodromo->nombreVacun);

    if (vacunodromo->colaPacientes != NULL)
    {
        destruirCola(&vacunodromo->colaPacientes);
        vacunodromo->colaPacientes = NULL;
    }

    crearCola(&vacunodromo->colaPacientes);

    _llenarColaVacunacion(vacunodromo, arbolPacientes);
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
        fprintf(stdout, "La cola de vacunación de %s está vacía.\n", vacunodromo->nombreVacun);
        return;
    }

    // --

    TIPOELEMENTOCOLA pacienteActual;
    consultarPrimerElementoCola(vacunodromo->colaPacientes, &pacienteActual);


    suprimirElementoCola(&vacunodromo->colaPacientes);

    // --

    bool pacienteConDosisPendientesDeEstaVacuna = false;

    TIPOELEMENTOLISTA infoDosis;
    // Busco la vacuna que se va a administrar al paciente.
    TPOSICION posicionInfoDosis = primeroLista(pacienteActual.vacunas);
    while (true)
    {
        if (posicionInfoDosis == finLista(pacienteActual.vacunas))
        {
            fprintf(stdout, "ERR: El paciente no tiene en su lista de vacunas pendientes la vacuna de %s.\n", vacunodromo->nombreVacun);
            pacienteConDosisPendientesDeEstaVacuna = false;
            break;
        }

        recuperarElementoLista(pacienteActual.vacunas, posicionInfoDosis, &infoDosis);

        if (strcmp(infoDosis.nombreVacuna, vacunodromo->nombreVacun) == 0)
        {
            if (infoDosis.i_dosisAdministradas < infoDosis.i_dosisMaximas)
            {
                pacienteConDosisPendientesDeEstaVacuna = true;
            } else
            {
                pacienteConDosisPendientesDeEstaVacuna = false;
                fprintf(stdout, "ERR: El paciente ya tiene administrado el total de dosis (%d) previstas para él de la vacuna %s.\n", infoDosis.i_dosisMaximas, vacunodromo->nombreVacun);
            }

            break;
        }

        posicionInfoDosis = siguienteLista(pacienteActual.vacunas, posicionInfoDosis);
    }

    // --

    if (pacienteConDosisPendientesDeEstaVacuna)
    {
        // fprintf(stdout, "DEBUG: Voy a actualizar la vacuna %s con valor previo %d y nuevo valor %d\n", infoDosis.nombreVacuna, infoDosis.i_dosisAdministradas, infoDosis.i_dosisAdministradas + 1);

        infoDosis.i_dosisAdministradas++;

        modificarElementoLista(&(pacienteActual).vacunas, posicionInfoDosis, infoDosis);

        fprintf(stdout, "    Vacunando a %s con %s (dosis %d de %d)\n", pacienteActual.apellidosNombre, vacunodromo->nombreVacun, infoDosis.i_dosisAdministradas, infoDosis.i_dosisMaximas);

        if (infoDosis.i_dosisAdministradas < infoDosis.i_dosisMaximas)
        {
            fprintf(stdout, "        INFO: El paciente NO ha sido vacunado completamente de esta vacuna. Se volverá a añadir al final de la cola.\n");
            anadirElementoCola(&vacunodromo->colaPacientes, pacienteActual);
        } else
        {
            pacienteConDosisPendientesDeEstaVacuna = false;
        };
    }

    // --

    // Cuidado, porque esto no se puede mezclar con lo de arriba como un "ELSE".
    if (!pacienteConDosisPendientesDeEstaVacuna)
    {

        fprintf(stdout, "        INFO: El paciente ha sido vacunado completamente de esta vacuna. Se eliminará de su lista de vacunas pendientes.\n");

        suprimirElementoLista(&(pacienteActual).vacunas, posicionInfoDosis);
        vacunodromo->i_numeroPacientes--;

        // --

        if (esListaVacia(pacienteActual.vacunas))
        {
            fprintf(stdout, "        INFO: Además, su lista de vacunas pendientes está vacía. Por lo tanto, se eliminará de la base de datos.\n");

            _eliminarPaciente(arbolPacientes, pacienteActual);
        } else
        {
            fprintf(stdout, "        INFO: Como tiene otras vacunas pendientes, NO se eliminará de la base de datos.\n");
        }
    }
}

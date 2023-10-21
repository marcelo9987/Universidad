/**
 * @file vacunodromo.c
 *
 * @author Marcelo Fort Muñoz
 *
 *
 * @copyright (C) Marcelo Fort Muñoz 2023 (ver .h).
 *
 * @brief Fichero de implementación del TDA (tipo de dato abstracto) vacunodromo.
 *
 * Almacena la implementación de las funciones del TDA vacunódromo.
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vacunodromo.h"

#define MAXLINEA 1000

/// Funciones privadas

/**
 * @brief Elimina un paciente del árbol de pacientes.
 * @param arbolPacientes El árbol de pacientes que contiene al paciente a eliminar.
 * @param pacienteAeliminar  El paciente a eliminar.
 * @return false en caso de que no se haya podido eliminar el paciente. true en caso contrario.
 * @pre El árbol de pacientes debe estar inicializado.
 * @pre El paciente a eliminar debe existir en el árbol de pacientes.
 * @private
 */
bool _eliminarPaciente(TABB *arbolPacientes, TIPOELEMENTOABB pacienteAeliminar)
{
    // Se comprueba que el paciente existe en el arbol. De no ser así, se informa al usuario y se devuelve false.
    if (esMiembroAbb(*arbolPacientes, pacienteAeliminar) == false)
    {
        fprintf(stdout, "ERR: eliminarPaciente --> El paciente no existe.\n");
        return false;
    }

    suprimirElementoAbb(arbolPacientes, pacienteAeliminar);

    return true;
}

/**
 * @brief Comprueba si existe una vacuna en un árbol de pacientes.
 * @param arbolPacientes El árbol de pacientes donde se buscará la vacuna.
 * @param nombreVacuna El nombre de la vacuna a buscar.
 * @return true si la vacuna existe en el árbol de pacientes. false en caso contrario.
 * @pre El árbol de pacientes debe estar inicializado y no ser vacío.
 * @attention Esta función es recursiva.
 * @private
 */
bool _existeVacuna(TABB arbolPacientes, char nombreVacuna[])
{
    // Si el árbol está vacío, no puede tener pacientes. Ergo, no puede tener vacunas.
    if (esAbbVacio(arbolPacientes))
    {
        return false;
    }

    // Creo un contenedor para los datos del paciente y otro para la posición en la lista de vacunas de este.
    TIPOELEMENTOABB datosPacienteEnBd;
    leerElementoAbb(arbolPacientes, &datosPacienteEnBd);

    // Recorro la lista de vacunas del paciente. En caso de encontrar la vacuna, se devuelve true.
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

    // Si no se ha encontrado la vacuna, se busca en los subárboles izquierdo y derecho.
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

/**
 * @brief Imprime por pantalla las vacunas de un paciente.
 * @param listaVacunas La lista de vacunas del paciente.
 * @pre La lista de vacunas debe estar inicializada.
 * @related _imprimirPaciente
 * @private
 */
void _imprimirVacunas(TLISTA listaVacunas)
{
    // Se recorre la lista de vacunas del paciente y se imprimen por pantalla.
    TPOSICION contenedorInfoVacuna = primeroLista(listaVacunas);
    while (contenedorInfoVacuna != finLista(listaVacunas))
    {
        // Se crea un contenedor para la información de la vacuna y se recupera la información de la vacuna en la posición actual.
        // Después se imprime por pantalla y se avanza a la siguiente posición.
        TIPOELEMENTOLISTA infoVacunaEnLista;
        recuperarElementoLista(listaVacunas, contenedorInfoVacuna, &infoVacunaEnLista);
        fprintf(stdout, "\tVacuna: %s  dosis administradas: %d de %d\n", infoVacunaEnLista.nombreVacuna, infoVacunaEnLista.i_dosisAdministradas, infoVacunaEnLista.i_dosisMaximas);
        contenedorInfoVacuna = siguienteLista(listaVacunas, contenedorInfoVacuna);
    }
}

/**
 * @brief Imprime por pantalla los datos de un paciente.
 * @param paciente El paciente del cual se imprimirán los datos.
 * @pre El puntero a paciente DEBE NO apuntar a NULL.
 * @pre El paciente debe existir.
 * @related _listadoPacientes
 * @private
 */
void _imprimirPaciente(TIPOELEMENTOABB *paciente)
{
    fprintf(stdout, "%s\n", (*paciente).apellidosNombre);
    _imprimirVacunas((*paciente).vacunas);
}

/**
 * @brief Recorre un árbol de pacientes en post-orden y guarda los datos de los pacientes en un archivo.
 * @param arbolPacientes El árbol de pacientes del cual se guardarán los datos.
 * @param fichero El fichero donde se guardarán los datos.
 * @pre El árbol de pacientes debe estar inicializado y no ser vacío.
 * @attention Esta función es recursiva.
 * @private
 */
void _recorridoPostOrdenGuardar(TABB arbolPacientes, FILE *fichero)
{
    if (esAbbVacio(arbolPacientes))
    {
//        fprintf(stdout, "ERR: _recorridoPostOrdenGuardar --> El arbol está vacío.\n"); // Para evitar verbosidad he decidido no dar este error.
        return;
    }

    // Los subárboles izquierdo y derecho son recorridos en post-orden.
    _recorridoPostOrdenGuardar(izqAbb(arbolPacientes), fichero);
    _recorridoPostOrdenGuardar(derAbb(arbolPacientes), fichero);

    // Se crea un contenedor para los datos del paciente y se leen los datos del paciente en el árbol.
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
 * @brief Elimina los caracteres de salto de línea de una cadena de caracteres.
 * @param linea La cadena de caracteres de la cual se eliminarán los caracteres de salto de línea y retorno de carro.
 * @private
 */
void _strip_line(char *linea)
{
    linea[strcspn(linea, "\r\n")] = 0;
}

/**
 * @brief Imprime por pantalla los datos de los pacientes de un árbol de pacientes en orden alfabético (inorden).
 * @param arbolPacientes El árbol de pacientes del cual se imprimirán los datos.
 * @param primeraIteracion Un booleano que indica si es la primera iteración de la función.
 * @pre El árbol de pacientes debe estar inicializado y no ser vacío.
 * @attention Esta función es recursiva.
 * @related listadoPacientes
 * @private
 */
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

/**
 * @brief Llena una cola de vacunación con los pacientes que se vacunarán con una vacuna especificada por el usuario.
 * @param vacunodromo El vacunódromo donde se creará la cola de vacunación.
 * @param arbolPacientes El árbol de pacientes del cual se extraerán los pacientes para la cola de vacunación.
 * @pre El vacunódromo debe estar inicializado.
 * @pre El árbol de pacientes debe estar inicializado.
 * @pre El árbol de pacientes debe contener al menos un paciente.
 * @attention Esta función es recursiva.
 * @related crearColaVacunacion
 * @private
 * @note Se imprime por pantalla el nombre de los pacientes que se añaden a la cola de vacunación.
 */
void _llenarColaVacunacion(VACUNODROMO *vacunodromo, TABB arbolPacientes)
{
    if (esAbbVacio(arbolPacientes))
    {
        return;
    }

    TIPOELEMENTOABB datosPacienteEnBd;
    leerElementoAbb(arbolPacientes, &datosPacienteEnBd);

    // Se recorre la lista de vacunas del paciente. En caso de encontrar la vacuna, se añade el paciente a la cola de vacunación.
    TPOSICION posicionInfoDosis = primeroLista(datosPacienteEnBd.vacunas);
    while (posicionInfoDosis != finLista(datosPacienteEnBd.vacunas))
    {
        TIPOELEMENTOLISTA infoDosis;
        recuperarElementoLista(datosPacienteEnBd.vacunas, posicionInfoDosis, &infoDosis);

        if (infoDosis.i_dosisAdministradas < infoDosis.i_dosisMaximas && strcmp(infoDosis.nombreVacuna, vacunodromo->nombreVacun) == 0)
        {
            // Se añade el paciente a la cola de vacunación y se imprime por pantalla.
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

    // No se permite que haya dos pacientes con el mismo nombre. Se comprueba si el paciente ya existe en el árbol.
    if (esMiembroAbb(*arbolPacientes, elementoArbolInsertar) == true)
    {
        fprintf(stdout, "ERR: anhadirPaciente --> El paciente ya existe.\n");
        return;
    }

    crearLista(&elementoArbolInsertar.vacunas);

    TIPOELEMENTOLISTA elementoListaVacunas;

    for (;;)
    {
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

    //en los ifs de C por defecto este evalúa a 0 como false y a cualquier otro valor como true
    if (_eliminarPaciente(arbolPacientes, pacienteAeliminar))
    {
        fprintf(stdout, "INFO: eliminarPaciente --> Paciente '%s' eliminado.\n", pacienteAeliminar.apellidosNombre);
        return;
    }

    fprintf(stdout, "ERR: eliminarPaciente --> NO se ha encontrado ningún paciente llamado '%s'.\n", pacienteAeliminar.apellidosNombre);
}

void cargarArchivo(TABB *arbolPacientes, int argc, char *argv[])
{
    if ((argc != 3) || (strncmp(argv[1], "-f\0", 3) != 0)) // Si el número de argumentos o el formato de los argumentos son incorrectos
    {
        if (argc > 1)
        {
            fprintf(stdout, "Los argumentos no son correctos.\nUso: %s [opciones] [fichero]\n\tOpciones:\n\t-f (opcional) fichero\n", argv[0]);
        }
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

    while ((fgets(linea, MAXLINEA, fichero) != NULL))
    {
        if (linea[0] == '\n' || linea[0] == '\r')
        {
            continue;
        }
        _strip_line(linea);

        TIPOELEMENTOABB elementoArbolInsertar;

        char *nombrePaciente = strtok(linea, "|");
        strcpy(elementoArbolInsertar.apellidosNombre, nombrePaciente);
#if defined DEBUG
        fprintf(stdout, "\nDEBUG:: Nombre paciente: %s\n", elementoArbolInsertar.apellidosNombre);
#endif

        char *listaVacunas = strtok(NULL, "|");
        //   fprintf(stdout, "Lista vacunas: %s\n", listaVacunas);

        TIPOELEMENTOLISTA infoDosis;
        crearLista(&elementoArbolInsertar.vacunas);

        // Con la ayuda de strtok (Que juega con un buffer intermedio) separamos los campos de la lista de vacunas. Es parecido a lo que hacíamos con los CSV.
        char *campo = strtok(listaVacunas, ";");
        while (campo != NULL)
        {
            for (int campoActual = 0; campoActual < 3; campoActual++)
            {
                switch (campoActual)
                {
                    case nombreVacuna:
                        strcpy(infoDosis.nombreVacuna, campo);
#if defined DEBUG
                        fprintf(stdout, "DEBUG:: Nombre vacuna: %s\n", infoDosis.nombreVacuna);
#endif
                        break;
                    case dosisMaximas:
                        infoDosis.i_dosisMaximas = atoi(campo);
#if defined DEBUG
                        fprintf(stdout, "DEBUG:: Dosis maximas: %d\n", infoDosis.i_dosisMaximas);
#endif
                        break;
                    case dosisAdministradas:
                        infoDosis.i_dosisAdministradas = atoi(campo);
#if defined DEBUG
                        fprintf(stdout, "DEBUG:: Dosis administradas: %d\n", infoDosis.i_dosisAdministradas);
#endif
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

    // Llamo a la subrutina privada recursiva.
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
    vacunodromo->colaPacientes = NULL; // He decidido que la cola de pacientes se inicialice a NULL. De esta forma, si se intenta acceder a ella sin haberla creado, se producirá un error.
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

    // Entiendo que llegado a este punto, se quiere una cola nueva... Por lo tanto, si ya existe una cola, se destruye.
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

    // Se comprueba si el paciente tiene dosis pendientes de esta vacuna.
    bool pacienteConDosisPendientesDeEstaVacuna = false;

    TIPOELEMENTOLISTA infoDosis;
    // Busco la vacuna que se va a administrar al paciente.
    TPOSICION posicionInfoDosis = primeroLista(pacienteActual.vacunas);
    while (true)
    {
        if (posicionInfoDosis == finLista(pacienteActual.vacunas))
        {
            // Si ha entrado en este condicional, entonces el paciente no tiene en su lista de vacunas pendientes la vacuna que se le pretende administrar.
            fprintf(stdout, "ERR: El paciente no tiene en su lista de vacunas pendientes la vacuna de %s.\n", vacunodromo->nombreVacun);
            pacienteConDosisPendientesDeEstaVacuna = false;
            break;
        }

        recuperarElementoLista(pacienteActual.vacunas, posicionInfoDosis, &infoDosis);

        // si el nombre de la vacuna coincide con la vacuna que se va a administrar al paciente:
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
#if defined DEBUG
        fprintf(stdout, "DEBUG: Voy a actualizar la vacuna %s con valor previo %d y nuevo valor %d\n", infoDosis.nombreVacuna, infoDosis.i_dosisAdministradas, infoDosis.i_dosisAdministradas + 1);
#endif

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
        }
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

// :> Y así como comenzó, terminó. Con un comentario.

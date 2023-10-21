/**
 * @file vacunodromo.h
 *
 * @author Marcelo Fort Muñoz
 *
 * @version 1.0
 *
 * @copyright (C) Marcelo Fort Muñoz 2023. Todos los derechos GNU GPL.
 *
 * @brief En esta librería se encuentran las funciones que gestionan el vacunódromo. (Tipo de dato abstracto)
 *
 * @note Esta librería requiere de la biblioteca de árboles binarios de búsqueda y la librería de colas provistas, de las cuales no se atribuye autoría ni licencia.
 *      Estas corrresponderan únicamente a aquellos que las hayan desarrollado.
 */

#ifndef ENTREGAPRACTICA3_VACUNODROMO_H
#define ENTREGAPRACTICA3_VACUNODROMO_H

#include "abb.h" //requiere la biblioteca de árboles binarios de búsqueda provista
#include "cola.h" // requiere la biblioteca de colas provista

/**
 * @brief Estructura que conforma un vacunódromo.
 * @var nombreVacunodromo Nombre del vacunódromo.
 * @var i_numeroPacientes Número de pacientes que se vacunarán en el vacunódromo.
 * @var colaPacientes Cola (con sus respectivas vacunas y número de dosis/dosis restantes) de pacientes que se vacunarán en el vacunódromo.
 */
typedef struct
{
    char nombreVacun[MAXNOMBREVACUNA];
    int i_numeroPacientes;
    TCOLA colaPacientes;
} VACUNODROMO;

/**
 * Añade un paciente al arbol de pacientes
 * @param arbolPacientes El arbol de pacientes
 * @pre El arbol de pacientes debe estar inicializado.
 * @pre El paciente no debe existir en el arbol de pacientes.
 */
void anhadirPaciente(TABB *arbolPacientes);

/**
 * @brief Carga los datos de los pacientes desde un archivo.
 * @param arbolPacientes El arbol de pacientes donde se cargarán los datos.
 * @param argc El número de argumentos pasados al programa.
 * @param argv Los argumentos pasados al programa.
 */
void cargarArchivo(TABB *arbolPacientes, int argc, char *argv[]);

/**
 * @brief Crea una cola de vacunación en base a una vacuna especificada por el usuario. En esta estarán los pacientes que se vacunarán con dicha vacuna.
 * @param vacunodromo El vacunodromo donde se creará la cola de vacunación.
 * @param arbolPacientes El arbol de pacientes del cual se extraerán los pacientes para la cola de vacunación.
 * @pre El vacunodromo debe estar inicializado.
 * @pre El arbol de pacientes debe estar inicializado.
 * @pre El arbol de pacientes debe contener al menos un paciente.
 */
void crearColaVacunacion(VACUNODROMO *vacunodromo, TABB arbolPacientes);

/**
 * @brief Elimina un paciente del arbol de pacientes.
 * @param arbolPacientes El arbol de pacientes del cual se eliminará el paciente.
 * @pre El arbol de pacientes debe estar inicializado.
 */
void eliminarPaciente(TABB *arbolPacientes);

/**
 * @brief Guarda los datos de los pacientes en un archivo en postorden.
 * @param arbolPacientes El arbol de pacientes del cual se guardarán los datos.
 * @param nombreArchivo El nombre del archivo donde se guardarán los datos.
 */
void guardarArchivo(TABB arbolPacientes, char *nombreArchivo);

/**
 * @brief Inicializa el vacunodromo.
 * @param vacunodromo El vacunodromo a inicializar.
 */
void inicializarVacundromo(VACUNODROMO *vacunodromo);

/**
 * @brief Muestra por pantalla los datos de los pacientes del arbol de pacientes.
 * @param arbolPacientes El arbol de pacientes del cual se imprimirán los datos.
 * @pre El arbol de pacientes debe estar inicializado.
 */
void listadoPacientes(TABB arbolPacientes);

void vacunarPrimerPaciente(VACUNODROMO *vacunodromo, TABB *arbolPacientes);

#endif //ENTREGAPRACTICA3_VACUNODROMO_H

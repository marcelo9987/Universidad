/*
 * archivo: vacunodromo.h
 * Autor: Marcelo Fort Muñoz
 */
#ifndef ENTREGAPRACTICA3_VACUNODROMO_H
#define ENTREGAPRACTICA3_VACUNODROMO_H

#include "abb.h"
#include "cola.h"

typedef struct
{
    char nombreVacun[MAXNOMBREVACUNA];
    int i_numeroPacientes;
    TCOLA colaPacientes;
}VACUNODROMO;

/**
 * Añade un paciente al arbol de pacientes
 * @param arbolPacientes El arbol de pacientes
 * @pre El arbol de pacientes debe estar inicializado.
 */
void anhadirPaciente(TABB* arbolPacientes);

/**
 * @brief Muestra por pantalla los datos de los pacientes del arbol de pacientes.
 * @param arbolPacientes El arbol de pacientes del cual se imprimirán los datos.
 * @pre El arbol de pacientes debe estar inicializado.
 */
void listadoPacientes(TABB arbolPacientes, bool primeraIteracion);

/**
 * @brief Elimina un paciente del arbol de pacientes.
 * @param arbolPacientes El arbol de pacientes del cual se eliminará el paciente.
 * @pre El arbol de pacientes debe estar inicializado.
 */
void eliminarPaciente(TABB *arbolPacientes);

/**
 * @brief Carga los datos de los pacientes desde un archivo.
 * @param arbolPacientes El arbol de pacientes donde se cargarán los datos.
 * @param argc El número de argumentos pasados al programa.
 * @param argv Los argumentos pasados al programa.
 */
void cargarArchivo(TABB *arbolPacientes, int argc, char *argv[]);
/**
 * @brief Guarda los datos de los pacientes en un archivo en postorden.
 * @param arbolPacientes El arbol de pacientes del cual se guardarán los datos.
 * @param nombreArchivo El nombre del archivo donde se guardarán los datos.
 */
void guardarArchivo(TABB arbolPacientes, char *nombreArchivo);

/**
 * @brief Crea una cola de vacunación en base a una vacuna especificada por el usuario. En esta estarán los pacientes que se vacunarán con dicha vacuna.
 * @param vacunodromo El vacunodromo donde se creará la cola de vacunación.
 * @param arbolPacientes El arbol de pacientes del cual se extraerán los pacientes para la cola de vacunación.
 * @pre El vacunodromo debe estar inicializado.
 * @pre El arbol de pacientes debe estar inicializado.
 * @pre El arbol de pacientes debe contener al menos un paciente.
 */
void crearColaVacunacion(VACUNODROMO *vacunodromo, TABB arbolPacientes);

#endif //ENTREGAPRACTICA3_VACUNODROMO_H

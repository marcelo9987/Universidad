/*
 * archivo: vacunodromo.h
 * Autor: Marcelo Fort Muñoz
 */
#ifndef ENTREGAPRACTICA3_VACUNODROMO_H
#define ENTREGAPRACTICA3_VACUNODROMO_H

#include "abb.h"

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

void guardarArchivo(TABB arbolPacientes, char *nombreArchivo);

#endif //ENTREGAPRACTICA3_VACUNODROMO_H

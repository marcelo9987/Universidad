/*
 * archivo: vacunodromo.h
 * Autor: Marcelo Fort Muñoz
 */
#ifndef ENTREGAPRACTICA3_VACUNODROMO_H
#define ENTREGAPRACTICA3_VACUNODROMO_H

#include <stdbool.h>
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

#endif //ENTREGAPRACTICA3_VACUNODROMO_H

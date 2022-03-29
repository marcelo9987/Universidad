#include "./TAD/cola.h"

#define MAX_NOMBREVACUNODROMO_LEN 40

typedef struct
{
    char nombreVacunodromo[MAX_NOMBREVACUNODROMO_LEN];
    int numPacientesCola;
    TCOLA pacientes;
} VACUNODROMO;

typedef VACUNODROMO* PVACUNODROMO;

/**
 * Crea un vacunódromo y lo asigna a un puntero a PVACUNODROMO
 *
 * @param vacunodromo
 * @param nombreVacunodromo
 */
void crear_vacunodromo(PVACUNODROMO* vacunodromo, char nombreVacunodromo[]);

/**
 * Añade un paciente al vacunódromo
 *
 * @param vacunodromo
 */
void anadir_paciente(PVACUNODROMO* vacunodromo);

/**
 * Vacuna una paciente y lo manda al final de la cola.
 * Si el paciente ha recibido ya todas sus vacunas, este es eliminado de la cola.
 *
 * @param vacunodromo
 */
void vacunar_paciente(PVACUNODROMO* vacunodromo);


void destruir_paciente(PVACUNODROMO* vacunodromo);

/**
 *  Destruye al vacunódromo y a todos sus elementos
 *
 * @param vacunodromo
 */
void destruir_vacunodromo(PVACUNODROMO* vacunodromo);

/**
 * Imprime los pacientes restantes en el vacunódromo e imprime al primer paciente con toda su información
 * @param vacunodromo
 */
void imprimir(PVACUNODROMO vacunodromo);

void imprimir_paciente(PVACUNODROMO vacunodromo);

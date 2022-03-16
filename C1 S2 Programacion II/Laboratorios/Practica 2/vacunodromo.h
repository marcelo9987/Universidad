//#include "./TAD/lista.h"
#include "./TAD/cola.h"

#define MAX_NOMBREVACUNODROMO_LEN 40

typedef struct
{
    char nombreVacunodromo[MAX_NOMBREVACUNODROMO_LEN];
    int numPacientesCola;
    TCOLA pacientes;
} VACUNODROMO;

typedef VACUNODROMO* PVACUNODROMO;

void crear_vacunodromo(PVACUNODROMO* vacunodromo, char nombreVacunodromo[]);

void destruir_paciente(PVACUNODROMO* vacunodromo);

void destruir_vacunodromo(PVACUNODROMO* vacunodromo);

void anadir_paciente(PVACUNODROMO* vacunodromo);



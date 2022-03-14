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

void crear_vacunodromo(VACUNODROMO* vacunodromo, char nombreVacunodromo[]);

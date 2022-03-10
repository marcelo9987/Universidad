#define NAME_MAX_LENGTH 32
#include "./TAD/lista.h"
#include "./TAD/cola.h"

typedef struct
{
    char nombreVacunodromo[NAME_MAX_LENGTH];
    int numeroPacientes;
    TCOLA pacientes;
}vacunodromo;
void createVacunodromo(vacunodromo* vac1,char location[MAX_NAME_LENGTH]);
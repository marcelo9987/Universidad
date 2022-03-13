#include <stdlib.h>

//#include "./vacunodromo.h"
//TODO ¿Puedo usar vacunodromo.h?
//#error .

#include "./TAD/cola.h"

#define MAX_NOMBREVACUNODROMO_LEN 40

typedef struct
{
    char nombreVacunodromo[MAX_NOMBREVACUNODROMO_LEN];
    int numPacientesCola;
    TCOLA pacientes;
} VACUNODROMO;

/*
void createVacunodromo(vacunodromo* vac1, char location[NAME_MAX_LENGTH])
{
    if (!vac1)
    {
        destruirCola(vac1->pacientes);
        free (vac1);
    }
    vac1 = (vacunodromo*) malloc(sizeof(vacunodromo));
}

void removeVacunodromo(vacunodromo* vac1)
{
    destruirCola(vac1->pacientes);
    free (vac1);

}
*/

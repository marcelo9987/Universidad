#include <stdlib.h>
#include "./vacunodromo.h"

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
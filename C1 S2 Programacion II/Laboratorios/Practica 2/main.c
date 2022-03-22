#include <stdio.h>
#include <string.h>
#include "./TAD/cola.h"
#include "./TAD/lista.h"
#include "vacunodromo.h"


void menu();

int main()
{
    menu();
    return 0;
}

void menu()
{
    /****/
    char nombreVacunodromo[MAX_NOMBREVACUNODROMO_LEN];
    PVACUNODROMO vacunodromo;
    printf("Introduce el nombre del vacunódromo: ");
    scanf("%[^\n]s", nombreVacunodromo);
//    wprintf(L"%s",nombreVacunodromo);
    /****/

    crear_vacunodromo(& vacunodromo, nombreVacunodromo);


    char sel = '\0';
    do
    {
        printf("\n                Vacunódromo %s\n", nombreVacunodromo);
        printf("Opciones:\n");
        printf("1. Imprimir vacunódromo\n");
        printf("2. Vacunar siguiente paciente\n");
        printf("3. Añadir paciente\n");
        printf("0. Salir\n");

        printf("Selección: ");
        scanf(" %c", & sel);

        printf("\n");
        switch (sel)
        {
            case '1':
                imprimir(vacunodromo);

                break;

            case '2':
                vacunar_paciente(& vacunodromo);
                break;

            case '3':
                anadir_paciente(& vacunodromo);
                break;

            case '0':
                destruir_vacunodromo(& vacunodromo);
                break;
            default:
                break;
        }
    } while (sel != '0');
}

#include <stdio.h>
#include <string.h>
#include "./TAD/cola.h"
#include "./TAD/lista.h"
#include "vacunodromo.h"

VACUNODROMO prueba;

void menu();

int main()
{
    menu();
    return 0;
}

void menu()
{
    /****/
    PVACUNODROMO vacunodromo;
    crear_vacunodromo(& vacunodromo, "casaMarcelo");
    /****/
    char sel ='\0';
    do
    {
        printf("                MENU VACUNÓDROMO\n");
        printf("Opciones:\n");
        printf("1. Añadir paciente\n");
        printf("2. Vacunar siguiente paciente\n");
        printf("3. Imprimir vacunódromo\n");
        printf("4. Salir\n\n");

        printf("Selección: ");


        scanf(" %c", & sel);

        switch (sel)
        {
            case '1':
                anadir_paciente(& vacunodromo);
                break;

            case '2':
//            vacunar_paciente();
                break;

            case '3':
                imprimir(vacunodromo);
                break;

            case '4':
                destruir_vacunodromo (&vacunodromo);
                break;
            default:
                break;
        }
    } while (sel != '4');
}

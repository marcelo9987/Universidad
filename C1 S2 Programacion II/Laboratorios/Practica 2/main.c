#include <stdio.h>
#include <string.h>
#include "./TAD/cola.h"
#include "./TAD/lista.h"
#include "vacunodromo.h"
#include <locale.h>
#include <wchar.h>
VACUNODROMO prueba;

void menu();

int main()
{
    setlocale(LC_ALL,"");
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
        wprintf(L"\n                MENU VACUNÓDROMO\n");
        wprintf(L"Opciones:\n");
        wprintf(L"1. Añadir paciente\n");
        wprintf(L"2. Vacunar siguiente paciente\n");
        wprintf(L"3. Imprimir vacunódromo\n");
        wprintf(L"4. Salir\n\n");

        wprintf(L"Selección: ");


        scanf(" %c", & sel);

        switch (sel)
        {
            case '1':
                anadir_paciente(& vacunodromo);
                break;

            case '2':
            vacunar_paciente(&vacunodromo);
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

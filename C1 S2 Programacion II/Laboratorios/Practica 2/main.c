#include <stdio.h>
#include <string.h>
#include "./TAD/cola.h"
#include "./TAD/lista.h"
#include "vacunodromo.h"
#include <locale.h>
#include <wchar.h>

void menu();

int main()
{
    setlocale(LC_ALL, "");
    menu();
    return 0;
}

void menu()
{
    /****/
    char nombreVacunodromo[MAX_NOMBREVACUNODROMO_LEN];
    PVACUNODROMO vacunodromo;
    wprintf(L"Introduce el nombre del vacunódromo(Se aceptan caracteres especiales): ");
    wscanf(L"%[^\n]s", nombreVacunodromo);
//    wprintf(L"%s",nombreVacunodromo);
    /****/

    crear_vacunodromo(& vacunodromo, nombreVacunodromo);


    char sel = '\0';
    do
    {
        wprintf(L"\n                Vacunódromo %s\n", nombreVacunodromo);
        wprintf(L"Opciones:\n");
        wprintf(L"1. Imprimir vacunódromo\n");
        wprintf(L"2. Vacunar siguiente paciente\n");
        wprintf(L"3. Añadir paciente\n");
        wprintf(L"0. Salir\n");

        wprintf(L"Selección: ");
        wscanf(L" %c", & sel);

        wprintf(L"\n");
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

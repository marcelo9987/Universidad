#include <stdio.h>
#include "abb.h"
#include <stdbool.h>
#include "vacunodromo.h"

int main()
{
    TABB arbolPacientes;
    crearAbb(&arbolPacientes);
    bool salir = false;
    do
    {
        fprintf(stdout, "\n");
        fprintf(stdout, "Menu de gestion del vacunodromo\n");
        fprintf(stdout, "A. Añadir pacientes\n");
        fprintf(stdout, "L. Listar pacientes\n");
        fprintf(stdout, "E. Eliminar paciente\n");
        fprintf(stdout, "S. Salir\n");

        fprintf(stdout, "Introduzca una opcion: ");

        char opcion = getchar();
        while (getchar() != '\n');// Limpiar buffer

        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'A':
            case 'a':
                anhadirPaciente(&arbolPacientes);
                break;

            case 'L':
            case 'l':
                listadoPacientes(arbolPacientes,true);
                break;

            case 'E':
            case 'e':
                eliminarPaciente(&arbolPacientes);
                break;

            case 'S':
            case 's':
                //elimino el arbol
                destruirAbb(&arbolPacientes);
                salir = true;
                break;

            default:
                fprintf(stdout, "ERR: Opcion %c no valida. \a \n", opcion);
                break;
        }

    } while (salir == false);

}

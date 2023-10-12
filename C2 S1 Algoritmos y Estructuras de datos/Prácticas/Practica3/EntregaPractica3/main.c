#include <stdio.h>
#include "abb.h"
#include <stdbool.h>
#include <string.h>
#include "vacunodromo.h"

int main(int argc, char *argv[])
{

    TABB arbolPacientes;
    crearAbb(&arbolPacientes);

    cargarArchivo(&arbolPacientes, argc, argv);

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
        char opcion;
        scanf(" %c", &opcion);
        /*char opcion = getchar();
        while (getchar() != '\n')
        {}// Limpiar buffer*/

        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'A':
            case 'a':
                anhadirPaciente(&arbolPacientes);
                break;

            case 'L':
            case 'l':
                listadoPacientes(arbolPacientes, true);
                break;

            case 'E':
            case 'e':
                eliminarPaciente(&arbolPacientes);
                break;

            case 'S':
            case 's':
                salir = true;
                break;

            default:
                fprintf(stdout, "ERR: Opcion %c no valida. \a \n", opcion);
                break;
        }

    } while (salir == false);

    if(argc > 2)
    {
        guardarArchivo(arbolPacientes, argv[2]);
        //elimino el arbol
        destruirAbb(&arbolPacientes);
        return 0;
    }

    char respuesta = '\0';
    do
    {
        fprintf(stdout, "El programa no ha podido detectar el archivo de pacientes. Desea crear uno nuevo? (S/N): ");

        fscanf(stdout, " %1c", &respuesta);

    } while (respuesta != 'S' && respuesta != 's' && respuesta != 'N' && respuesta != 'n');

    switch (respuesta)
    {
        char nombreArchivo[FILENAME_MAX];

        case 'S':
        case 's':

            fprintf(stdout, "Introduzca un nombre para el archivo: ");
            fscanf(stdin, " %[^\n]s", nombreArchivo);
            guardarArchivo(arbolPacientes, nombreArchivo);

            break;
        default:
            break;
    }
    //elimino el arbol
    destruirAbb(&arbolPacientes);
    return 0;

}

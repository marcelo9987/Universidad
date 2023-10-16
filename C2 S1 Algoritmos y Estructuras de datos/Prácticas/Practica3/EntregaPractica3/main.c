#include <stdio.h>
#include "abb.h"
#include <stdbool.h>
#include "vacunodromo.h"

/**
 *  Llama a una función para la administración de la base de datos del vacunódromo en función de la opción elegida por el usuario.
 * @param arbolPacientes El arbol de pacientes que contiene la base de datos.
 * @param salir Un puntero a una variable booleana que indica si el usuario ha elegido salir del programa.
 */
void gestorBaseDatos(TABB *arbolPacientes, bool *salir)
{
    char opcion = '\0';
    do
    {
        fprintf(stdout, "\n");
        fprintf(stdout, "Menu de gestión de la base de datos\n");
        fprintf(stdout, "A. Añadir pacientes\n");
        fprintf(stdout, "L. Listar pacientes\n");
        fprintf(stdout, "E. Eliminar paciente\n");
        fprintf(stdout, "S. Salir\n");

        fprintf(stdout, "Introduzca una opción: ");
        scanf(" %1c", &opcion);
    }while(opcion != 'A' && opcion != 'a' && opcion != 'L' && opcion != 'l' && opcion != 'E' && opcion != 'e' && opcion != 'S' && opcion != 's');

    fprintf(stdout, "\n");

    switch (opcion)
    {
        case 'A':
        case 'a':
            anhadirPaciente(arbolPacientes);
            break;

        case 'L':
        case 'l':
            listadoPacientes((*arbolPacientes), true);
            break;

        case 'E':
        case 'e':
            eliminarPaciente(arbolPacientes);
            break;

        case 'S':
        case 's':
            (*salir) = true;
            break;

        default:
            fprintf(stdout, "ERR: Opcion %c no valida. \a \n", opcion);
            break;
    }
}

int main(int argc, char *argv[])
{

    TABB arbolPacientes;
    crearAbb(&arbolPacientes);

    cargarArchivo(&arbolPacientes, argc, argv);

    bool salir = false;
    do
    {
        char baseOvacunodromo = '\0';
        do
        {
            fprintf(stdout, "\n");
            fprintf(stdout, "Bienvenido al gestor del vacunódromo\n");
            fprintf(stdout, "====================================\n");
            fprintf(stdout, "A. Gestión de la base de datos\n");
            fprintf(stdout, "B. Gestión del vacunódromo\n");
            fprintf(stdout, "S. Salir\n");
            fscanf(stdin, " %1c", &baseOvacunodromo);
        }while(baseOvacunodromo != 'A' && baseOvacunodromo != 'a' && baseOvacunodromo != 'B' && baseOvacunodromo != 'b' && baseOvacunodromo != 'S' && baseOvacunodromo != 's');

        fprintf(stdout, "\n");

        switch(baseOvacunodromo)
        {
            case 'A':
            case 'a':
                gestorBaseDatos(&arbolPacientes, &salir);
                break;
            case 'B':
            case 'b':
                break;
            case 'S':
            case 's':
                salir = true;
                break;
            default:
                fprintf(stdout, "ERR: Opcion %c no valida. \a \n", baseOvacunodromo);
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

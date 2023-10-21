#include <stdio.h>
#include "abb.h"
#include <stdbool.h>
#include "vacunodromo.h"


bool esOpcionCorrecta(char opcion, int menuSeleccion)
{
    enum opcionesMenu
    {
        MENU_PRINCIPAL = 0,
        MENU_BASEDATOS = 1,
        MENU_VACUNODROMO = 2,
        MENU_SALIR = 3

    };
    switch (menuSeleccion)
    {
        case MENU_PRINCIPAL:
            return (opcion == 'A' || opcion == 'a' || opcion == 'B' || opcion == 'b' || opcion == 'S' || opcion == 's');
        case MENU_BASEDATOS:
            return (opcion == 'A' || opcion == 'a' || opcion == 'L' || opcion == 'l' || opcion == 'E' || opcion == 'e' || opcion == 'S' || opcion == 's');
        case MENU_VACUNODROMO:
            return (opcion == 'C' || opcion == 'c' || opcion == 'V' || opcion == 'v' || opcion == 'S' || opcion == 's');
        case MENU_SALIR:
            return (opcion == 'S' || opcion == 's' || opcion == 'N' || opcion == 'n');
        default:
            return false;


    }

}

/**
 *  Llama a una función para la administración de la base de datos del vacunódromo en función de la opción elegida por el usuario.
 * @param arbolPacientes El arbol de pacientes que contiene la base de datos.
 * @param salir Un puntero a una variable booleana que indica si el usuario ha elegido salir del programa.
 */
void gestorBaseDatos(TABB *arbolPacientes)
{
    bool salir = false;
    do
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
        } while (!esOpcionCorrecta(opcion, 1));

        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'A':
            case 'a':
                anhadirPaciente(arbolPacientes);
                break;

            case 'L':
            case 'l':
                listadoPacientes((*arbolPacientes));
                break;

            case 'E':
            case 'e':
                eliminarPaciente(arbolPacientes);
                break;

            case 'S':
            case 's':
                salir = true;
                break;

            default:
                fprintf(stdout, "ERR: Opción %c no válida.\n", opcion);
                break;
        }
    } while (salir == false);
}

void gestorVacunodromo(VACUNODROMO *vacunodromoActual, TABB arbolPacientes)
{
    bool salir = false;
    do
    {
        char opcion = '\0';
        do
        {
            fprintf(stdout, "\n");
            fprintf(stdout, "Menu de gestión del vacunódromo\n");
            fprintf(stdout, "C. Crear cola de vacunacion\n");
            fprintf(stdout, "V. Vacunar\n");
            fprintf(stdout, "S. Salir\n");

            fprintf(stdout, "Introduzca una opción: ");
            fscanf(stdin, " %1c", &opcion);
        } while (!esOpcionCorrecta(opcion, 2));
        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'C':
            case 'c':
                crearColaVacunacion(vacunodromoActual, arbolPacientes);
                break;
            case 'V':
            case 'v':
                if (vacunodromoActual->colaPacientes == NULL)
                {
                    fprintf(stdout, "ERR: No hay ninguna cola de vacunación creada.\n");
                } else
                {
                    vacunarPrimerPaciente(vacunodromoActual, &arbolPacientes);
                }

                break;
            case 'S':
            case 's':
                salir = true;
                break;
            default:
                fprintf(stdout, "ERR: Opción %c no válida.\n", opcion);
                break;
        }
    } while (salir == false);
}

int main(int argc, char *argv[])
{

    TABB arbolPacientes;
    crearAbb(&arbolPacientes);
    cargarArchivo(&arbolPacientes, argc, argv);

    VACUNODROMO vacunodromo;
    inicializarVacundromo(&vacunodromo);

    bool salir = false;
    do
    {
        char opcion = '\0';
        do
        {
            fprintf(stdout, "\n");
            fprintf(stdout, "Bienvenido al menú del sistema de gestión de vacunas y vacunódromos\n");
            fprintf(stdout, "====================================\n");
            fprintf(stdout, "A. Gestión de la base de datos\n");
            fprintf(stdout, "B. Gestión del vacunódromo\n");
            fprintf(stdout, "S. Salir\n");

            fprintf(stdout, "Introduzca una opción: ");
            fscanf(stdin, " %1c", &opcion);
        } while (!esOpcionCorrecta(opcion, 0));

        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'A':
            case 'a':
                gestorBaseDatos(&arbolPacientes);
                break;
            case 'B':
            case 'b':
                gestorVacunodromo(&vacunodromo, arbolPacientes);
                break;
            case 'S':
            case 's':
                salir = true;
                break;
            default:
                fprintf(stdout, "ERR: Opción %c no válida.\n", opcion);
                break;
        }
    } while (salir == false);

    if (argc > 2)
    {
        guardarArchivo(arbolPacientes, argv[2]);
        fprintf(stdout, "INFO: Archivo guardado con éxito.\n");

        //elimino el arbol
        destruirAbb(&arbolPacientes);
        // destruyo el vacunodromo (libero su cola)
        destruirCola(&vacunodromo.colaPacientes);

        fprintf(stdout, "INFO: Programa finalizado con éxito.\n");
        return 0;
    }

    char respuesta = '\0';
    do
    {
        fprintf(stdout, "El programa no ha podido detectar el archivo de pacientes. Desea crear uno nuevo? (S/N): ");

        fscanf(stdin, " %1c", &respuesta);

    } while (!esOpcionCorrecta(respuesta, 3));

    switch (respuesta)
    {
        char nombreArchivo[FILENAME_MAX];

        case 'S':
        case 's':

            fprintf(stdout, "Introduzca un nombre para el archivo: ");
            fscanf(stdin, " %[^\n]s", nombreArchivo);
            guardarArchivo(arbolPacientes, nombreArchivo);
            fprintf(stdout, "Archivo guardado con éxito.\n");
            break;
        default:
            break;
    }
    //elimino el arbol
    destruirAbb(&arbolPacientes);
    // destruyo el vacunodromo (libero su cola)
    destruirCola(&vacunodromo.colaPacientes);
    fprintf(stdout, "INFO: Programa finalizado con éxito.\n");
    return 0;
}

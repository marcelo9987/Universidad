#include <stdio.h>
#include "abb.h"
#include <stdbool.h>
#include "vacunodromo.h"

enum opcionesMenu
{
    MENU_PRINCIPAL,
    MENU_BASEDATOS,
    MENU_VACUNODROMO,
    MENU_SALIR
};

bool esOpcionCorrecta(char opcion, enum opcionesMenu menuSeleccion)
{

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
            fscanf(stdin, " %1c", &opcion);
        } while (!esOpcionCorrecta(opcion, MENU_BASEDATOS));

        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'A':
            case 'a':
                anhadirPaciente(arbolPacientes);
                break;

            case 'L':
            case 'l':
                listadoPacientes(*arbolPacientes);
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

void gestorVacunodromo(VACUNODROMO *vacunodromoActual, TABB *arbolPacientes)
{
    bool salir = false;
    do
    {
        char opcion = '\0';
        do
        {
            fprintf(stdout, "\n");
            fprintf(stdout, "Menu de gestión del vacunódromo\n");
            fprintf(stdout, "C. Crear cola de vacunación\n");
            fprintf(stdout, "V. Vacunar\n");
            fprintf(stdout, "S. Salir\n");

            fprintf(stdout, "Introduzca una opción: ");
            fscanf(stdin, " %1c", &opcion);
        } while (!esOpcionCorrecta(opcion, MENU_VACUNODROMO));
        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'C':
            case 'c':
                crearColaVacunacion(vacunodromoActual, *arbolPacientes);
                break;
            case 'V':
            case 'v':
                if (vacunodromoActual->colaPacientes == NULL)
                {
                    fprintf(stdout, "ERR: No hay ninguna cola de vacunación creada.\n");
                } else
                {
                    vacunarPrimerPaciente(vacunodromoActual, arbolPacientes);
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
            fprintf(stdout, "Bienvenid@ al menú del sistema de gestión de vacunas y vacunódromos\n");
            fprintf(stdout, "====================================\n");
            fprintf(stdout, "A. Gestión de la base de datos\n");
            fprintf(stdout, "B. Gestión del vacunódromo\n");
            fprintf(stdout, "S. Salir\n");

            fprintf(stdout, "Introduzca una opción: ");
            fscanf(stdin, " %1c", &opcion);
        } while (!esOpcionCorrecta(opcion, MENU_PRINCIPAL));

        fprintf(stdout, "\n");

        switch (opcion)
        {
            case 'A':
            case 'a':
                gestorBaseDatos(&arbolPacientes);
                break;
            case 'B':
            case 'b':
                gestorVacunodromo(&vacunodromo, &arbolPacientes);
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


    // Guardmos el árbol de pacientes en un archivo.
    if (argc >= 3)
    {
        // Si se ha pasado un archivo de pacientes como argumento, se guarda el árbol de pacientes en dicho archivo.
        guardarArchivo(arbolPacientes, argv[2]);
        fprintf(stdout, "INFO: Archivo guardado con éxito.\n");

    } else {

        // Si no se ha pasado un archivo de pacientes como argumento, se le pregunta al usuario si desea crear uno nuevo.

        char respuesta = '\0';
        do
        {
            fprintf(stdout, "El programa no ha podido detectar el archivo de pacientes. Desea crear uno nuevo? (S/N): ");

            fscanf(stdin, " %c", &respuesta);

        } while (!esOpcionCorrecta(respuesta, MENU_SALIR));

        char nombreArchivo[FILENAME_MAX];

        switch (respuesta)
        {
            case 'S':
            case 's':

                fprintf(stdout, "Introduzca un nombre para el archivo: ");
                fscanf(stdin, " %[^\n]s", nombreArchivo);

                guardarArchivo(arbolPacientes, argv[2]);
                fprintf(stdout, "INFO: Archivo guardado con éxito.\n");
                break;
            default:
                break;
        }
    }

    //elimino el árbol
    destruirAbb(&arbolPacientes);

    // destruyo el vacunódromo (libero su cola)
    destruirCola(&vacunodromo.colaPacientes);

    fprintf(stdout, "INFO: Programa finalizado con éxito.\n");

    return 0;

}

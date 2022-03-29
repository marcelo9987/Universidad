#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vacunodromo.h"


void menu();

int main(int argc, char* argv[])
{

    if(argc>2)
    {
       if(strcmp(argv[1],"-f")==0)
       {

               char linea[200];

               FILE* Parchivo;

               TIPOELEMENTOCOLA paciente;
               TIPOELEMENTOLISTA nuevaVacuna;

               Parchivo=fopen(argv[2],"rt");
               fgets(linea,200,Parchivo);
               char* nombre = strtok(linea,"|");
               char* vac = strtok(NULL,";");
               char* vacMax= strtok(NULL,";");
               int vacMax2 = atoi(vacMax);
               printf("\nNombre:%s\n",nombre);
               printf("\nVac:%s\n",vac);
               printf("\nVacMax:%i\n",vacMax2);

       }
    }
    /*
    menu();
    */
    return 0;
}



void menu()
{
    /****/
    char nombreVacunodromo[MAX_NOMBREVACUNODROMO_LEN];
    PVACUNODROMO vacunodromo;
    printf("Introduce el nombre del vacunódromo: ");
    scanf("%[^\n]s", nombreVacunodromo);
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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "tabla_hash_encadenamiento.h"


//Hay que añadir como parámetro la variable nColisionesI: número de colisiones en inserción
void insercionArchivo(FILE *fp, TablaHash *t, unsigned int tipo, unsigned int K, unsigned int *nColisionesI, enum CampoBusqueda campoBusqueda);

//Hay que añadir como parámetro la variable nPasosExtraB: número de pasos extra en búsqueda
void busquedaArchivo(FILE *fp, TablaHash t, unsigned int tipo, unsigned int K, unsigned int *nPasosExtraB, enum CampoBusqueda campoBusqueda);

int main(int argc, char **argv)
{
    //variable que almacenan el tipo de función hash (1-2-3)
    unsigned int tipoFH;
    unsigned int K = 256; //factor de ponderación para hash por suma ponderada

    enum CampoBusqueda campoBusqueda;

    TablaHash t; //tabla hash

    //////////////////////////////////////////////////////////////////////
    //Inicializar a 0 las variables nColisionesI y nPasosExtraB
    //////////////////////////////////////////////////////////////////////
    unsigned int nColisionesI = 0;
    unsigned int nPasosExtraB = 0;


    //Abrimos el fichero de datos de ejemplo, con 10000 jugadores
    FILE *fp = fopen("pacientes_vacunodromo.txt", "rt");

    //--

    bool modoInteractivo = (argc == 1);

    //--

    //Informo del tamaño de la tabla actual
    /* printf("Tamaño de la tabla hash: %d\n\n", N); */
    printf("N:%u, ", N);

    //--

    if (modoInteractivo)
    {
        //Pregunto al usuario que función hash quiere utilizar
        printf("\tFunción hash a utilizar:"
               "\n\t\t1: método división (suma ascii módulo N)"
               "\n\t\t2: suma ponderada con K=256"
               "\n\t\t3: suma ponderada con otro valor de K ");

        printf("\n\tTipo función hash: ");

        scanf("%u", &tipoFH);
    } else
    {
        tipoFH = atoi(argv[1]);
    }

    //--

    if (tipoFH == 3)
    {
        if (modoInteractivo)
        {
            printf("\t\tValor de ponderación K (256): ");
            scanf("%d", &K);
        } else if (argc < 3)
        {
            printf("Error: Faltan argumentos (K)\n");
            exit(1);
        } else
        {
            K = atoi(argv[2]);
        }
    }

    /* printf("\nFUNCIÓN HASH %u", tipoFH); */
    printf("FH:%u, ", tipoFH);

    //--

    if (tipoFH == 2 || tipoFH == 3)
    {
        printf("K:%u, ", K);
    } else
    {
        printf("K:-, ");
    }

    //--

    if (modoInteractivo)
    {
        //Pregunto al usuario qué campo desea usar como clave
        printf("\tCampo a usar como clave:"
               "\n\t\tN: nombre"
               "\n\t\tA: alias"
               "\n\t\tC: correo");

        printf("\n\tCampo: ");

        char seleccion = '\0';
        scanf(" %c", &seleccion);
        campoBusqueda=seleccion;

    } else if (argc < 4)
    {
        campoBusqueda = ALIAS;
//        printf("Error: Faltan argumentos (CampoBusqueda)\n");
//        exit(1);
    } else
    {
        campoBusqueda = argv[3][0];

    }

    campoBusqueda = toupper(campoBusqueda);

    switch (campoBusqueda)
    {
        case NOMBRE:
            printf("Campo: NOMBRE, ");
            break;
        case ALIAS:
            printf("Campo: ALIAS, ");
            break;
        case CORREO:
            printf("Campo: CORREO, ");
            break;
        default:
            printf("Error: CampoBusqueda incorrecto\n");
            exit(1);
    }

    //--

    //Inicializo la tabla hash por encadenamiento
    InicializarTablaHash(t);

    /* printf("\n\t----INSERCIÓN ENCADENAMIENTO----"); */
    //llamo a la función de inserción en t a partir del archivo y el tipo de función hash a utilizar
    //////////////////////////////////////////////////////
    //Añadir como parámetro por referencia nColisionesI
    //////////////////////////////////////////////////////
    insercionArchivo(fp, &t, tipoFH, K, &nColisionesI, campoBusqueda);
    //////////////////////////////////////////////////////
    //Imprimir nColisionesI
    //////////////////////////////////////////////////////
//    printf("\n\n\t----ESTADÍSTICAS----");
    printf("nColisionesI:%d, ", nColisionesI);

    rewind(fp); //rebobino

    /* printf("\n\n\t----BÚSQUEDA ENCADENAMIENTO----"); */
    //Llamo a la función de búsqueda en t a partir del archivo y el tipo de función hash a utilizar
    //////////////////////////////////////////////////////////////////
    //Añadir como parámetro por referencia nPasosExtraB
    //////////////////////////////////////////////////////////////////
    busquedaArchivo(fp, t, tipoFH, K, &nPasosExtraB, campoBusqueda);
    //////////////////////////////////////////////////////////////////
    //Imprimir nPasosExtraB
    //////////////////////////////////////////////////////////////////
    printf("nPasosExtraB:%d\n", nPasosExtraB);

    DestruirTablaHash(t); //Destruyo la tabla

    fclose(fp); //Cierro el archivo    

    return (EXIT_SUCCESS);
}

//Función para insertar usuarios en tabla hash, usando la función hash "tipo"
//////////////////////////////////////////////////////////////////
//Añadir el parámetro por referencia nColisionesI
//////////////////////////////////////////////////////////////////
void insercionArchivo(FILE *fp, TablaHash *t, unsigned int tipoFH, unsigned int K, unsigned int *nColisionesI, enum CampoBusqueda campoBusqueda)
{
    TIPOELEMENTO paciente;
    if (fp)
    {
        fscanf(fp, " %[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
        while (!feof(fp))
        {
            //////////////////////////////////////////////////////////////////////////////////////////
            //Modificar la función InsertarHash para que devuelve: 1 si colisión, 0 en caso contrario
            //y acumular estos valores en nColisionesI
            /////////////////////////////////////////////////////////////////////////////////////////
            *nColisionesI += InsertarHash(t, paciente, tipoFH, K, campoBusqueda);
            fscanf(fp, " %[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
        }
    } else
    {
        printf("El archivo no ha podido abrirse\n");
    }
}

//Función para buscar un elemento leído del archivo en la tabla t, usando la función hash "tipo"
//////////////////////////////////////////////////////////////////
//Añadir el parámetro por referencia nPasosExtraB
//////////////////////////////////////////////////////////////////
void busquedaArchivo(FILE *fp, TablaHash t, unsigned int tipoFH, unsigned int K, unsigned int *nPasosExtraB, enum CampoBusqueda campoBusqueda)
{
    TIPOELEMENTO paciente;
    if (fp)
    {
        fscanf(fp, " %[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
        while (!feof(fp))
        {
            //////////////////////////////////////////////////////////////////////////////////////////
            //Añadir a BuscarHash() el parámetro por referencia nPasosExtraB
//            if(*nPasosExtraB==0)
//            {
//                printf("\n\n\n PASOS EXTRAB ES CERO\n\n\n");
//            }
            BuscarHash(t, &paciente, tipoFH, K, nPasosExtraB, campoBusqueda);

            fscanf(fp, " %[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
        }
    } else
    {
        printf("El archivo no ha podido abrirse\n");
    }
}

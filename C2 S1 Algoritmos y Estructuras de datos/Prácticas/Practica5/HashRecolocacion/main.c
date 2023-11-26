#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "tabla_hash_recolocacion.h"

/// MODIFICACIONES EN main.c
/// Inserción (función insercionArchivo): Variables nColisionesI, nPasosExtraI
/// Búsqueda (función busquedaArchivo): Variables nPasosExtraB

void insercionArchivo(FILE *fp, TablaHash t, unsigned int tipoFH, unsigned int K, unsigned int tipoR, unsigned int a, unsigned int *nColisionesI, unsigned int *nPasosExtraI, enum CampoBusqueda campoBusqueda);

void busquedaArchivo(FILE *fp, TablaHash t, unsigned int tipoFH, unsigned int K, unsigned int tipoR, unsigned int a, unsigned int *nPasosExtraB, enum CampoBusqueda campoBusqueda);

int main(int argc, char **argv)
{
    //variable que almacenan el tipo de función hash (1-2-3)
    unsigned int tipoFH;
    unsigned int K = 256; //factor de ponderación para hash por suma ponderada

    //variable que almacena el tipo de recolocación: lineal (1), o cuadrática (2)
    unsigned int tipoR;

    enum CampoBusqueda campoBusqueda;

    TablaHash t; //tabla hash

    //////////////////////////////////////////////////////////////////////////////////////
    //Definir las variables nColisionesI, nPasosExtraI y nPasosExtraB e inicializarlas a 0
    //////////////////////////////////////////////////////////////////////////////////////
    unsigned int nColisionesI = 0;
    unsigned int nPasosExtraI = 0;
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
        //Pregunto al usuario que estrategia de recolocación quiere utilizar
        //Si es lineal, también pido el valor de a
        printf("\n\n\tEstrategia de recolocación (1: Lineal, 2: Cuadrática): ");

        scanf("%u", &tipoR);
    } else if (argc < 4)
    {
        printf("Error: Faltan argumentos (tipoR)\n");
        exit(1);
    } else
    {
        tipoR = atoi(argv[3]);
    }

    //--

    unsigned int a = 0; //inicializo a

    if (tipoR == 1)
    {
        if (modoInteractivo)
        {
            printf("\t\tValor de a (1 para recolocación simple): ");
            scanf("%u", &a);
        } else if (argc < 5)
        {
            printf("Error: Faltan argumentos (a)\n");
            exit(1);
        } else
        {
            tipoR = 1;
            a = atoi(argv[4]);
        }
        /*    printf("\n\nRECOLOCACIÓN LINEAL con a=%u", a);*/
        printf("Recolocacion:Lineal, a:%u, ", a);
    } else
    {
        /* printf("\n\nRECOLOCACIÓN CUADRÁTICA"); */
        printf("Recolocacion:Cuadratica, a:-, ");

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

    } else if (argc < 6)
    {
        campoBusqueda = ALIAS;
//        printf("Error: Faltan argumentos (CampoBusqueda)\n");
//        exit(1);
    } else
    {
        campoBusqueda = argv[5][0];

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

    /* printf("\n\t----INSERCIÓN RECOLOCACIÓN----"); */
    //llamo a la función de inserción en t a partir del archivo
    //////////////////////////////////////////////////////////////////
    //Añadir los parámetros por referencia nColisionesI y nPasosExtraI
    //////////////////////////////////////////////////////////////////
    insercionArchivo(fp, t, tipoFH, K, tipoR, a, &nColisionesI, &nPasosExtraI, campoBusqueda);
    //////////////////////////////////////////////////////////////////
    //Imprimir nColisionesI y nPasosExtraI
    //////////////////////////////////////////////////////////////////
    printf("nColisionesI:%d, ", nColisionesI);
    printf("nPasosExtraI:%d, ", nPasosExtraI);

    rewind(fp); //rebobino

    /* printf("\n\n\t----BÚSQUEDA RECOLOCACIÓN----"); */
    //Llamo a la función de búsqueda en t a partir del archivo 
    //////////////////////////////////////////////////////////////////
    //Añadir el parámetros por referencia nPasosExtraB
    //////////////////////////////////////////////////////////////////
    busquedaArchivo(fp, t, tipoFH, K, tipoR, a, &nPasosExtraB, campoBusqueda);
    //////////////////////////////////////////////////////////////////
    //Imprimir nPasosExtraB
    //////////////////////////////////////////////////////////////////
    printf("nPasosExtraB:%d\n", nPasosExtraB);


    fclose(fp); //Cierro el archivo

    return (EXIT_SUCCESS);
}

//Función para insertar usuarios en tabla hash, usando la función hash "tipo"
//////////////////////////////////////////////////////////////////
//Añadir los parámetros por referencia nColisionesI y nPasosExtraI
//////////////////////////////////////////////////////////////////
void insercionArchivo(FILE *fp, TablaHash t, unsigned int tipoFH, unsigned int K, unsigned int tipoR, unsigned int a, unsigned int *nColisionesI, unsigned int *nPasosExtraI, enum CampoBusqueda campoBusqueda)
{
    TIPOELEMENTO paciente;
    if (fp)
    {
        fscanf(fp, "%[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
        while (!feof(fp))
        {
            //////////////////////////////////////////////////////////////////////////////////////////
            //Modificar la función InsertarHash para que devuelve: 1 si colisión, 0 en caso contrario
            //y acumular estos valores en nColisionesI
            //Añadir a InsertarHash parámetro nPasosExtraI por referencia
            /////////////////////////////////////////////////////////////////////////////////////////
            *nColisionesI += InsertarHash(t, paciente, tipoFH, K, tipoR, a, nPasosExtraI, campoBusqueda);
            fscanf(fp, "%[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
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
void busquedaArchivo(FILE *fp, TablaHash t, unsigned int tipoFH, unsigned int K, unsigned int tipoR, unsigned int a, unsigned int *nPasosExtraB, enum CampoBusqueda campoBusqueda)
{
    TIPOELEMENTO paciente;
    if (fp)
    {
        fscanf(fp, "%[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
        while (!feof(fp))
        {
            //El número de colisiones es el mismo que en inserción, hay pasos adicionales al buscar en la lista
            ///////////////////////////////////////////////////////////////////////////////
            //Modificar la función BuscarHash() para que reciba nPasosExtraB por referencia 
            ///////////////////////////////////////////////////////////////////////////////
            BuscarHash(t, &paciente, tipoFH, K, tipoR, a, nPasosExtraB, campoBusqueda);
            fscanf(fp, "%[^-] - %s - %s", paciente.nombre, paciente.alias, paciente.correo);
        }
    } else
    {
        printf("El archivo no ha podido abrirse\n");
    }
}

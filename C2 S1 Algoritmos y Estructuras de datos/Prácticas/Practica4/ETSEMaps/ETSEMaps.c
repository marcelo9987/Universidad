#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "grafo.h"



//FUNCIONES DEL PROGRAMA DE PRUEBA DE GRAFOS

//Opción a del menú, introducir un vértice en el grafo

void introducir_vertice(grafo *G)
{
    tipovertice v1;
    printf("Introduce vértice: ");
    scanf("%s", v1.nombre);
    if (existe_vertice(*G, v1))
    {
        printf("Ese vértice ya esta en el grafo\n");
    } else
    {
        insertar_vertice(G, v1);
    }
}
//Opción b del menú, eliminar un vértice del grafo

void eliminar_vertice(grafo *G)
{
    tipovertice v1;
    printf("Introduce vértice: ");
    scanf(" %s", v1.nombre);
    if (existe_vertice(*G, v1))
    {
        borrar_vertice(G, v1);
    } else
    {
        printf("Ese vértice no existe en el grafo\n");
    }
}

//Opción c del menú, crear una relación entre dos vértices

void nuevo_arco(grafo *G)
{
    tipovertice v1, v2;
    //Insertamos una nueva relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Nueva relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vértice origen: ");
    scanf("%s", v1.nombre);
    if (!existe_vertice(*G, v1))
    {
        printf("El vértice %d no existe en el grafo\n", v1);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vértice destino: ");
    scanf("%s", v2.nombre);
    if (!existe_vertice(*G, v2))
    {
        printf("El vértice %d no existe en el grafo\n", v2);
        return;
    }

    //todo: es aquí?
    char tipoDeConexion;
    printf("Introduce el tipo de conexion: ");
    scanf(" %c", &tipoDeConexion);
    tipoDeConexion = (char) toupper(tipoDeConexion);
    if (tipoDeConexion != 'A' && tipoDeConexion != 'C')
    {
        printf("El tipo de conexion no es valido\n");
        return;
    }

    //todo: es aquí?
    double valorArco;
    printf("Introduce el valor del arco: ");
    scanf("%lf", &valorArco);
    if (valorArco <= 0)
    {
        printf("El valor del arco no es valido\n");
        return;
    }

    //Creación del arco
    if (!distancia(*G, posicion(*G, v1), posicion(*G, v2), tipoDeConexion))
    {
        crear_arco(G, posicion(*G, v1), posicion(*G, v2), valorArco, tipoDeConexion);
    }
}

//todo: idem
//Opción d del menú, eliminar una relación entre dos vértices
void eliminar_arco(grafo *G)
{
    tipovertice v1, v2;
    //Eliminamos una relación pidiendo los datos al usuario controlando que existan los vértices
    printf("Eliminar relacion vertice1-->vertice2\n");
    //Vértice origen del arco
    printf("Introduce vértice origen: ");
    scanf("%s", v1.nombre);
    if (!existe_vertice(*G, v1))
    {
        printf("El vértice %s no existe en el grafo\n", v1.nombre);
        return;
    }
    //Vértice destino del arco
    printf("Introduce vértice destino: ");
    scanf("%s", v2.nombre);
    if (!existe_vertice(*G, v2))
    {
        printf("El vértice %s no existe en el grafo\n", v2.nombre);
        return;
    }

    char tipoDeConexion;
    printf("Introduce el tipo de conexión: ");
    scanf(" %c", &tipoDeConexion);

    tipoDeConexion = (char) toupper(tipoDeConexion);

    // Eliminación del arco


    switch (tipoDeConexion)
    {
        case 'A':
        case 'C':
            if (distancia(*G, posicion(*G, v1), posicion(*G, v2), tipoDeConexion))
            {
                borrar_arco(G, posicion(*G, v1), posicion(*G, v2), tipoDeConexion);
            }
            break;
        default:
            printf("El tipo de conexión no es valido\n");
            return;
    }

}

//Opción i del menú, imprimir el grafo
//Función que imprime el grafo utilizando num_vertices para saber cuántos vértices tiene
//y array_vertices para recuperar el vector de vértices y recorrerlo

void imprimir_grafo(grafo G)
{
    tipovertice *VECTOR; //Para almacenar el vector de vértices del grafo
    int N; //número de vértices del grafo

    //Para recorrerla, simplemente vamos a recorrer la matriz de adyacencia
    N = num_vertices(G);
    VECTOR = array_vertices(G);

    int i, j;
    printf("El grafo actual es:\n");
    for (i = 0; i < N; i++)
    {
        //Imprimo el vértice
        printf("vértice(%i): %s\n", i, VECTOR[i].nombre);
        //Chequeo sus arcos
        for (j = 0; j < N; j++)
        {
            if (distancia(G, i, j, 'C'))
            {
                printf("\t--> %s con valor %lf\n", VECTOR[j].nombre, calcularAdyacencia(G, i, j, 'C'));
            }
            if (distancia(G, i, j, 'A'))
            {
                printf("\t==> %s con valor %lf\n", VECTOR[j].nombre, calcularAdyacencia(G, i, j, 'A'));
            }
        }
    }
}


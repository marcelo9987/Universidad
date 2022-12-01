# include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define esperar()
//#define esperar() \
//{                 \
//    printf("\nContinuar: ");\
//    while(getchar()!='\n');\
//}

//#define procmap(numUso)
#define procmap(numUso) _procmap(numUso)


void _procmap(int numUso)
{
    char nombreArchivoDestino[20];
    sprintf(nombreArchivoDestino, "%s%i.mem", "maps", numUso);
    FILE* archivo = fopen(nombreArchivoDestino, "w+");
    
    char nombreArchivo[0xfff];
    sprintf(nombreArchivo, "%s%d%s", "/proc/", getpid(), "/maps");
    FILE* contenidosMapaMemoria;
    contenidosMapaMemoria = fopen(nombreArchivo, "r");
    int counter = 0;
    
    char buffer[300];
    while (1)
    {
        
        fgets(buffer, sizeof(buffer), contenidosMapaMemoria);
        if (feof(contenidosMapaMemoria))
        {
            break;
        }
        fprintf(archivo, "%s", buffer);
        
        ++counter;
    }
    printf("[ DEBUG ] He leído %i líneas.\n", counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}


int main()
{
    printf("[ DEBUG ] mi pid es: %i\n", getpid());
    char v[25];
    char* mi_str1 = NULL;
    char* mi_str2 = NULL;
    size_t tam = 400; //uso size_t en vez de u_int a razón de que la necesidad de espacio.
    
    for (int veces = 1; veces < 20; veces++) // Cada vuelta incrementa el espacio reservado
    {
        printf("\n\n[ INFO ] *** Inicio de la iteración: %i ***\n\n",veces);
        procmap(10 * veces + 1);
        esperar();
        
        printf("\n[ INFO ] Reservando %zu bytes de datos\n", tam);
        mi_str1 = (char*) malloc(tam * sizeof(char));
        if (mi_str1 == NULL)
        {
            printf("[ ERROR ] Fallo en el malloc\n");
            break;
        }else
        {
            printf("[ INFO ] Malloc realizado con éxito.\n");
        }
        
        printf("[ DEBUG ] mi_str1 está en %p\n", mi_str1);
        
        procmap(10 * veces + 2);
        esperar();
        
        printf("\n[ INFO ] Reservando %zu bytes de datos\n", tam);
        mi_str2 = (char*) malloc(tam * sizeof(char));
        if (mi_str2 == NULL)
        {
            printf("[ ERROR ] Fallo en el malloc\n");
            break;
        }else
        {
            printf("[ INFO ] Malloc realizado con éxito.\n");
        }
        printf("[ DEBUG ] mi_str2 está en %p\n", mi_str2);
        
        procmap(10 * veces + 3);
        esperar();
        
        free(mi_str1);
        free(mi_str2);
        
        printf("Después del free\n");
        
        procmap(10 * veces + 4);
        esperar();
        
        tam *= 10;
        printf("\n\n[ INFO ] *** Final de la iteración: %i ***\n\n",veces);
    }
    
    
    return 0;
}
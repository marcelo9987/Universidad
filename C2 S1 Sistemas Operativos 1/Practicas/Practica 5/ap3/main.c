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
    printf("He leído %i líneas.\n", counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}


int main()
{
    printf("mi pid es: %i\n", getpid());
    char v[25];
    char* mi_str1 = NULL;
    char* mi_str2 = NULL;
    size_t tam = 400;
    
    for (int veces = 1; veces < 20; veces++)
    {
        procmap(10 * veces + 1);
        esperar();
        
        printf("\nReservando %zu bytes de datos\n", tam);
        mi_str1 = (char*) malloc(tam * sizeof(char));
        if (mi_str1 == NULL)
        {
            printf("Fallo en el malloc\n");
            break;
        }
        
        printf("mi_str1 está en %p\n", mi_str1);
        
        procmap(10 * veces + 2);
        esperar();
        
        printf("\nReservando %zu bytes de datos\n", tam);
        mi_str2 = (char*) malloc(tam * sizeof(char));
        if (mi_str2 == NULL)
        {
            printf("Fallo en el malloc\n");
            break;
        }
        printf("mi_str2 está en %p\n", mi_str2);
        
        procmap(10 * veces + 3);
        esperar();
        
        free(mi_str1);
        free(mi_str2);
        
        printf("Después del free\n");
        
        procmap(10 * veces + 4);
        esperar();
        
        tam *= 10;
        
    }
    
    
    return 0;
}
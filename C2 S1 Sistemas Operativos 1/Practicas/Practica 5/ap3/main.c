# include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void procmap(int numUso)
{
    char nombreArchivoDestino[5];
    sprintf(nombreArchivoDestino, "%s%i", "mem", numUso);
    FILE *archivo = fopen(nombreArchivoDestino, "w+");

    char nombreArchivo[0xfff];
    sprintf(nombreArchivo, "%s%d%s", "/proc/", getpid(), "/maps");
    FILE* contenidosMapaMemoria;
    contenidosMapaMemoria = fopen(nombreArchivo, "r");
    int counter =0;

    char buffer[300];
    while(1)
    {

        fgets(buffer, sizeof(buffer), contenidosMapaMemoria);
        if(feof(contenidosMapaMemoria))
        {
            break;
        }
        fprintf(archivo,"%s",buffer);

        ++counter;
    }
    printf("He leído %i líneas",counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}

int main()
{
    printf("mi pid es: %i\n", getpid());
    char v[25];
    char *mi_str = NULL;
    printf("mi_str está en %p\n", mi_str);
    procmap(0);
    printf("continuar: ");
    scanf("%s", v);
    mi_str = (char *) malloc(400000000 * sizeof(char));
    if (mi_str == NULL)
    {
        printf("Fallo en el malloc\n");
        exit(-1);
    }
    printf("mi_str está en %p\n", mi_str);
    procmap(1);
    printf("continuar: ");
    scanf("%s", v);
    free(mi_str);
    
    printf(" Después del free\n");
    printf("mi_str está en %p\n", mi_str);
    procmap(2);
    printf("continuar: ");
    scanf("%s", v);
    mi_str = (char *) malloc(600000000 * sizeof(char));
    printf("mi_str está en %p\n", mi_str);
    procmap(3);
    printf("continuar: ");
    scanf("%s", v);
    free(mi_str);
    printf("mi_str está en %p\n", mi_str);
    procmap(4);
    printf("continuar: ");
    scanf("%s", v);
    
    return 0;
}
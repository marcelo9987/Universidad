#include <stdio.h>
#include <unistd.h>

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
    printf("HOLA");
    procmap(99);
    sleep(20);
}
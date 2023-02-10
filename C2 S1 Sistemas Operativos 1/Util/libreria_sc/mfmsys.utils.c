//
// Created by ssoo on 11/12/22.
//

#include "mfmsys.utils.h"
#include <stdio.h>
#include <unistd.h>

void procmap(int numUso) {
    char nombreArchivoDestino[20];
    sprintf(nombreArchivoDestino, "%s%i.mem", "maps", numUso);
    FILE *archivo = fopen(nombreArchivoDestino, "w+");
    
    char nombreArchivo[0xfff];
    sprintf(nombreArchivo, "%s%d%s", "/proc/", getpid(), "/maps");
    FILE *contenidosMapaMemoria;
    contenidosMapaMemoria = fopen(nombreArchivo, "r");
    int counter = 0;
    
    char buffer[300];
    while (1) {
        
        fgets(buffer, sizeof(buffer), contenidosMapaMemoria);
        if (feof(contenidosMapaMemoria)) {
            break;
        }
        fprintf(archivo, "%s", buffer);
        
        ++counter;
    }
    printf("[ INFO ] He leído %i líneas.\n", counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}

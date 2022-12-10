#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>

#define procmap(numUso) _procmap(numUso)

void _procmap(int numUso) {
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


int main()
{
    procmap(-1);
    int archivo = 0;
    archivo = open("./prueba.txt", O_RDWR);
    
    
    struct stat archivo_stat;
    if (fstat(archivo, &archivo_stat) != 0)
    {
        printf("[ ERROR ] fstat ha fallado.\n");
    }
    int i_tamanhoArchivo = archivo_stat.st_size;
    
    procmap(0);
    void* v_archivo_lectura_compartida = mmap(NULL,i_tamanhoArchivo,PROT_READ,MAP_SHARED,archivo,0);
    procmap(1);
    munmap(v_archivo_lectura_compartida,i_tamanhoArchivo);
    close(archivo);
    
    
    archivo = open("./prueba.txt", O_RDWR);
    if (fstat(archivo, &archivo_stat) != 0)
    {
        printf("[ ERROR ] fstat ha fallado.\n");
    }
    i_tamanhoArchivo = archivo_stat.st_size;
    procmap(2);
    void* v_archivo_escritura_compartida = mmap(NULL,i_tamanhoArchivo,PROT_WRITE,MAP_SHARED,archivo,0);
    procmap(3);
    munmap(v_archivo_escritura_compartida,i_tamanhoArchivo);
  
    
    
     /*
    int tamanhoArchivo = archivo_stat.st_size;
    int tamRest = tamanhoArchivo;
    int posAct = 0;
    char archivoCompleto[tamanhoArchivo];
    while(posAct!=tamanhoArchivo)
    {
        int t_lectura = tamanhoArchivo-posAct<archivo_stat.st_blocks?255:tamanhoArchivo-posAct;
        if(tamanhoArchivo-posAct==0)
        {
            break;
        }
        
        char buff[t_lectura];
        read(archivo,buff,t_lectura);
        for(int i =posAct;i<posAct+t_lectura;i++)
        {
            archivoCompleto[i] = buff[i];
        }
        posAct += t_lectura;
        
    }
    
    for(int i =0;i<tamanhoArchivo;i++)
    {
        printf("%c",archivoCompleto[i]);
    }
    
    
    close(archivo);*/
    close(archivo);
    return 0;
}

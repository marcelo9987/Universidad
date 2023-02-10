#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <unistd.h>

int main()
{
    int archivo = 0;
    archivo = open("./la_mala_reputacion.txt", O_RDONLY);
    
    
    struct stat archivo_stat;
    if (fstat(archivo, &archivo_stat) != 0)
    {
        printf("[ ERROR ] fstat ha fallado.\n");
    }
    printf("el archivo tiene: %li B\n", archivo_stat.st_size);
    
    char* inicio_archivo = mmap(NULL,archivo_stat.st_size,PROT_READ,MAP_PRIVATE,archivo,0);
    
    close(archivo);
    for(int i =0;i<archivo_stat.st_size;i++)
    {
        printf("%c",inicio_archivo[i]);
    }
    munmap(inicio_archivo,archivo_stat.st_size);
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
    return 0;
}

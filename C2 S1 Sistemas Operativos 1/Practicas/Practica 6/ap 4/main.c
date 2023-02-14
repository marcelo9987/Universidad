//#define esperar()
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>

#define esperar() \
{                 \
    printf("\nContinuar: ");\
    while(getchar()!='\n');\
}
int main()
{
    int archivo = open("./textfile.txt",O_RDWR);
    struct stat st_archivo;
    fstat(archivo,&st_archivo);
    char* texto = mmap(NULL,st_archivo.st_size,PROT_WRITE,MAP_SHARED,archivo,0);
    
    *(texto+2) = 'r';
    esperar();
    msync(texto,st_archivo.st_size,MAP_SHARED);
    
    
}

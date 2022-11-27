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

int i_arrayGlobal[6];
int i_varGlobal;

int main()
{
    char i;
    int i_varLocal;
    int i_arrayLocal[6];
    printf("pid: %d\n",getpid());
    printf("Main: %p",main);
    printf("varG: %p arrG: %p\n",&i_varGlobal,&i_arrayGlobal);
    printf("varL: %p arrL: %p",&i_varLocal,&i_arrayLocal);
    scanf("%s",&i);
    
    i_arrayLocal[2]=99;
    i_arrayGlobal[1]=8273678;
    i_varLocal=99;
    procmap(0);
    scanf("%s",&i);
    
    
    return 0;
}

# include <stdio.h>
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

void f1(int param)
{
    int num = param;
    printf("[%i] Parámetro en: %p Var en: %p\n",getpid(),&param,&num);

}
void f2(int param)
{
    int num = param;
    printf("[%i] Parámetro en: %p Var en: %p\n",getpid(),&param,&num);
}

int main()
{
    printf("f1 en: %p\n",f1);
    f1(8);
    printf("f2 en: %p\n",f2);
    f2(9);
    procmap(0);
    scanf("%i",NULL);
    
    return 0;
}
# include <stdio.h>
#include <unistd.h>

#define esperar()
//#define esperar() \
//{                 \
//    printf("\nContinuar: ");\
//    while(getchar()!='\n');\
//}

//#define procmap(numUso)
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
    printf("He leído %i líneas.\n", counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}

void f1(int param)
{
    int num = param;
    printf("[%i] Parámetro en: %p Var en: %p\n",getpid(),&param,&num);
    procmap(1);

}
void f2(int param)
{
    int num = param;
    printf("[%i] Parámetro en: %p Var en: %p\n",getpid(),&param,&num);
    procmap(2);
}

int main()
{
    procmap(0);
    printf("f1 en: %p\n",f1);
    f1(8);
    printf("f2 en: %p\n",f2);
    f2(9);
    procmap(3);
    esperar();
    
    return 0;
}
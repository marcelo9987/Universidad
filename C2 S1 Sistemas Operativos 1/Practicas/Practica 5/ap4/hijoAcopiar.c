#include <stdio.h>
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

int i_varGlobal = 321;
int i_arrayGlobal[] = {42, 1, 2, 3, 4, 5};


int main() {
//    char i[20];
    int i_varLocal = 123;
    int i_arrayLocal[] = {5, 4, 3, 2, 1, 42};
    
    printf("pid: %d\n", getpid());
    printf("main: %p\n", main);
    printf("varG: %p arrG: %p\n", &i_varGlobal, &i_arrayGlobal);
    printf("varL: %p arrL: %p\n", &i_varLocal, &i_arrayLocal);
    
    esperar();
//    printf("Continuar: ")
    //scanf("%s", i);
    
    procmap(100);
    
    i_arrayLocal[2] = 99;
    i_arrayGlobal[1] = 8273678;
    i_varLocal = 99;
    i_varGlobal = 42;
    
    procmap(101);
    
    esperar();
//    printf("\nContinuar: ")
//    scanf("%s", i);
    
    
    return 0;
}

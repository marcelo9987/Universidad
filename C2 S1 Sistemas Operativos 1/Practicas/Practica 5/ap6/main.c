#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//Nota: se recomienda el plugin Ideolog para leer el resultado de la ejecución


//#define esperar()
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
    printf("[ INFO ] He leído %i líneas.\n", counter);
    fclose(archivo);
    fclose(contenidosMapaMemoria);
}

int i_numero_global = 42;

void *fhilo1(void *param) {

    procmap(10);
    
    
    int *numero = (int *) param;
    int i_variable_hilo1;

    printf("[Hilo 1] variable global en: %p\n", &i_numero_global);
    printf("[Hilo 1] Param en: %p\n", param);
    printf("[Hilo 1] variable local en: %p\n", &i_variable_hilo1);

    i_variable_hilo1 = *numero * i_numero_global;

    procmap(11);
    pthread_exit(0);
}

void *fhilo2(void *param) {

    procmap(20);

    
    int *numero = (int *) param;
    int i_variable_hilo2;

    printf("[Hilo 2] variable global en: %p\n", &i_numero_global);
    printf("[Hilo 2] Param en: %p\n", param);
    printf("[Hilo 2] variable local en: %p\n", &i_variable_hilo2);

    i_variable_hilo2 = *numero * i_numero_global;

    procmap(21);
    pthread_exit(0);

}

int main() {

    procmap(1);

    int i_numero_local = 7;
    printf("[Padre] Mi pid es: %i", getpid());
    printf("[Padre] variable global en: %p\n", &i_numero_global);
    printf("[Padre] variable local en: %p\n", &i_numero_local);

    pthread_t hilo1, hilo2;

    if (pthread_create(&hilo1, NULL, fhilo1, (void *) &i_numero_local) != 0) {
        perror("[ ERROR ] pthread_create() error");
        exit(-1);
    }
    
    procmap(2);
    
    if (pthread_create(&hilo2, NULL, fhilo2, (void *) &i_numero_local) != 0) {
        perror("[ ERROR ] pthread_create() error");
        exit(-1);
    }
    sleep(5);

    procmap(3);
    
    if (pthread_join(hilo1, NULL) != 0) {
        perror("[ ERROR ] pthread_create() error");
        exit(3);
    }
    
    procmap(4);

    if (pthread_join(hilo2, NULL) != 0) {
        perror("[ ERROR ] pthread_create() error");
        exit(3);
    }


    procmap(5);


    return 0;
}


//todo: PENDIENTE
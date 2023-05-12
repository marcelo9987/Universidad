// Practica 3 - Productor y Cosumidor con hilos, mutexes y variables de condicion
// Sistemas Operativos II 2022-2023
// Autores: Marcelo Fort Muñoz y Laura Salgueiro Sanchez

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

//Constantes

#define P 5 // productores
#define C 3 // consumidores
#define N 10 // tamaño del buffer
#define ITEMS_BY_P 20 // items por cada productor
#define ARRAY_ELEMENTS_PER_THREAD 100 // elementos por cada hilo


//Colores
#define KNADA    "\x1B[0m"
#define KTURQ    "\x1b[1;36m"
#define KBOR    "\x1b[1;33;91m"


#define sleep(t) usleep(t*10000) //para que el sleep sea en centésimas de segundo

//Variables globales
int stock_actual = 0; //número de elementos en el buffer
int posicionA = 0, posicionB = 0;
int buffer[N]; //buffer que guarda los elementos
int A[ARRAY_ELEMENTS_PER_THREAD * P], B[ARRAY_ELEMENTS_PER_THREAD * C];
long int a = 0, b = 0;    //variables en las que se almacenará la suma de los vectores
int elementos_consumidos = 0;
int tiempossleep[6];

//Mutexes y variables de condición
pthread_mutex_t mutexbuffer, mutexsumaA, mutexsumaB;
pthread_cond_t condicionlleno, condicionvacio;

//Funciones
int produce_item();

void insert_item(int *buffer, int producto);

int extrae_producto(int *buffer);

void sumaprod(int nhilo, int imprimirsumatorioprod);

void sumacons(int nhilo, int imprimirsumatoriocons);

void funcionproductor(int nhilo);

void funcionconsumidor(int nhilo);


int main(int argc, char *argv[])
{

    if (argc != 1 + 6) {
        printf("Número de parámetros incorrecto\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 6; i++) {
        tiempossleep[i] = atoi(argv[i + 1]);
    }


    pthread_t productor[P], consumidor[C];    //hilos productor y consumidor

    //inicializamos los mutexes y variables de condicion
    pthread_mutex_init(&mutexbuffer, NULL);
    pthread_mutex_init(&mutexsumaA, NULL);
    pthread_mutex_init(&mutexsumaB, NULL);

    pthread_cond_init(&condicionlleno, NULL);
    pthread_cond_init(&condicionvacio, NULL);

    //inicializamos los vectores de sumar
    for (int i = 0; i < ARRAY_ELEMENTS_PER_THREAD * P; i++) {
        A[i] = i;
    }
    for (int i = 0; i < ARRAY_ELEMENTS_PER_THREAD * C; i++) {
        B[i] = i;
    }

    for (int i = 0; i < N; i++) {    //inicializamos el buffer
        buffer[i] = -1;
    }

    //creamos los hilos de productor y consumidor
    for (int i = 0; i < P; i++) {
        pthread_create(&productor[i], NULL, (void *) &funcionproductor, (void *) (intptr_t) i);
    }
    for (int i = 0; i < C; i++) {
        pthread_create(&consumidor[i], NULL, (void *) &funcionconsumidor, (void *) (intptr_t) i);
    }

    // esperamos a que los hilos terminen
    for (int i = 0; i < P; i++) {
        pthread_join(productor[i], NULL);
    }
    for (int i = 0; i < C; i++) {
        pthread_join(consumidor[i], NULL);
    }

    printf("[Hilo principal] Suma array A: %ld\n", a);
    printf("[Hilo principal] Suma array B: %ld\n", b);

    //destruimos los mutexes y variables de condicion
    pthread_mutex_destroy(&mutexbuffer);
    pthread_mutex_destroy(&mutexsumaA);
    pthread_mutex_destroy(&mutexsumaB);

    pthread_cond_destroy(&condicionlleno);
    pthread_cond_destroy(&condicionvacio);


}



//HILOS

void funcionproductor(int nhilo)
{

    int producto, elementos_producidos_por_este_hilo = 0, imprimirsumatorioprod=0;


    do {
        //SECCIÓN 1 DEL PROFE: INSERTAR EN EL BUFFER
        if (elementos_producidos_por_este_hilo < ITEMS_BY_P) {

            producto = produce_item(); //producimos un producto

            sleep(tiempossleep[0]);

            pthread_mutex_lock(&mutexbuffer);
            //REGION CRITICA

            while (stock_actual == N) {    //si el stock_actual es igual al tamaño del buffer, esperamos a que se vacíe
                pthread_cond_wait(&condicionlleno, &mutexbuffer);    //desbloquea el mutexbuffer y espera a que se le permita seguir por la condicionlleno
            }

            insert_item(buffer, producto); //metemos el elemento en la posición que me indica el stock_actual

            sleep(tiempossleep[1]);

            printf("%s[Productor  %d] Inserto %6d en %d.%s\n", KBOR, nhilo, producto, stock_actual, KNADA);

            stock_actual++; //aumentamos el stock_actual

            pthread_cond_signal(&condicionvacio);

            //FIN REGION CRITICA
            pthread_mutex_unlock(&mutexbuffer);

            elementos_producidos_por_este_hilo++;

        }




        //SECCIÓN 2: LA SUMA

	if (posicionA < ARRAY_ELEMENTS_PER_THREAD * P){
		if (pthread_mutex_trylock(&mutexsumaA) == 0) {    //si consigue obtener el buffer, suma
		    //REGION CRITICA
	
	        //printf("%s[Productor  %d] Sumo. posicionA: %5d.%s\n", KBOR, nhilo, posicionA, KNADA);
		           
			sumaprod(nhilo, imprimirsumatorioprod);

	        sleep(tiempossleep[2]);
			

	        //FIN REGION CRITICA
	        pthread_mutex_unlock(&mutexsumaA);
		}
	}else if(imprimirsumatorioprod==0){	//si ya se terminó el sumatorio y aún no imprimí el valor, lo imprimo
		printf("%s[Productor  %d] Fin tarea sumatorio. Valor final del sumatorio de a: %ld.%s\n", KBOR, nhilo, a, KNADA);
		imprimirsumatorioprod=1;
	}

    } while (elementos_producidos_por_este_hilo < ITEMS_BY_P || imprimirsumatorioprod==0);	//salimos del bucle si produjimos lo necesario y si terminamos la tarea del sumatorio (la terminamos cuando imprimimos el valor final del sumatorio)


    printf("%s[Productor  %d] Fin de este hilo.%s\n", KBOR, nhilo, KNADA);
    

    pthread_exit(NULL);
}


void funcionconsumidor(int nhilo)
{

    int producto,imprimirsumatoriocons=0;

    while (elementos_consumidos < ITEMS_BY_P * P || imprimirsumatoriocons==0) {
        //SECCIÓN 1: QUITAR DEL BUFFER
        if (elementos_consumidos < ITEMS_BY_P * P) {
            pthread_mutex_lock(&mutexbuffer);
            //REGION CRITICA

            while (stock_actual == 0 && elementos_consumidos < ITEMS_BY_P * P) {

                //printf("[Consumidor %d] Esperando... Elementos consumidos: %d. ", nhilo, elementos_consumidos);

                if (pthread_cond_wait(&condicionvacio, &mutexbuffer) != 0) {    //NOS BLOQUEAMOS
                    printf("Error en el wait\n");
                    exit(EXIT_FAILURE);
                }
            }

            if (elementos_consumidos < ITEMS_BY_P * P) {
                producto = extrae_producto(buffer);
                sleep(tiempossleep[3]);

                printf("%s[Consumidor %d] Quito   %6d de %d. %s\n", KTURQ, nhilo, producto, stock_actual - 1, KNADA);


                stock_actual--; //disminuimos en 1 el stock_actual (porque consumimos un elemento)

                elementos_consumidos++;    //aumento en 1 el número de elementos consumidos
                if (elementos_consumidos == ITEMS_BY_P * P) {    //si ya se metieron todos los elementos, el consumidor correspondiente despierta a todos los consumidores aunque solo seguirá uno (los esperan por un unlock en vez de por un signal)
                    printf("%s[Consumidor %d] Envío broadcast.%s\n", KTURQ, nhilo, KNADA);

                    pthread_cond_broadcast(&condicionvacio);

                }

                pthread_cond_signal(&condicionlleno);    //una vez que quitamos un elemento, los productores que estaban bloqueados pueden seguir

                //FIN REGION CRITICA
                pthread_mutex_unlock(&mutexbuffer);

                sleep(tiempossleep[4]);

            } else {
                //FIN REGION CRITICA
                pthread_mutex_unlock(&mutexbuffer);
            }

        }




		//printf("cons %d. posicionB: %d\n",nhilo,posicionB);

        //SECCIÓN 2: SUMA
        if (posicionB < ARRAY_ELEMENTS_PER_THREAD * C) {
        	if (pthread_mutex_trylock(&mutexsumaB) == 0) {    //si consigue obtener el buffer, suma
            	//REGION CRITICA
            
                //printf("%s[Consumidor %d] Sumo. posicionB: %5d.%s\n", KTURQ, nhilo, posicionB, KNADA);
				
				sumacons(nhilo,imprimirsumatoriocons);
				
                sleep(tiempossleep[5]);
                
                
            }

            //FIN REGION CRITICA
            pthread_mutex_unlock(&mutexsumaB);
        }else if(imprimirsumatoriocons==0){
        	printf("%s[Consumidor  %d] Fin tarea sumatorio. Valor final del sumatorio de b: %ld.%s\n", KTURQ, nhilo, b, KNADA);
        	imprimirsumatoriocons=1;
        }


    }

    printf("%s[Consumidor %d] Fin de este hilo.%s\n", KTURQ, nhilo, KNADA);

    pthread_exit(NULL);
}


//FUNCIONES
//funcion que genera un entero aleatorio entre 0 y 10000
int produce_item()
{
    return rand() % (10000 + 1); // generar un número aleatorio entre 0 y 10000
}

//funcion que coloca el elemento en el buffer
void insert_item(int *buffer, int producto)
{
    buffer[stock_actual] = producto;
}


//funcion que retira un elemento del buffer
int extrae_producto(int *buffer)
{
    int producto = buffer[stock_actual - 1]; //obtenemos el producto de la posicion indicada por el stock_actual
    buffer[stock_actual - 1] = -1; //ponemos un-1 en la posicion para indicar que esta eliminado
    return producto;
}


void sumaprod(int nhilo, int imprimirsumatorioprod)
{
    int veces = rand() % 5 + 1;    //sumamos de cada vez un valor entre 1 y 5

    for (int i = 0; i < veces && posicionA < ARRAY_ELEMENTS_PER_THREAD * P; i++) {
        a += A[posicionA];
        posicionA++;
    }
    
    if (posicionA == ARRAY_ELEMENTS_PER_THREAD * P){ //el primer productor que termina con la suma, imprime el resultado
		printf("%s[Productor  %d] Fin tarea sumatorio. Valor final del sumatorio de a: %ld.%s\n", KBOR, nhilo, a, KNADA);
		imprimirsumatorioprod=1;
	}
}


void sumacons(int nhilo, int imprimirsumatoriocons)
{
    int veces = rand() % 5 + 1;    //sumamos de cada vez un valor entre 1 y 5

    for (int i = 0; i < veces && posicionB < ARRAY_ELEMENTS_PER_THREAD * C; i++) {
        b += B[posicionB];
        posicionB++;
    }
    if (posicionB == ARRAY_ELEMENTS_PER_THREAD * C){ //el primer consumidor que termina con la suma, imprime el resultado
		printf("%s[Consumidor  %d] Fin tarea sumatorio. Valor final del sumatorio de b: %ld.%s\n", KTURQ, nhilo, b, KNADA);
		//printf("posicionB: %d\n",posicionB);
		imprimirsumatoriocons=1;
	}
}
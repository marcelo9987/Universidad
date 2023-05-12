// Practica 3 - Productor y Cosumidor con hilos, mutexes y variables de condicion
// Sistemas Operativos II 2022-2023
// Autores: Marcelo Fort Muñoz y Laura Salgueiro Sanchez

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

//Constantes
#define P 4 // productores
#define C 3 // consumidores
#define N 10 // tamaño del buffer
#define ITEMS_BY_P 20 // items por cada productor
#define ARRAY_ELEMENTS_PER_THREAD 100 // elementos por cada hilo


//Colores
#define KNADA    "\x1B[0m"
#define KTURQ    "\x1b[1;36m"
#define KBOR    "\x1b[1;33;91m"


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

int extract_item(int *buffer);

void sumaprod(int nhilo);

void sumacons(int nhilo);

void funcionproductor(int nhilo);

void funcionconsumidor(int nhilo);


int main(int argc, char *argv[])
{
    
    if (argc != 1 + 6)
    {
        printf("Número de parámetros incorrecto\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 6; i++)
    {
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
    for (int i = 0; i < ARRAY_ELEMENTS_PER_THREAD * P; i++)
    {
        A[i] = i;
    }
    for (int i = 0; i < ARRAY_ELEMENTS_PER_THREAD * C; i++)
    {
        B[i] = i;
    }
    
    for (int i = 0; i < N; i++)
    {    //inicializamos el buffer
        buffer[i] = -1;
    }
    
    //creamos los hilos de productor y consumidor
    for (int i = 0; i < P; i++)
    {
        pthread_create(&productor[i], NULL, (void *) &funcionproductor, (void *) (intptr_t) i);
    }
    for (int i = 0; i < C; i++)
    {
        pthread_create(&consumidor[i], NULL, (void *) &funcionconsumidor, (void *) (intptr_t) i);
    }
    
    // esperamos a que los hilos terminen
    for (int i = 0; i < P; i++)
    {
        pthread_join(productor[i], NULL);
    }
    for (int i = 0; i < C; i++)
    {
        pthread_join(consumidor[i], NULL);
    }
    
    printf("[Hilo principal] Suma array A: %ld\n", a);
    printf("[Hilo principal] Suma array B: %ld\n", b);
    
    //destruimos los mutexes y variables de condición
    pthread_mutex_destroy(&mutexbuffer);
    pthread_mutex_destroy(&mutexsumaA);
    pthread_mutex_destroy(&mutexsumaB);
    
    pthread_cond_destroy(&condicionlleno);
    pthread_cond_destroy(&condicionvacio);
    
    
    return 0;
}



//HILOS

void funcionproductor(int nhilo)
{
    
    int producto, elementos_producidos_por_este_hilo = 0;
    bool pendiente_imprimir_sumatorio = true;
    
    
    do
    {
        //SECCIÓN 1: INSERTAR EN EL BUFFER
        if (elementos_producidos_por_este_hilo < ITEMS_BY_P)
        {
            producto = produce_item(); //producimos un producto
            
            sleep(tiempossleep[0]);
            
            pthread_mutex_lock(&mutexbuffer);
            //REGION CRITICA
            
            while (stock_actual == N)
            {    //si el stock_actual es igual al tamaño del buffer, esperamos a que se vacíe
                pthread_cond_wait(&condicionlleno, &mutexbuffer);    //desbloquea el mutexbuffer y espera a que se le permita seguir por la condicionlleno
            }
            
            printf("%s[Productor  %d]%s Inserto %6d en %d.\n", KBOR, nhilo, KNADA, producto, stock_actual);
            
            insert_item(buffer, producto); //metemos el elemento en la posición que me indica el stock_actual
            
            sleep(tiempossleep[1]);
            
            pthread_cond_signal(&condicionvacio);   //indicamos que el buffer tiene por lo menos un elemento (para despertar a los posibles consumidores dormidos porque el buffer estaba vacio)
            
            //FIN REGION CRITICA
            pthread_mutex_unlock(&mutexbuffer);
            
            elementos_producidos_por_este_hilo++;
        }
        
        
        
        
        //SECCIÓN 2: LA SUMA
        
        if (pendiente_imprimir_sumatorio)
        {
            if (pthread_mutex_trylock(&mutexsumaA) == 0)
            {    //si consigue obtener el buffer, suma
                //REGION CRITICA
                
                if (posicionA < ARRAY_ELEMENTS_PER_THREAD * P)
                {   //antes de sumar, comprobamos que no se haya ya sumado todo el array
                    printf("%s[Productor  %d]%s Sumo. posicionA: %5d.\n", KBOR, nhilo, KNADA, posicionA);
                    
                    sumaprod(nhilo);
                    
                    sleep(tiempossleep[2]);
                    
                }
                
                //FIN REGION CRITICA
                pthread_mutex_unlock(&mutexsumaA);
            }
            
            // OJO: El siguiente if no se debe de cambiar por un else. Hay que imprimir la frase que nos permite terminar la tarea de sumar
            if (posicionA == ARRAY_ELEMENTS_PER_THREAD * P)
            {    //si ya se terminó el sumatorio y aún no imprimí el valor, lo imprimo
                printf("%s[Productor  %d]%s Fin tarea sumatorio. Valor final del sumatorio de a: %ld.\n", KBOR, nhilo, KNADA, a);
                pendiente_imprimir_sumatorio = false;   //finalizamos la tarea de sumar cuando hayamos imprimido el valor final del sumatorio
            }
            
        }
    } while (elementos_producidos_por_este_hilo < ITEMS_BY_P || pendiente_imprimir_sumatorio);    //salimos del bucle si produjimos lo necesario y si terminamos la tarea del sumatorio
    
    
    printf("%s[Productor  %d]%s Fin de este hilo.\n", KBOR, nhilo, KNADA);
    
    
    pthread_exit(NULL);
}


void funcionconsumidor(int nhilo)
{
    
    int producto;
    bool pendiente_imprimir_sumatorio = true;
    
    while (elementos_consumidos < ITEMS_BY_P * P || pendiente_imprimir_sumatorio)
    {
        //SECCIÓN 1: QUITAR DEL BUFFER
        if (elementos_consumidos < ITEMS_BY_P * P)
        {
            pthread_mutex_lock(&mutexbuffer);
            //REGION CRITICA
            
            while (stock_actual == 0 && elementos_consumidos < ITEMS_BY_P * P)
            {
                
                //printf("[Consumidor %d] Esperando... Elementos consumidos: %d.\n", nhilo, elementos_consumidos);
                
                if (pthread_cond_wait(&condicionvacio, &mutexbuffer) != 0)
                {    //NOS BLOQUEAMOS si no hay nada que extraer
                    printf("Error en el wait\n");
                    exit(EXIT_FAILURE);
                }
            }
            
            if (elementos_consumidos < ITEMS_BY_P * P)
            {   //si no se consumieron todos los elementos, consumimos
                producto = extract_item(buffer);
                sleep(tiempossleep[3]);
                
                printf("%s[Consumidor %d]%s Quito   %6d de %d.\n", KTURQ, nhilo, KNADA, producto, stock_actual);
                
                
                elementos_consumidos++;    //aumento en 1 el número de elementos consumidos
                
                sleep(tiempossleep[4]);
                
                if (elementos_consumidos == ITEMS_BY_P * P)
                {    //si ya se metieron todos los elementos, el consumidor correspondiente despierta a todos los consumidores aunque solo seguirá uno (los esperan por un unlock en vez de por un signal)
                    printf("%s[Consumidor %d]%s Envío broadcast.\n", KTURQ, nhilo, KNADA);
                    
                    pthread_cond_broadcast(&condicionvacio);    //Ahora el buffer siempre estará a 0. Nadie le mandará señal a los consumidores dormidos para despertarse. Los despertamos aqui a todos 
                    
                }
                
                pthread_cond_signal(&condicionlleno);    //una vez que quitamos un elemento, los productores que estaban bloqueados pueden seguir
                
                //FIN REGION CRITICA
                pthread_mutex_unlock(&mutexbuffer);
                
            } else
            {   //si se consumieron todos los elementos, desbloqueamos el mutex y salimos
                //FIN REGION CRITICA
                pthread_mutex_unlock(&mutexbuffer); //dejamos el mutex libre para que los consumidores que despertamos con el broadcast puedan acabar
            }
            
        }
        
        
        
        
        //SECCIÓN 2: SUMA
        if (pendiente_imprimir_sumatorio)
        {
            if (pthread_mutex_trylock(&mutexsumaB) == 0)
            {    //si consigue obtener el buffer, suma
                //REGION CRITICA
                
                if (posicionB < ARRAY_ELEMENTS_PER_THREAD * C)
                {   //antes de sumar, comprobamos que no se haya ya sumado todo el array
                    
                    printf("%s[Consumidor %d]%s Sumo. posicionB: %5d.\n", KTURQ, nhilo, KNADA, posicionB);
                    
                    sumacons(nhilo);
                    
                    sleep(tiempossleep[5]);
                }
                
                //FIN REGION CRITICA
                pthread_mutex_unlock(&mutexsumaB);
                
            }
            
            // OJO: El siguiente if no se debe de cambiar por un else. Hay que imprimir la frase que nos permite terminar la tarea de sumar
            if (posicionB == ARRAY_ELEMENTS_PER_THREAD * C)
            {
                printf("%s[Consumidor %d]%s Fin tarea sumatorio. Valor final del sumatorio de b: %ld.\n", KTURQ, nhilo, KNADA, b);
                pendiente_imprimir_sumatorio = false;   //una vez que imprimimos el valor final del sumatorio, terminamos con la suma
            }
            
        }
    }
    
    printf("%s[Consumidor %d]%s Fin de este hilo.\n", KTURQ, nhilo, KNADA);
    
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
    
    stock_actual++; //aumentamos el stock_actual
}


//funcion que retira un elemento del buffer
int extract_item(int *buffer)
{
    stock_actual--; //disminuimos en 1 el stock_actual (porque consumimos un elemento)
    
    int producto = buffer[stock_actual]; //obtenemos el producto de la posición indicada por el stock_actual
    buffer[stock_actual] = -1; //ponemos un-1 en la posición para indicar que está eliminado
    
    return producto;
}


void sumaprod(int nhilo)
{
    int veces = rand() % 5 + 1;    //sumamos de cada vez un valor entre 1 y 5
    
    for (int i = 0; i < veces && posicionA < ARRAY_ELEMENTS_PER_THREAD * P; i++)
    {
        a += A[posicionA];
        posicionA++;
    }
}


void sumacons(int nhilo)
{
    int veces = rand() % 5 + 1;    //sumamos de cada vez un valor entre 1 y 5
    
    for (int i = 0; i < veces && posicionB < ARRAY_ELEMENTS_PER_THREAD * C; i++)
    {
        b += B[posicionB];
        posicionB++;
    }
}

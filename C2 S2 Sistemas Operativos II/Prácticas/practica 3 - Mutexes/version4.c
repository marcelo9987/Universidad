// Practica 3 - Productor y Cosumidor con hilos y mutexes
// Sistemas Operativos II 2022-2023
// Autores: Marcelo Fort Muñoz y Laura Salgueiro Sanchez

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>
//#include <errno.h>

//Constantes
#define P 3 // productores
#define C 3 // consumidores
#define N 10 // tamaño del buffer
#define ITEMS_BY_P 20 // items por cada productor
#define ARRAY_ELEMENTS_PER_THREAD 100 // elementos por cada hilo

#define sleep(t) usleep(t*100000) //para que el sleep sea en décimas de segundo

//Colores
#define KNADA    "\x1B[0m"
#define KTURQ    "\x1b[1;36m"
#define KBOR    "\x1b[1;33;91m"


//Variables globales
int contador = 0; //número de elementos en el buffer
int posicionA = 0, posicionB = 0;
int buffer[N]; //buffer que guarda los elementos
int A[ARRAY_ELEMENTS_PER_THREAD * P], B[ARRAY_ELEMENTS_PER_THREAD * C];
long int a = 0, b = 0;    //variables en las que se almacenará la suma de los vectores
int elementosquitados = 0, yaterminado = 0;
int tiempossleep[6];

//Mutexes y variables de condición
pthread_mutex_t mutexbuffer, mutexsumaA, mutexsumaB, mutexelementostotales;
pthread_cond_t condicionlleno, condicionvacio, condicionsumaA, condicionsumaB;

//Funciones
int produce_item();

void insert_item(int *buffer, int producto);

int consume_item(int *buffer);

void mostrar_hora();

void mostrar_buffer(int *buffer);

void sumaprod(int nhilo);

void sumacons(int nhilo);

void funcionproductor(int nhilo);

void funcionconsumidor(int nhilo);


int main(int argc, char *argv[])
{
    
    pthread_t productor[P], consumidor[C];    //hilos productor y consumidor
    
    if (argc != 7)
    {
        printf("Número de parámetros incorrecto\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < 6; i++)
    {
        tiempossleep[i] = atoi(argv[i + 1]);
    }
    
    //destruir variables de condición
    pthread_mutex_destroy(&mutexbuffer);
    pthread_mutex_destroy(&mutexelementostotales);
    pthread_mutex_destroy(&mutexsumaA);
    pthread_mutex_destroy(&mutexsumaB);
    
    pthread_cond_destroy(&condicionlleno);
    pthread_cond_destroy(&condicionvacio);
    pthread_cond_destroy(&condicionsumaA);
    pthread_cond_destroy(&condicionsumaB);
    
    pthread_mutex_init(&mutexbuffer, NULL);    //inicializamos el mutex
    pthread_mutex_init(&mutexelementostotales, NULL);    //inicializamos el mutex
    pthread_mutex_init(&mutexsumaA, NULL);    //inicializamos el mutex
    pthread_mutex_init(&mutexsumaB, NULL);    //inicializamos el mutex
    
    pthread_cond_init(&condicionlleno, NULL);    //inicializamos la condicion
    pthread_cond_init(&condicionvacio, NULL);    //inicializamos la condicion
    pthread_cond_init(&condicionsumaA, NULL);    //inicializamos la condicion
    pthread_cond_init(&condicionsumaB, NULL);    //inicializamos la condicion
    
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
    //mostrar_buffer(buffer);
    
    
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
    
    pthread_mutex_destroy(&mutexbuffer);
    pthread_mutex_destroy(&mutexelementostotales);
    pthread_mutex_destroy(&mutexsumaA);
    pthread_mutex_destroy(&mutexsumaB);
    
    pthread_cond_destroy(&condicionlleno);
    pthread_cond_destroy(&condicionvacio);
    pthread_cond_destroy(&condicionsumaA);
    pthread_cond_destroy(&condicionsumaB);
    
    return 0;
}



//HILOS

void funcionproductor(int nhilo)
{
    
    int producto, elementos_producidos_por_este_hilo = 0;
//    long int ultimasuma; //variable para guardar los productos
    
    
    do
    {
        //SECCIÓN 1 DEL PROFE: INSERTAR EN EL BUFFER
        if (elementos_producidos_por_este_hilo < ITEMS_BY_P)
        {
            
            producto = produce_item(); //producimos un producto
            
            sleep(tiempossleep[0]);
            
            pthread_mutex_lock(&mutexbuffer);
            //REGION CRITICA
            
            while (contador == N)
            {    //si el contador es igual al tamaño del buffer, esperamos a que se vacíe
                pthread_cond_wait(&condicionlleno, &mutexbuffer);    //desbloquea el mutexbuffer y espera a que se le permita seguir por la condicionlleno
            }
            
            insert_item(buffer, producto); //metemos el elemento en la posición que me indica el contador
            
            sleep(tiempossleep[1]);
            
            printf("%s[Productor  %d] Inserto %6d en %d. %s", KBOR, nhilo, producto, contador, KNADA);
            mostrar_hora();
            //mostrar_buffer(buffer);
            contador++; //aumentamos el contador
            
            pthread_cond_signal(&condicionvacio);
            
            //FIN REGION CRITICA
            pthread_mutex_unlock(&mutexbuffer);
            
            elementos_producidos_por_este_hilo++;
            
        }
        
        
        
        
        //SECCIÓN 2: LA SUMA
        
        
        if (pthread_mutex_trylock(&mutexsumaA) == 0)
        {    //si consigue obtener el buffer, suma
            //REGION CRITICA
            
            sumaprod(nhilo);
            
            sleep(tiempossleep[2]);
            
            //FIN REGION CRITICA
            pthread_mutex_unlock(&mutexsumaA);
        }
        
        
    } while (elementos_producidos_por_este_hilo < ITEMS_BY_P || posicionA < ARRAY_ELEMENTS_PER_THREAD * P);
    
    
    printf("%s[Productor  %d] Fin de este hilo. Valor final del sumatorio de a: %ld. %s", KBOR, nhilo, a, KNADA);
    mostrar_hora();
    
    pthread_exit(NULL);
}


void funcionconsumidor(int nhilo)
{
    
    int producto, flag = 0;
//    long int ultimasuma; //variable para guardar los productos
    
    
    
    while (elementosquitados < ITEMS_BY_P * P || posicionB < ARRAY_ELEMENTS_PER_THREAD * C)
    {
        //SECCIÓN 1: QUITAR DEL BUFFER
        if (elementosquitados < ITEMS_BY_P * P)
        {
            pthread_mutex_lock(&mutexbuffer);
            //REGION CRITICA
            
            while (contador == 0)
            {
                
                printf("[Consumidor %d] Esperando... Elementos quitados: %d. ", nhilo, elementosquitados);
                mostrar_hora();
                if (yaterminado == 0)
                {    //si los productores aún no metieron todos los elementos en el buffer, hace el cond_wait esperando a que lo despierten
                    //if(elementosquitados!=ITEMS_BY_P*P){
                    //printf("Salí por el wait\n");
                    if (pthread_cond_wait(&condicionvacio, &mutexbuffer) != 0)
                    {    //NOS BLOQUEAMOS
                        printf("Error en el wait\n");
                        exit(EXIT_FAILURE);
                    }
                }
                
                if (elementosquitados == ITEMS_BY_P * P)
                {    //si todos los productores terminaron de meter los elementos en el buffer, hacemos un unlock para que el siguiente consumidor pueda coger el mutex y consumir, terminando su ejecución
                    flag = 1;
                    printf("[Consumidor %d] Hago unlock cuando elementosquitados==ITEMS_BY_P*P. posicionB= %d. ", nhilo, posicionB);
                    mostrar_hora();
                    
                    pthread_mutex_unlock(&mutexbuffer);    //tenemos que desbloquear el mutex porque no lo desbloqueamos luego
                    break;
                }
            }
            
            if (flag != 1)
            {
                producto = consume_item(buffer);
                sleep(tiempossleep[3]);
                
                printf("%s[Consumidor %d] Quito   %6d de %d. %s", KTURQ, nhilo, producto, contador - 1, KNADA);
                mostrar_hora();
                
                sleep(tiempossleep[4]);
                
                contador--; //disminuimos en 1 el contador (porque consumimos un elemento)
                elementosquitados++;    //aumento en 1 el número de elementos quitados
                if (elementosquitados == ITEMS_BY_P * P)
                {    //si ya se metieron todos los elementos, el consumidor correspondiente despierta a todos los consumidores aunque solo seguirá uno (los esperan por un unlock en vez de por un signal)
                    printf("[Consumidor %d] Envío broadcast. ", nhilo);
                    mostrar_hora();
                    
                    pthread_cond_broadcast(&condicionvacio);
                    yaterminado = 1;
                }
                pthread_cond_signal(&condicionlleno);    //una vez que quitamos un elemento, los productores que estaban bloqueados pueden seguir
                
                //FIN REGION CRITICA
                pthread_mutex_unlock(&mutexbuffer);
            }
            
        }
        
        
        
        
        
        //SECCIÓN 2: SUMA
        if (pthread_mutex_trylock(&mutexsumaB) == 0)
        {    //si consigue obtener el buffer, suma
            //REGION CRITICA
            
            sumacons(nhilo);
            
            sleep(tiempossleep[5]);
            
            //FIN REGION CRITICA
            pthread_mutex_unlock(&mutexsumaB);
        }
        
        
    }
    
    printf("%s[Consumidor %d] Fin de este hilo. Valor final del sumatorio de b: %ld. %s", KBOR, nhilo, b, KNADA);
    mostrar_hora();
    
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
    buffer[contador] = producto;
}

void mostrar_buffer(int *buffer)
{
    printf("\n------- Buffer(contador = %d) ", contador);
    mostrar_hora();
    for (int i = 0; i < 10; i++)
    {
        printf("pos %d: %d\n", i, buffer[i]);
    }
    mostrar_hora();
    printf("\n");
}

//funcion que retira un elemento del buffer y lo suma con el anterior si existe
int consume_item(int *buffer)
{
    int producto = buffer[contador - 1]; //obtenemos el producto de la posicion indicada por el contador
    buffer[contador - 1] = -1; //ponemos un-1 en la posicion para indicar que esta eliminado
    return producto;
}

//funcion para mostrar la hora indicando los minutos, los segundos, y los microsegundos
void mostrar_hora()
{
    struct timeval tv;
    struct tm *tm_info;
    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);
    printf("(min:seg - %d:%d, microseg - %ld)\n", tm_info->tm_min, tm_info->tm_sec, tv.tv_usec);
}


void sumaprod(int nhilo)
{
    int veces = rand() % 5 + 1;    //sumamos de cada vez un valor entre 1 y 5
    
    for (int i = 0; i < veces && posicionA < ARRAY_ELEMENTS_PER_THREAD * P; i++)
    {
        a += A[posicionA];
        //printf("a: %ld\n", a);
        posicionA++;
        if (posicionA == ARRAY_ELEMENTS_PER_THREAD)
        {
            printf("[Productor  %d] Fin sumas de a: %ld. ", nhilo, a);
            mostrar_hora();
        }
    }
}


void sumacons(int nhilo)
{
    int veces = rand() % 5 + 1;    //sumamos de cada vez un valor entre 1 y 5
    
    for (int i = 0; i < veces && posicionB < ARRAY_ELEMENTS_PER_THREAD * C; i++)
    {
        b += B[posicionB];
        //printf("b: %ld\n", b);
        posicionB++;
        if (posicionB == ARRAY_ELEMENTS_PER_THREAD)
        {
            printf("[Consumidor %d] Fin sumas de b: %ld. ", nhilo, b);
            mostrar_hora();
        }
    }
}

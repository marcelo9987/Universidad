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
#define P 1 // productores
#define C 1 // consumidores
#define N 10 // tamano del buffer
#define ITEMS_BY_P 20 // items por cada productor

//Colores
#define KNADA	"\x1B[0m"
#define KTURQ	"\x1b[1;36m"
#define KBOR	"\x1b[1;33;91m"

//Variables globales
int contador = 0; //numero de elementos en el buffer
int posicionA=0, posicionB=0;   //indices de los vectores suma
//todo: definir tamBuffer
int buffer[tamBuffer]; //buffer que guarda los elementos
int A[100*P],B[100*C];
long int a=0, b=0;   //variables que almacenan el valor de la suma de los vectores A y B

//Mutexes y variables de condicion
pthread_mutex_t mutexbuffer, mutexsumaA, mutexsumaB;
pthread_cond_t condicionlleno, condicionvacio, condicionsumaA, condicionsumaB;

//Funciones
int produce_item();
void insert_item(int *buffer, int producto);
int consume_item(int *buffer);
void sumaprod();
void sumacons();
void funcionproductor(int nhilo);
void funcionconsumidor(int nhilo);


int main() {

	pthread_t consumidor[P],consumidor[C];    //hilos productor y consumidor

	//todo:  debemos destruir los mutexes antes de ser creados?

	pthread_mutex_destroy(&mutexbuffer);    //eliminamos los mutex del kernel
	pthread_mutex_destroy(&mutexsumaA);
	pthread_mutex_destroy(&mutexsumaB);
	pthread_mutex_init(&mutexbuffer,NULL);	//inicializamos el mutex
	pthread_mutex_init(&mutexsumaA,NULL);	//inicializamos el mutex
	pthread_mutex_init(&mutexsumaB,NULL);	//inicializamos el mutex
	pthread_cond_init(&condicionlleno,NULL);	//inicializamos la condicion
	pthread_cond_init(&condicionvacio,NULL);	//inicializamos la condicion
	pthread_cond_init(&condicionsumaA,NULL);	//inicializamos la condicion
	pthread_cond_init(&condicionsumaB,NULL);	//inicializamos la condicion
	
	//creamos los hilos productores y consumidores
	for(int=0;i<P;i++){
		pthread_create(&productor[i], NULL, (void*)&funcionproductor, (void*)i);
	}
	for(int=0;i<C;i++){
		pthread_create(&consumidor[i], NULL, (void*)&funcionconsumidor, (void*)i);
	}
	
	// esperamos a que los hilos terminen
	for(int i=0;i<P;i++){
		pthread_join(productor[i], NULL);
	}
	for(int i=0;i<C;i++){
		pthread_join(consumidor[i], NULL);
	}
		
	pthread_mutex_destroy(&mutexbuffer);
	pthread_mutex_destroy(&mutexsumaA);
	pthread_mutex_destroy(&mutexsumaB);
	pthread_cond_destroy(&condicionlleno);	
	pthread_cond_destroy(&condicionvacio);
	pthread_cond_destroy(&condicionsumaA);
	pthread_cond_destroy(&condicionsumaB);
}



/////////////////////////////////////
////////////////HILOS////////////////
/////////////////////////////////////

//AUN NO ESTÁN BIEN HECHAS LAS FUNCIONES!!!
//HAY QUE QUITAR Y CAMBIAR COSAS
void funcionproductor(int nhilo) {

	int producto; //variable para guardar los productos
	
	for(int i=0;i<ITEMS_BY_P;i++){
	
		producto = produce_item(); //producimos un producto, en este caso sera un numero aleatorio entre 0 y 10000
		
		if(pthread_mutex_trylock(&mutexbuffer)==0){	//intenta entrar, si no, puede hacer otra cosa
		
			insert_item(buffer, producto); //metemos el elemento en la posición que me indica el contador
			printf("%sEl productor %d inserta %d en %d%s ", KBOR, nhilo, producto, contador, KNRM);
			contador++; //aumentamos el contador
			pthread_mutex_unlock(&mutexbuffer);
		}else{	//si no entro en la región crítica, colaboramos en la suma
			pthread_mutex_lock(&mutexsumaA);
					//todo: meter la suma	
			pthread_mutex_unlock(&mutexsumaA);
		}
		
		sleep(rand()%5);
	}
	
	printf("%sEl productor %d finalizó.%s\n",KBOR,nhilo,KNRM);
}


void funcionconsumidor(int nhilo) {

	int producto; //variable para guardar los productos
		
	for(int i=1;i<=ITEMS_BY_P;i++){
		
		pthread_mutex_lock(&mutexbuffer);
		producto = consume_item(buffer);
		printf("%sEl consumidor %d quita %d de %d%s ", KTURQ, nhilo, producto, contador-1, KNRM);
		contador--; //disminuimos en 1 el contador (porque consumimos un elemento)
		pthread_mutex_unlock(&mutexbuffer);
		
		sleep(rand()%5);
	}
	
	printf("%sEl consumidor %d finalizó.%s\n",KTURQ,nhilo,KNRM);
}



/////////////////////////////////////
//////////////FUNCIONES//////////////
/////////////////////////////////////

//funcion que genera un entero aleatorio entre 0 y 10000
int produce_item(){
	return rand() % (10000 + 1); // generar un número aleatorio entre 0 y 10000
}

//funcion que coloca el elemento en el buffer
void insert_item(int *buffer, int producto){
	buffer[contador] = producto;
}

//funcion que retira un elemento del buffer y lo suma con el anterior si existe
int consume_item(int *buffer){
	int producto = buffer[contador-1]; //obtenemos el producto de la posicion indicada por el contador
	buffer[contador-1] = -1; //ponemos un-1 en la posicion para indicar que esta eliminado
	return producto;
}


void sumaprod(){
	int veces;
	veces=rand()%5 + 1;	//sumamos de cada vez un valor entre 1 y 5
	for(int i=0;i<veces;i++){
		pthread_mutex_lock(&mutexsumaA);
		a= a + A[posicionA];	
		//printf("a: %ld\n",a);
		posicionA++;
		pthread_mutex_unlock(&mutexsumaA);
	}
}

void sumacons(){
	int veces;
	veces=rand()%5 + 1;	//sumamos de cada vez un valor entre 1 y 5
	for(int i=0;i<veces;i++){
		pthread_mutex_lock(&mutexsumaB);
		b = b + B[posicionB];	
		//printf("b: %ld\n",b);
		posicionB++;
		pthread_mutex_unlock(&mutexsumaB);
	}
}

// Practica 3 - Productor y Cosumidor con hilos y mutexes
// Sistemas Operativos II 2022-2023
// Autores: Marcelo Fort Muñoz y Laura Salgueiro Sanchez

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h> 
#include <time.h> 
#include <errno.h>

//Constantes
#define P 1 // productores
#define C 3 // consumidores
#define N 10 // tamano del buffer
#define ITEMS_BY_P 20 // items por cada productor

//Colores
#define KNADA	"\x1B[0m"
#define KTURQ	"\x1b[1;36m"
#define KBOR	"\x1b[1;33;91m"

//Variables globales
int contador = 0; //numero de elementos en el buffer
int posicionA=0, posicionB=0;
int buffer[N]; //buffer que guarda los elementos
int A[100*P],B[100*C];
long int a=0, b=0;	//variables en las que se almacenará la suma de los vectores
int elementosquitados=0, yaterminado=0;

//Mutexes y variables de condición
pthread_mutex_t mutexbuffer, mutexsumaA, mutexsumaB;
pthread_cond_t condicionlleno, condicionvacio, condicionsumaA, condicionsumaB;
pthread_mutex_t mutexelementostotales;

//Funciones
int produce_item();
void insert_item(int *buffer, int producto);
int consume_item(int *buffer);
void mostrar_hora();
void mostrar_buffer(int *buffer);
long int sumaprod();	//inline
long int sumacons();
void funcionproductor(int nhilo);
void funcionconsumidor(int nhilo);


int main() {

	pthread_t productor[P],consumidor[C];    //hilos productor y consumidor

	pthread_mutex_destroy(&mutexbuffer);
	pthread_mutex_destroy(&mutexsumaA);
	pthread_mutex_destroy(&mutexsumaB);
	//destruir variables de condición
	pthread_mutex_destroy(&mutexelementostotales);
	pthread_mutex_init(&mutexbuffer,NULL);	//inicializamos el mutex
	pthread_mutex_init(&mutexelementostotales,NULL);	//inicializamos el mutex
	pthread_mutex_init(&mutexsumaA,NULL);	//inicializamos el mutex
	pthread_mutex_init(&mutexsumaB,NULL);	//inicializamos el mutex
	pthread_cond_init(&condicionlleno,NULL);	//inicializamos la condicion
	pthread_cond_init(&condicionvacio,NULL);	//inicializamos la condicion
	pthread_cond_init(&condicionsumaA,NULL);	//inicializamos la condicion
	pthread_cond_init(&condicionsumaB,NULL);	//inicializamos la condicion
	
	//inicializamos los vectores de sumar
	for(int i=0;i<100*P;i++){
		A[i]=i;
	}	
	for(int i=0;i<100*C;i++){
		B[i]=i;
	}	
	
	for(int i=0;i<N;i++){	//inicializamos el buffer
		buffer[i]=-1;
	}
	//mostrar_buffer(buffer);
	
	
	//creamos los hilos de productor y consumidor
	for(int i=0;i<P;i++){
		pthread_create(&productor[i], NULL, (void*)&funcionproductor, (void*)(intptr_t)i);
	}
	for(int i=0;i<C;i++){
		pthread_create(&consumidor[i], NULL, (void*)&funcionconsumidor, (void*)(intptr_t)i);
	}
	
	// esperamos a que los hilos terminen
	for(int i=0;i<P;i++){
		pthread_join(productor[i], NULL);
	}
	for(int i=0;i<C;i++){
		pthread_join(consumidor[i], NULL);
	}
	
	printf("Suma array A: %ld\n",a);
	printf("Suma array B: %ld\n",b);
	
	pthread_mutex_destroy(&mutexbuffer);
	pthread_mutex_destroy(&mutexsumaA);
	pthread_mutex_destroy(&mutexsumaB);
	pthread_mutex_destroy(&mutexelementostotales);
	pthread_cond_destroy(&condicionlleno);	
	pthread_cond_destroy(&condicionvacio);	
	pthread_cond_destroy(&condicionsumaA);
	pthread_cond_destroy(&condicionsumaB);
}



//HILOS

void funcionproductor(int nhilo) {

	int producto;
	long int ultimasuma; //variable para guardar los productos
	
	for(int i=0;i<ITEMS_BY_P;i++){
	
		producto = produce_item(); //producimos un producto
		
		while(pthread_mutex_trylock(&mutexbuffer)!=0){	//si no pillamos el mutex, hacemos la suma
			ultimasuma=sumaprod();
			sumaprod();
		}
		//si entra no es 1, es que pilló el mutex con el trylock, entonces entramos en región crítica


		while(contador==N){	//si el mutex esta lleno, hacemos la suma y esperamos a que nos digan que puedo meter elemento
			ultimasuma=sumaprod();
			pthread_cond_wait(&condicionlleno,&mutexbuffer);	//desbloquea el mutexbuffer y espera a que se le permita seguir por la condicionlleno
		}
		//REGION CRITICA
		insert_item(buffer, producto); //metemos el elemento en la posición que me indica el contador

		printf("%sEl productor %d inserta %d en %d %s ", KBOR, nhilo, producto, contador, KNADA);	mostrar_hora();
		//mostrar_buffer(buffer);
		contador++; //aumentamos el contador
		//REGION CRITICA
		pthread_cond_signal(&condicionvacio);	//PONER BROADCAST?
		pthread_mutex_unlock(&mutexbuffer);
		
		
		sleep(rand()%2);
	}
	
	printf("%sEl productor %d finalizó.%s\n",KBOR, nhilo,KNADA);
	
	printf("Valor final en la ultima contribución de A: %ld\n",ultimasuma);
	//printf("posicionB %d\n", posicionB);
	
}


void funcionconsumidor(int nhilo) {

	int producto, entra=0, flag=0;
	long int ultimasuma; //variable para guardar los productos
	
	while(elementosquitados!=ITEMS_BY_P*P){	//puede ser que aquí ya sepamos que ya se quitaron todos los elementos
		//meter variable condicion
		if(pthread_mutex_trylock(&mutexbuffer)!=0){
			ultimasuma=sumacons();
			entra=1;
		}
		if(entra==1){
			entra=0;
			pthread_mutex_lock(&mutexbuffer);
		}
		
		//ESTO HAY QUE VER CÓMO HACERLO MEJOR O DÓNDE METERLO
		/*if(elementosquitados==ITEMS_BY_P*P){	//si ya se quitaron todos los elementos, no puedo quitar más => salgo del bucle
											//no puedo probarlo fuera de la RC porque después de comprobarlo puede ser que se cambie el valor 
			break;
		}*/
		
		while(contador==0){	//EXPLICAR POR QUÉ EL WHILE
			ultimasuma=sumacons();	//sumo siempre que me desbloquean o solo una vez?
			/*if(elementosquitados==ITEMS_BY_P*P){	//si ya se quitaron todos los elementos, no puedo quitar más => salgo del bucle
								//no puedo probarlo fuera de la RC porque después de comprobarlo puede ser que se cambie el valor 
				break;
			}*/
			printf("Esperando consumidor %d\nElementos quitados: %d\n", nhilo,elementosquitados);mostrar_hora();
			if(yaterminado==0){
				printf("Salí por el wait\n");
				if(pthread_cond_wait(&condicionvacio,&mutexbuffer)!=0){
					printf("Error en el wait\n");
					exit(4);
				}
			}
			
			if(elementosquitados==ITEMS_BY_P*P){
				flag=1;
				printf("Consumidor %d hace unlock cuando elementosquitados==ITEMS_BY_P*P\n",nhilo);
				pthread_mutex_unlock(&mutexbuffer);	//tenemos que desbloquear el mutex porque no lo desbloqueamos luego
				break;
			}
		}
		
		if(flag==1){
			break;
		}
		/*if(elementosquitados==ITEMS_BY_P*P){	//si ya se quitaron todos los elementos, no puedo quitar más => salgo del bucle
											//no puedo probarlo fuera de la RC porque después de comprobarlo puede ser que se cambie el valor 
			break;
		}*/
		producto = consume_item(buffer);
		
		printf("%sEl consumidor %d quita %d de %d%s", KTURQ, nhilo, producto, contador-1, KNADA);
		mostrar_hora();
		//mostrar_buffer(buffer);
		
		contador--; //disminuimos en 1 el contador (porque consumimos un elemento)
		elementosquitados++;	//aumento en 1 el número de elementos quitados
		if(elementosquitados==ITEMS_BY_P*P){
			printf("Envío broadcast. Soy consumidor %d\n\n", nhilo);mostrar_hora();
			pthread_cond_broadcast(&condicionvacio);
			yaterminado=1;
		}
		pthread_cond_signal(&condicionlleno);	//una vez que quitamos un elemento, los productores que estaban bloqueados pueden seguir
												//MIRAR SI PONER BROADCAST
		pthread_mutex_unlock(&mutexbuffer);
		
		//mostrar_buffer(buffer); //mostramos el estado del buffer
		
		sleep(rand()%2);
		
	}
	
	printf("Valor final en la ultima contribución de B: %ld\n",ultimasuma);
	printf("%sEl consumidor %d finalizó.%s\n",KTURQ, nhilo, KNADA);
}



//FUNCIONES
//funcion que genera un entero aleatorio entre 0 y 10000
int produce_item(){
	return rand() % (10000 + 1); // generar un número aleatorio entre 0 y 10000
}

//funcion que coloca el elemento en el buffer
void insert_item(int *buffer, int producto){
	buffer[contador] = producto;
}
void mostrar_buffer(int *buffer){
	printf("\n------- Buffer(contador = %d) ", contador);
	mostrar_hora();
	for(int i=0;i<10;i++) printf("pos %d: %d\n", i, buffer[i]);
	mostrar_hora();
	printf("\n");
}

//funcion que retira un elemento del buffer y lo suma con el anterior si existe
int consume_item(int *buffer){
	int producto = buffer[contador-1]; //obtenemos el producto de la posicion indicada por el contador
	buffer[contador-1] = -1; //ponemos un-1 en la posicion para indicar que esta eliminado
	return producto;
}
//funcion para mostrar la hora indicando los minutos, los segundos, y los microsegundos
void mostrar_hora(){
	struct timeval tv;
	struct tm* tm_info;
   	gettimeofday(&tv, NULL);
   	tm_info = localtime(&tv.tv_sec);
	printf("(min:seg - %d:%d, microseg - %ld)\n", tm_info->tm_min, tm_info->tm_sec, tv.tv_usec);
}



long int sumaprod(){
	int veces;
	long int ultimasuma;
	veces=rand()%5 + 1;	//sumamos de cada vez un valor entre 1 y 5
	for(int i=0;i<veces && posicionA<100*P;i++){	//METER AQUÍ LA CONDICION DE posicion<100*P O EN EL CÓDIGO???
		pthread_mutex_lock(&mutexsumaA);
		a+=A[posicionA];	
		printf("a: %ld\n",a);
		posicionA++;
		ultimasuma=a;
		pthread_mutex_unlock(&mutexsumaA);
	}
	return ultimasuma;
}


long int sumacons(){
	int veces;
	long int ultimasuma;
	veces=rand()%5 + 1;	//sumamos de cada vez un valor entre 1 y 5
	for(int i=0;i<veces && posicionB<100*C;i++){
		pthread_mutex_lock(&mutexsumaB);
		b+=B[posicionB];	
		printf("b: %ld\n",b);
		posicionB++;
		ultimasuma=b;
		pthread_mutex_unlock(&mutexsumaB);
	}
	return ultimasuma;
}


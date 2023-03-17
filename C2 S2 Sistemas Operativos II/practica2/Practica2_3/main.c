#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

// Definicion de constantes
#define ITE 10
#define N ITE
#define NUM_THREAD 4

// Variables globales
int count = -1;
int buffer[N];

// Variables globales para los semaforos
sem_t *lleno;
sem_t *vacio;
sem_t *control;

// Obtenemos la hora actual en formato hh:mm:ss:ms
char* getTimeString() {

	// Obtenemos la hora actual
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int hour = tm.tm_hour;
	int min = tm.tm_min;
	int sec = tm.tm_sec;
	int ms = clock() % 1000;

	// Creamos el string con la hora actual
	char *timeString = malloc(12);
	sprintf(timeString, "%02d:%02d:%02d:%03d", hour, min, sec, ms);

	// Devolvemos el string
	return timeString;

}

// Producimos un item, como numero aleatorio entre 0 y 99
int produce_item() {
	return rand() % 100;
}

// Insertamos un item pasado por parametro en el buffer
void insert_item(int item) {
	buffer[count + 1] = item;
}

// Eliminamos un item del buffer y lo devolvemos
int consume_item() {
	// Obtener el elemento del buffer
	int ele = buffer[count];
	// Eliminar el elemento del buffer, marcandolo como -1
	buffer[count] = -1;
	// Si hay mas de un elemento en el buffer, sumar el elemento anterior
	if (count > 0) {
		ele += buffer[count - 1];
	}
	return ele;
}

// Codigo productor
void productor() {

	// Definicion de variables
	int item;

	// Bucle de ejecucion
	for(int i = 0; i < ITE; i++) {

		// Producimos el item
		printf("%s - Productor: produciendo item \n", getTimeString());
		item = produce_item();
		printf("%s - Productor: termino de producir item | Item: %d \n", getTimeString(), item);

		printf("%s - Productor: esperando hueco \n", getTimeString());
		// Esperamos a que haya hueco en el buffer
		sem_wait(vacio);

		// Esperamos a que no haya nadie en la zona critica
		sem_wait(control);

		printf("%s - Productor: insertando item | Posicion: %d \n", getTimeString(), count + 1);

		// Insertamos el item en el buffer
		insert_item(item);

		printf("%s - Productor: actualizando contador | Contador actual: %d \n", getTimeString(), count);

		count = count + 1;

		printf("%s - Productor: terminamos actualizar contador | Contador actual: %d \n", getTimeString(), count);

		// Liberamos la zona critica
		sem_post(control);

		// Avisamos de que hay un item en el buffer
		sem_post(lleno);

		sleep(rand() % 4);

	}

	pthread_exit(NULL);

}

// Proceso consumidor
void consumidor() {

	// Definicion de variables
	int item;
	int temp;

	// Bucle de ejecucion
	for(int i = 0; i < ITE; i++) {

		printf("%s - Consumidor: esperando a que existan items \n", getTimeString());
		sem_wait(lleno);

		printf("%s - Consumidor: esperando a que no haya nadie en la zona critica \n", getTimeString());
		sem_wait(control);

		// Zona critica forzada	
		item = consume_item();
		printf("%s - Consumidor: item consumido: %d \n", getTimeString(), item);

		temp = count;

		// Forzamos una posible carrera critica
		sleep(1);

		if (temp != count) {
			printf("%s - Consumidor: Ocurrio una carrera critica \n", getTimeString());
			pthread_exit(NULL);
		}
	
		printf("%s - Consumidor: actualizando contador | Contador actual: %d \n", getTimeString(), count);

		count = temp - 1;

		printf("%s - Consumidor: terminamos actualizar contador | Contador actual: %d \n", getTimeString(), count);

		// Fin de la zona critica

		// Liberamos la zona critica
		sem_post(control);

		// Avisamos de que hay un hueco en el buffer
		sem_post(vacio);
	
		printf("%s - Consumidor: item consumido: %d \n", getTimeString(), item);

		sleep(rand() % 4);

	}

	pthread_exit(NULL);

}

int main() {

	// Eliminamos los semaforos
	sem_unlink("lleno");
	sem_unlink("vacio");
	sem_unlink("control");

	// Creamos los semaforos
	lleno = sem_open("lleno", O_CREAT, 0700, 0);
	vacio = sem_open("vacio", O_CREAT, 0700, N);
	control = sem_open("control", O_CREAT, 0700, 1);

	// Inicializamos la semilla del generador de numeros aleatorios
	srand(time(NULL));

	// Inicializamos las variables
	pthread_t hilos[NUM_THREAD];
	int e = 0;

	// Inicializamos el buffer a -1
	for (int i = 0; i < N; i++) {
		buffer[i] = -1;
	}

	// Creamos los procesos con fork
	for (int i = 0; i < NUM_THREAD; i++) {

		// Creamos el hilo, si es par es productor, si es impar es consumidor
		if (i % 2 == 0) {

			e = pthread_create(&hilos[i], NULL, (void *) productor, NULL);

		} else {

			e = pthread_create(&hilos[i], NULL, (void *) consumidor, NULL);

		}

		if (e != 0) {
			printf("Error al crear el hilo %d", i);
			exit(EXIT_FAILURE);
		}

	}

	// Esperamos a que terminen los hilos
	for (int i = 0; i < NUM_THREAD; i++) {
		pthread_join(hilos[i], NULL);
	}

	// Eliminamos los semaforos
	sem_unlink("lleno");
	sem_unlink("vacio");
	sem_unlink("control");

	// Devolvemos 0
	return EXIT_SUCCESS;

}

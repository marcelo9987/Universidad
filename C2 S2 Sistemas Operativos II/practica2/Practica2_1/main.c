#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>

// Recomentacion: emplear ./main | grep carrera
// De esta manera vemos si se han producido carreras criticas o no
// De igual modo en el codigo del consumidor si comentamos el sleep, se minimiza la probabilidad de que ocurra una carrera critica

// Definicion de constantes
#define ITE 10
#define N ITE
#define NUM_PROC 4

// Puntero al primer elemento del mapa de memoria
int *ptr;

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
	int count = *ptr;
	int *buffer = ptr + sizeof(count);
	buffer[count + 1] = item;
}

// Eliminamos un item del buffer y lo devolvemos
int consume_item() {
	int count = *ptr;
	int *buffer = ptr + sizeof(count);
	// Obtenemos el elemento del buffer
	int ele = buffer[count];
	// Eliminamos el elemento del buffer, marcandolo como -1
	buffer[count] = -1;
	// Si no es el ultimo elemento del buffer, obtenemos el anterior
	if (count > 0) {
		ele += buffer[count - 1];
	}
	return ele;
}

// Proceso productor
void productor() {

	// Definicion de variables
	int item;

	// Bucle de ejecucion
	for(int i = 0; i < ITE; i++) {

		// Producimos el item
		printf("%s - Productor: produciendo item \n", getTimeString());
		item = produce_item();
		printf("%s - Productor: termino de producir item | Item: %d \n", getTimeString(), item);

		// Esperamos a que haya hueco en el buffer
		printf("%s - Productor: esperando hueco \n", getTimeString());
		while(*ptr == N - 1);

		// Insertamos el item en el buffer
		printf("%s - Productor: insertando item | Posicion: %d \n", getTimeString(), *ptr + 1);
		// Zona critica
		insert_item(item);

		// Actualizamos el contador
		printf("%s - Productor: actualizando contador | Contador actual: %d \n", getTimeString(), *ptr);
		*ptr = *ptr + 1;
		printf("%s - Productor: terminamos actualizar contador | Contador actual: %d \n", getTimeString(), *ptr);

		// No hace falta avisar al consumidor, porque tiene espera activa

		sleep(rand() % 4);

	}

	exit(EXIT_SUCCESS);

}

// Proceso consumidor
void consumidor() {

	// Definicion de variables
	int item;
	int temp;

	// Bucle de ejecucion
	for(int i = 0; i < ITE; i++) {

		// Esperamos a que haya un item en el buffer
		printf("%s - Consumidor: esperando item \n", getTimeString());
		while (*ptr == -1);
		printf("%s - Consumidor: item encontrado \n", getTimeString());

		// Consumimos el item
		printf("%s - Consumidor: obteniendo item \n", getTimeString());
		// Zona critica forzada
		item = consume_item();

		// Comprobamos si hay una carrera critica y actualizamos el contador
		printf("%s - Consumidor: actualizando contador \n", getTimeString());
	
		temp = *ptr;

		// Comentario: si se quita el sleep, se minimiza la probabilidad de que ocurra una carrera critica
		// Pero puede ocurrir igualmente
		sleep(1);

		// Se detecta una carrera critica y se muestra por pantalla
		// Existen otras formas de detectar una carrera critica, pero esta es la mas sencilla
		// Ademas de en esta zona critica, tambien se puede detectar otras zonas criticas en el codigo
		if (temp != *ptr) {
			printf("%s - Consumidor: Ocurrio una carrera critica \n", getTimeString());
			exit(EXIT_FAILURE);
		}
	
		*ptr = temp - 1;

		// Fin de la zona critica

		printf("%s - Consumidor: terminamos actualizar contador | Valor del contador: %d \n", getTimeString(), *ptr);

		// No hace falta avisar al productor, porque tiene espera activa
		printf("%s - Consumidor: item consumido: %d \n", getTimeString(), item);

		sleep(rand() % 4);

	}

	exit(EXIT_SUCCESS);

}

int main() {

	// Inicializamos la semilla del generador de numeros aleatorios
	srand(time(NULL));

	// Creamos el contador y el buffer
	// Puntero al primer elemento del mapa de memoria
	int count = -1;
	int buffer[N];

	// Inicializamos el buffer a -1
	for (int i = 0; i < N; i++) {
		buffer[i] = -1;
	}

	// Creamos el mapa de memoria
	ptr = mmap(NULL, sizeof(buffer) + sizeof(count), PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	// Comprobamos si se ha creado correctamente
	if (ptr == MAP_FAILED) {
		perror("Error al crear el mapa de memoria");
		exit(EXIT_FAILURE);
	}

	// Copiar el contador al mapa de memoria
	memcpy(ptr, &count, sizeof(count));

	// Copiar el buffer al mapa de memoria
	memcpy(ptr + sizeof(count), buffer, sizeof(buffer));

	// Creamos los procesos con fork
	for (int i = 0; i < NUM_PROC; i++) {

		// Creamos el proceso
		if (fork() == 0) {
			// Comprobamos si es el productor o el consumidor
			if (i == 0) {
				productor();
			} else {
				consumidor();
			}
		}

	}

	// Esperamos a que terminen los procesos
	for (int i = 0; i < NUM_PROC; i++) {
		wait(NULL);
	}

	// Cerramos el mapa de memoria
	munmap(ptr, sizeof(buffer) + sizeof(count));

	// Devolvemos 0
	return EXIT_SUCCESS;

}

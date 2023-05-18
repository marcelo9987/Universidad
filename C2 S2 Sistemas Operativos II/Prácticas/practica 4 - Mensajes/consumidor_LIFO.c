#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_BUFFER 5 /* tamaño del buffer */
#define DATOS_A_CONSUMIR 100 /* número de datos a producir/consumir */

// Los nombres de almacén para las colas de productor y consumidor son diferentes entre ellos.
// Además, estos son distintos en las versiones FIFO y LIFO.
// La totalidad del código de este fichero es equivalente al de consumidor_FIFO.c, salvo por los nombres de las colas de mensajes.
#define NOMBRE_ALMACEN_C2P "/ALMACEN_C2P_LIFO"
#define NOMBRE_ALMACEN_P2C "/ALMACEN_P2C_LIFO"

/* cola de entrada de mensajes para el productor */
mqd_t almacenConsumidorHaciaProductor;

/* cola de entrada de mensajes para el consumidor */
mqd_t almacenProductorHaciaConsumidor;

/**
 * Función que obtiene el número de mensajes en una cola de mensajes.
 * @param almacen Cola de mensajes de la que se quiere obtener el número de mensajes.
 * @return Número de mensajes en la cola de mensajes recibida como parámetro.
 */
int obtenerNumeroMensajesEnCola(mqd_t almacen)
{
    struct mq_attr attr;

    // Esta función nos permite obtener los atributos de la cola de mensajes almacen en la variable attr.
    mq_getattr(almacen, &attr);

    // La variable attr.mq_curmsgs contiene el número de mensajes que hay en este momento en la cola de mensajes.
    return attr.mq_curmsgs;
}

/**
 * Función que imprime el estado de las colas de mensajes. Se utiliza para poder tener un control visual de la ejecución del consumidor.
 * @param iter Número de iteración en la que se encuentra el consumidor (Se utiliza para imprimirlo por pantalla).
 * @param comentario Comentario adicional que se quiere imprimir por pantalla.
 */
void imprimirEstadoColas(int iter, char *comentario)
{
    printf("[Consumidor] [iter: %3d] [Almacén C->P: %d elems] [Almacén P->C: %d elems] %s\n", iter,
           obtenerNumeroMensajesEnCola(almacenConsumidorHaciaProductor),
           obtenerNumeroMensajesEnCola(almacenProductorHaciaConsumidor), comentario);
}

/**
 * Función equivalente a la anterior, pero que además imprime el elemento que se ha recibido.
 * @param iter Número de iteración en la que se encuentra el consumidor (Se utiliza para imprimirlo por pantalla).
 * @param comentario Comentario adicional que se quiere imprimir por pantalla.
 * @param elem Elemento que se ha recibido en la cola de mensajes.
 */
void imprimirEstadoColas_c(int iter, char *comentario, char elem)
{
    if (elem == '\0')
    {
        printf("[Consumidor] [iter: %3d] [Almacén C->P: %d elems] [Almacén P->C: %d elems] %s (vacío)\n",
               iter, obtenerNumeroMensajesEnCola(almacenConsumidorHaciaProductor),
               obtenerNumeroMensajesEnCola(almacenProductorHaciaConsumidor), comentario);
    } else
    {
        printf("[Consumidor] [iter: %3d] [Almacén C->P: %d elems] [Almacén P->C: %d elems] %s %c\n",
               iter, obtenerNumeroMensajesEnCola(almacenConsumidorHaciaProductor),
               obtenerNumeroMensajesEnCola(almacenProductorHaciaConsumidor), comentario, elem);
    }
}

/**
 * Esta función nos permite modelar los diferentes comportamientos que queremos que tengan el productor y el consumidor.
 * Nos ayudará a conseguir que la cola del productor se llene y se vacíe según la fase.
 * Está explicado con mayor profundidad en la memoria de la práctica.
 * @param iter Número de iteración en la que se encuentra el consumidor (Se utiliza para saber en qué fase se encuentra).
 */
void dormir(int iter)
{
    int sleep_ms;

    if (iter < 20)
    {
        sleep_ms = 0;
        if (iter == 0)
        {
            imprimirEstadoColas(iter, "[elems 0 - 19] En esta fase no duermo entre consumiciones");
        }
    } else if (iter < 40)
    {
        sleep_ms = 100;
        if (iter == 20)
        {
            imprimirEstadoColas(iter, "[elems 20 - 39] En esta fase duermo 100 ms entre consumiciones.\n*** Esto forzará el llenado del buffer *** puesto que el productor sigue sin dormir entre producciones");
        }
    } else if (iter < 50)
    {
        sleep_ms = 0;
        if (iter == 40)
        {
            imprimirEstadoColas(iter, "[elems 40 - 49] En esta fase no duermo entre consumiciones.\n*** Esto forzará el vaciado del buffer *** puesto que el productor sigue durmiendo entre producciones");
        }
    } else
    {
        sleep_ms = rand() % 200;
        if (iter == 50)
        {
            imprimirEstadoColas(iter, "[elems 50 - 100] En esta fase duermo un tiempo aleatorio (entre 0 y 200) entre consumiciones");
        }
    }

    if (sleep_ms > 0)
    {
        // Indicamos el tiempo que queremos dormir en microsegundos.
        usleep(sleep_ms * 1000);
    }
}

/**
 * Función que envía un mensaje al productor. Se utiliza para indicarle que puede producir un elemento.
 * @param mensaje Mensaje que se quiere enviar al productor. En este caso, siempre será un carácter nulo.
 * @param iter Número de iteración en la que se encuentra el consumidor (Se utiliza para imprimirlo por pantalla).
 */
void enviaMensajeAlProductor(const char *mensaje, int iter)
{
    imprimirEstadoColas_c(iter, "Envío mensaje al productor: ", mensaje[0]);
    mq_send(almacenConsumidorHaciaProductor, mensaje, sizeof(char), 0);
}

/**
 * Función que extrae un elemento de la cola de mensajes del consumidor.
 * @param mensaje Mensaje que se quiere extraer de la cola de mensajes del consumidor.
 * @param iter Número de iteración en la que se encuentra el consumidor (Se utiliza para imprimirlo por pantalla).
 * @return Elemento que se ha extraído de la cola de mensajes del consumidor.
 */
char extraer_elemento(char *mensaje, int iter)
{
    char elem = *mensaje;

    imprimirEstadoColas_c(iter, "Extraigo elemento", elem);

    *mensaje = '\0';

    return elem;
}

/**
 * Función que consume un elemento.
 * @param elemento Elemento que se quiere consumir.
 * @param iter Número de iteración en la que se encuentra el consumidor (Se utiliza para imprimirlo por pantalla).
 */
void consumir_elemento(char elemento, int iter)
{
    imprimirEstadoColas_c(iter, "Consumo elemento", elemento);
}

/**
 * Función que modela el comportamiento del consumidor.
 */
void consumidor(void)
{
    char elem;
    char mensaje = '\0';

    // Enviamos al productor, nada más empezar, tantos mensajes como elementos puede almacenar el buffer.
    for (int iter = 0; iter < MAX_BUFFER; iter++)
    {
        enviaMensajeAlProductor(&mensaje, iter);
    }

    // Empieza nuestro proceso real de consumo de mensajes.
    for (int iter = 0; iter < DATOS_A_CONSUMIR; iter++)
    {
        // Se duerme el tiempo que corresponda según la fase en la que se encuentre el consumidor.
        dormir(iter);

        // Recibimos un mensaje del productor. En caso de que no haya mensajes, se bloquea hasta que llegue uno.
        mq_receive(almacenProductorHaciaConsumidor, &mensaje, sizeof(char), 0);

        // Extraemos el elemento del mensaje.
        elem = extraer_elemento(&mensaje, iter);

        // En caso de que no estemos consumiendo ya los últimos mensajes, enviamos un mensaje al productor para que produzca otro elemento.
        if (iter < DATOS_A_CONSUMIR - MAX_BUFFER)
        {
            enviaMensajeAlProductor(&mensaje, iter);
        }

        // Una vez ya solicitado un nuevo elemento al productor, consumimos "tranquilamente" el elemento que hemos extraído.
        consumir_elemento(elem, iter);
    }
}


int main(void)
{
    struct mq_attr attr; /* Atributos de la cola */
    attr.mq_maxmsg = MAX_BUFFER;
    attr.mq_msgsize = sizeof(char);

    // El consumidor no ha de borrar los almacenes, puesto que se ejecuta primero el productor.

    // Apertura de de las colas de mensajes, una de solo lectura y otra de solo escritura.
    almacenConsumidorHaciaProductor = mq_open(NOMBRE_ALMACEN_C2P, O_CREAT | O_RDONLY, 0777, &attr);
    almacenProductorHaciaConsumidor = mq_open(NOMBRE_ALMACEN_P2C, O_CREAT | O_WRONLY, 0777, &attr);

    // Comprobación de errores en la apertura de los buffers.
    if ((almacenConsumidorHaciaProductor == -1) || (almacenProductorHaciaConsumidor == -1))
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Inicialización de la semilla para la generación de números aleatorios.
    // Es importante que sea diferente a la del consumidor, ya que si no, se producirían los mismos números aleatorios en ambos procesos.
    srand(getpid());

    // Llamada a la función consumidor, que se encarga de solicitar y consumir los elementos que le manda el productor.
    consumidor();

    // Nos aseguramos de que no queden mensajes en las colas de mensajes (La comprobación será visual, viendo después el log de la ejecución).
    imprimirEstadoColas(DATOS_A_CONSUMIR, "Fin de la consumición");

    // Cierre de los buffers.
    mq_close(almacenConsumidorHaciaProductor);
    mq_close(almacenProductorHaciaConsumidor);

    return EXIT_SUCCESS;
}

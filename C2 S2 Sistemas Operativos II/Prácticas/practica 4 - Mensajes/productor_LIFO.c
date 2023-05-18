#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define MAX_BUFFER 5 /* tamaño del buffer */
#define DATOS_A_PRODUCIR 100 /* número de datos a producir/consumir */

// Los nombres de almacén para las colas de productor y consumidor son diferentes entre ellos.
// Además, estos son distintos en las versiones FIFO y LIFO.
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
 * Función que imprime el estado de las colas de mensajes. Se utiliza para poder tener un control visual de la ejecución del productor.
 * @param iter Número de iteración en la que se encuentra el productor (Se utiliza para imprimirlo por pantalla).
 * @param comentario Comentario adicional que se quiere imprimir por pantalla.
 */
void imprimirEstadoColas(int iter, char *comentario)
{
    printf("[Productor]  [iter: %3d] [Almacén C->P: %d elems] [Almacén P->C: %d elems] %s\n", iter,
           obtenerNumeroMensajesEnCola(almacenConsumidorHaciaProductor),
           obtenerNumeroMensajesEnCola(almacenProductorHaciaConsumidor), comentario);
}

/**
 * Función equivalente a la anterior, pero que además imprime el elemento que se ha producido.
 * @param iter Número de iteración en la que se encuentra el productor (Se utiliza para imprimirlo por pantalla).
 * @param comentario Comentario adicional que se quiere imprimir por pantalla.
 * @param elem Elemento que se ha producido.
 */
void imprimirEstadoColas_c(int iter, char *comentario, char elem)
{
    if (elem == '\0')
    {
        printf("[Productor]  [iter: %3d] [Almacén C->P: %d elems] [Almacén P->C: %d elems] %s (vacío)\n",
               iter, obtenerNumeroMensajesEnCola(almacenConsumidorHaciaProductor),
               obtenerNumeroMensajesEnCola(almacenProductorHaciaConsumidor), comentario);
    } else
    {
        printf("[Productor]  [iter: %3d] [Almacén C->P: %d elems] [Almacén P->C: %d elems] %s %c\n",
               iter, obtenerNumeroMensajesEnCola(almacenConsumidorHaciaProductor),
               obtenerNumeroMensajesEnCola(almacenProductorHaciaConsumidor), comentario, elem);
    }
}

/**
 * Esta función nos permite modelar los diferentes comportamientos que queremos que tengan el productor y el consumidor.
 * Nos ayudará a conseguir que la cola del productor se llene y se vacíe según la fase.
 * Está explicado con mayor profundidad en la memoria de la práctica.
 * @param iter Número de iteración en la que se encuentra el productor (Se utiliza para saber en qué fase se encuentra).
 */
void dormir(int iter)
{
    int sleep_ms;

    if (iter < 30)
    {
        sleep_ms = 0;
        if (iter == 0)
        {
            imprimirEstadoColas(iter, "[elems 0 - 29] En esta fase no duermo entre producciones");
        }
    } else if (iter < 50)
    {
        sleep_ms = 100;
        if (iter == 30)
        {
            imprimirEstadoColas(iter, "[elems 30 - 49] En esta fase duermo 100 ms entre producciones");
        }
    } else
    {
        sleep_ms = rand() % 200;
        if (iter == 50)
        {
            imprimirEstadoColas(iter, "[elems 50 - 99] En esta fase duermo un tiempo aleatorio (entre 0 y 200) entre producciones");
        }
    }

    if (sleep_ms > 0)
    {
        // Indicamos el tiempo que queremos dormir en microsegundos.
        usleep(sleep_ms * 1000);
    }
}

/**
 * Función que produce un elemento. En este caso, simplemente devuelve un carácter que se corresponde con el elemento que se quiere producir.
 * @param iter Número de iteración en la que se encuentra el productor (Se utiliza para saber qué elemento se quiere producir).
 * @return Elemento de tipo carácter que se quiere producir.
 */
char producir_elemento(int iter)
{
    char elem = 'a' + iter % MAX_BUFFER;

    imprimirEstadoColas_c(iter, "Produzco elemento:", elem);

    return elem;
}

/**
 * Función que construye el mensaje que se va a enviar al consumidor. En este caso, simplemente se copia el elemento en el mensaje.
 * @param mensaje Puntero al mensaje que se va a enviar al consumidor.
 * @param elem Elemento de tipo char que se quiere enviar al consumidor.
 */
void construir_mensajeProductor(char *mensaje, char elem)
{
    *mensaje = elem;
}

/**
 * Función que se encarga de producir los elementos y enviarlos al consumidor.
 * Tenemos un único productor y un único consumidor, con un buffer limitado y que se sincronizan mediante paso de mensajes.
 */
void productor(void)
{
    char mensaje;

    // El número de elementos a producir por el productor es el mismo que el número de elementos a consumir por el consumidor, conocido de antemano por ambos.
    for (int iter = 0; iter < DATOS_A_PRODUCIR; iter++)
    {
        // Se duerme el tiempo que corresponda según la fase en la que se encuentre el productor.
        dormir(iter);

        // Se produce un elemento de tipo char, incluso antes de que haya sido solicitado, ya que sabemos que el consumidor lo va a solicitar.
        char elem = producir_elemento(iter);

        // Nos quedamos bloqueados, a la espera de que el consumidor nos solicite un elemento.
        mq_receive(almacenConsumidorHaciaProductor, &mensaje, sizeof(char), 0);

        // Construimos el mensaje que se va a enviar al consumidor.
        construir_mensajeProductor(&mensaje, elem);

        // Imprimimos el estado de las colas antes de enviar el mensaje.
        imprimirEstadoColas_c(iter, "Envío mensaje:", elem);

        // Enviamos el mensaje al consumidor.
        // En este caso mandamos todos con prioridad cada vez mayor, ya que queremos que los elementos nuevos se consuman antes que los antiguos.
        // Esta es la única diferencia entre el productor LIFO y el FIFO.
        mq_send(almacenProductorHaciaConsumidor, &mensaje, sizeof(char), iter);
    }
}


int main(void)
{
    struct mq_attr attr; /* Atributos de la cola */
    attr.mq_maxmsg = MAX_BUFFER;
    attr.mq_msgsize = sizeof(char);

    // Borrado de las colas de mensajes por si contenian elementos de una ejecución previa
    mq_unlink(NOMBRE_ALMACEN_C2P);
    mq_unlink(NOMBRE_ALMACEN_P2C);

    // Apertura de de las colas de mensajes, una de solo lectura y otra de solo escritura.
    almacenConsumidorHaciaProductor = mq_open(NOMBRE_ALMACEN_C2P, O_CREAT | O_RDONLY, 0777, &attr);
    almacenProductorHaciaConsumidor = mq_open(NOMBRE_ALMACEN_P2C, O_CREAT | O_WRONLY, 0777, &attr);

    // Comprobación de errores en la apertura de las colas de mensajes.
    if ((almacenConsumidorHaciaProductor == -1) || (almacenProductorHaciaConsumidor == -1))
    {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    // Inicialización de la semilla para la generación de números aleatorios.
    // Es importante que sea diferente a la del consumidor, ya que si no, se producirían los mismos números aleatorios en ambos procesos.
    srand(getpid());

    // Llamada a la función productor, que se encarga de producir los elementos y enviarlos al consumidor.
    productor();

    // Nos aseguramos de que no queden mensajes en las colas de mensajes (La comprobación será visual, viendo después el log de la ejecución).
    imprimirEstadoColas(DATOS_A_PRODUCIR, "Fin de la producción");

    // Cierre de las colas de mensajes.
    mq_close(almacenConsumidorHaciaProductor);
    mq_close(almacenProductorHaciaConsumidor);

    return EXIT_SUCCESS;
}

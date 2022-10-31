/*
 * 3. El siguiente código esboza un programa que utiliza las señales SIGUSR1 y SIGUSR2 entre un
 * proceso padre y otro hijo con una única función personalizada de captura de estas señales. Analiza
 * el código, complétalo según se indica en las líneas comentadas y comprueba su funcionamiento.
*/

/* Incluye las librerias necesarias*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static void gestion(int); /*Declaracion de la funcion de gestion de señales recibidas*/
int main()
{
/* Declara las variables necesarias*/
    pid_t padre = getpid();
    pid_t hijo;
    if (signal(SIGUSR1, gestion) == SIG_ERR)
    {
        printf("Error al crear gestor 1\n");
    }
    if (signal(SIGUSR2, gestion) == SIG_ERR)
    {
        printf("Error al crear gestor 2\n");
    }
    //  if (signal(SIGTERM, gestion) == SIG_ERR)
    //  {
    //      printf("Error al crear gestor 3\n");
    //  }

//    printf("prefork\n");
    if ((hijo = fork()) == 0)
    { /*Trabajo del hijo*/
        printf("[%d] Soy el hijo\n", getpid());
        sleep(1);
        printf("[Hijo] Voy a enviar SIGUSR1 al padre.\n");
        kill(padre, SIGUSR1); /*Envia señal al padre*/
        printf("[Hijo] Ya se ha enviado la señal SIGUSR1 al padre.\n");
        for (;;); /*Espera señal del padre indefinidamente*/
    } else
    {
        printf("[%d] Soy el padre\n", getpid());
        int status;
        /*Trabajo del padre*/
        /* Completa el código del padre para enviar las señales SIGUSR2 y SIGTERM al hijo,
        y espera a que acabe con wait */
        sleep(1);
        printf("[Padre] Voy a enviar SIGUSR2 al hijo.\n");
        kill(hijo, SIGUSR2);//SIGUSR2 = 12 y es una señal para uso libre del usuario
        sleep(1);
        printf("[Padre] Voy a enviar SIGTERM al hijo.\n");
        kill(hijo, SIGTERM);//SIGTERM = 9 termina un proceso.
        printf("[Padre] Voy a esperar al hijo.\n");
        pid_t pidSalida = wait(&status);
        printf("[Padre] He salido del wait. pid del wait: %d, estatus: %i, valor de salida: %d\n", pidSalida, status,
               WEXITSTATUS(status));
        
    }
}

static void gestion(int numero_de_senhal)
{ /* Funcion de gestion de señales*/
    switch (numero_de_senhal)
    {
        case SIGUSR1: /*Entra señal SIGUSR1*/
            printf("[%d] Señal tipo 1 recibida.\n", getpid());
            break;
        case SIGUSR2: /*Entra señal SIGUSR1*/
            printf("[%d] Señal tipo 2 recibida.\n", getpid());
            break;
//        case SIGTERM:
//            printf("Señal tipo finalización recibida. Soy %d \n", getpid());
////            exit(0);
//            /*Completa para el resto de las señales usadas*/
//            return;
        default:
            printf("[%d] Recibida señal no esperada (%d).\n", getpid(), numero_de_senhal);
            break;
    }
}
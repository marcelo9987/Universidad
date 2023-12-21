#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>

#define SALIDA_ERRORES stdout

#define TAMANHO_LINEA 1000

struct EntradaTablaEnrutamiento
{
    char direccion_txt[INET_ADDRSTRLEN];
    struct in_addr direccion_bin;
    int longitud_prefijo;
    int num_interfaz_salida;
};

void imprimir_ayuda(char *nombreArchivo)
{
    printf("Uso:\n");
    printf("%s <archivoTablas> <IP>\n", nombreArchivo);
    printf("Opción\t\t\tSignificado\n");
    printf("archivoTablas\t\tArchivo en el que se guardan las tablas con las direcciones ip, máscaras e interfaces\n");
    printf("IP\t\t\tIP que será redireccionada\n");
}

bool cadena2entero(const char *const cadena, int *const entero)
{
    char *endptr = NULL;

    errno = 0;

    long valor = strtol(cadena, &endptr, 10);

    if (errno != 0) // Ha ocurrido algún error.
    {
        return false;
    }

    if (endptr == cadena) // No se ha leído ningún dígito.
    {
        return false;
    }

    *entero = (int) valor; // Damos por válido el número leído

    if (*endptr != '\0' && *endptr != '\n') // No se ha leído la cadena completa.
    {
        fprintf(SALIDA_ERRORES, "[AVISO] Se ha leído la cadena <<%s>>, pero no se ha leído la cadena completa.\n", cadena);
        return true;
    }

    return true;
}

bool getDireccionQueEnrutar(char *const direccion_txt, struct EntradaTablaEnrutamiento *const ipQueEnrutar)
{
    ipQueEnrutar->longitud_prefijo = -1; // Sin sentido en este caso
    ipQueEnrutar->num_interfaz_salida = -1; // Lo guardaremos cuando lo conozcamos.

    // Pasamos la IP de entrada a binario.
    switch (inet_pton(AF_INET, direccion_txt, (void *) &ipQueEnrutar->direccion_bin))
    {
        case 1: // Éxito.
            break;

        case 0: // Formato de dirección incorrecto.
            fprintf(SALIDA_ERRORES, "[ERROR] Formato de dirección incorrecto.\n");
            return false;

        case -1: // Ha ocurrido algún error como que no se conozca la familia de direcciones.
            perror("[ERROR] al procesar el formato la dirección IP de entrada");
            return false;

        default: // Caso no controlado.
            fprintf(SALIDA_ERRORES, "[ERROR] desconocido al procesar el formato la dirección IP de entrada.\n");
            return false;;
    }

    // Una vez que sabemos que es válida, copiamos la dirección IP de entrada.
    strcpy(ipQueEnrutar->direccion_txt, direccion_txt);

    printf("IP proporcionada: %s\n", ipQueEnrutar->direccion_txt);

    return true;
}


bool getEntradaTablaEnrutamiento(const int num_linea, char *const linea, struct EntradaTablaEnrutamiento *const entrada)
{

    // Ejemplos de líneas válidas:
    // 194.32.0.0/11,1
    // 194.64/16,2

    // Leemos la cadena que contiene la dirección IP/sufijo de la entrada de la tabla.
    char *direccion_txt = strtok(linea, ","); // "194.32.0.0/11", "194.64/16", ...

    // Leemos la cadena que contiene el número de interfaz de la entrada de la tabla.
    char *interfaz_tabla_txt = strtok(NULL, ","); // "0","1", "2", ...
    if (interfaz_tabla_txt == NULL)
    {
        fprintf(SALIDA_ERRORES, "[ERROR] Formato de la tabla incorrecto: No se ha indicado la dirección de la interfaz en la línea %d\n", num_linea);
        return false;
    }

    // Leemos un posible resto de línea de la entrada de la tabla.
    char *resto_linea = strtok(NULL, ",");
    if (resto_linea != NULL)
    {
        fprintf(SALIDA_ERRORES, "[AVISO] Se han introducido más datos de los necesarios en la línea %d\n", num_linea);
    }

    //--

    // struct in_addr direccion_bin;

    // Note: the buffer pointed to by netp should be zeroed out before
    // calling inet_net_pton(), since the call writes only as many bytes
    // as are required for the network number (or as are explicitly
    // specified by pres), which may be less than the number of bytes in
    // a complete network address.
    entrada->direccion_bin.s_addr = 0;

    // int longitud_prefijo;

    // Convertimos a binario la IP de la tabla.
    if ((entrada->longitud_prefijo = inet_net_pton(AF_INET, direccion_txt, (void *) &entrada->direccion_bin, sizeof(struct in_addr))) == -1)
    {
        perror("[ERROR] Formato incorrecto de la dirección leída en la tabla");
        return false;
    }

    //--

    //long num_interfaz_salida;

    // Comprobamos si se ha leído correctamente el número de la interfaz.
    if (cadena2entero(interfaz_tabla_txt, &entrada->num_interfaz_salida) == false)
    {
        fprintf(SALIDA_ERRORES, "[ERROR] Formato de la tabla incorrecto en la línea %d: No se ha indicado un número de interfaz válido.\n", num_linea);
        return false;
    }

    if (entrada->num_interfaz_salida < 0)
    {
        fprintf(SALIDA_ERRORES, "[ERROR] Formato de la tabla incorrecto en la línea %d: Los números de interfaz no pueden ser negativo.\n", num_linea);
        return false;
    }

    // Una vez que sabemos que es válida, copiamos la dirección IP de entrada.
    strcpy(entrada->direccion_txt, direccion_txt);

    return true;
}

bool comprobarSiEsUnaRutaAplicable(struct EntradaTablaEnrutamiento *entrada, struct EntradaTablaEnrutamiento *ipQueEnrutar, bool *const es_ruta_aplicable)
{
    printf("[DEBUG] IP        : %-16s", ipQueEnrutar->direccion_txt);

    char netaddr_txt[INET_ADDRSTRLEN];

    // Obtenemos (como cadena de texto) la "dirección de red" asociada a la IP que queremos enrutar, en caso de que usáramos la longitud de prefijo indicada en esta entrada de la tabla de enrutoamiento..
    if (inet_net_ntop(AF_INET, (void *) &ipQueEnrutar->direccion_bin, (*entrada).longitud_prefijo, netaddr_txt, INET_ADDRSTRLEN) == NULL)
    {
        printf("Formato de dirección incorrecto.\n");
        return false;
    }

    printf(" -> %-16s", netaddr_txt);

    // --

    struct in_addr ip_en_esa_red_bin;
    ip_en_esa_red_bin.s_addr = 0;

    // Convertimos a binario la dirección de red recién obtenida en el paso anterior.
    if ((inet_net_pton(AF_INET, netaddr_txt, (void *) &ip_en_esa_red_bin, sizeof(struct in_addr))) < 0)
    {
        fprintf(SALIDA_ERRORES, "Formato de dirección incorrecto.\n");
        return false;
    }

    printf(" -> %-16s", ipQueEnrutar->direccion_txt);

    // --

    // Comprobamos si la IP que queremos enrutar está en la red de esta entrada de la tabla de enrutamiento.
    // Esto será cierto si ambas direcciones binarias son iguales.
    if (entrada->direccion_bin.s_addr == ip_en_esa_red_bin.s_addr)
    {
        *es_ruta_aplicable = true;
    } else
    {
        *es_ruta_aplicable = false;
    }

    return true;
}

int main(int argc, char *argv[])
{
/*
    // Dirección y sufijo por defecto. Los rellenaremos ucando los enontremos en la tabla que vamos a leer de archivo
    struct EntradaTablaEnrutamiento rutaPorDefecto;

    rutaPorDefecto.direccion_txt = NULL;
    rutaPorDefecto.direccion_bin.s_addr = 0;
    rutaPorDefecto.longitud_prefijo = -1;
    rutaPorDefecto.num_interfaz_salida = -1;
*/

    int num_interfaz_ruta_por_defecto = -1; // La inicializamos a un valor que no puede ser válido

    // --

    // Variable bandera (se utiliza la regla del prefijo más largo).
    // TODO !!
//    bool encontradaRutaAdecuada = false;

    //--

    if (argc != 3)
    {
        fprintf(SALIDA_ERRORES, "[ERROR] Número de parámetros introducidos erróneo.\n");
        imprimir_ayuda(argv[0]);
        exit(EXIT_FAILURE);
    }

    //--

    FILE *fp = fopen(argv[1], "rt");
    if (fp == NULL)
    {
        perror("[ERROR] al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    //--

    struct EntradaTablaEnrutamiento ipQueEnrutar;

    if (getDireccionQueEnrutar(argv[2], &ipQueEnrutar) == false)
    {
        fclose(fp);
        exit(EXIT_FAILURE);
    };

    // --

    struct EntradaTablaEnrutamiento rutaSalida;
    rutaSalida.direccion_txt[0] = '\0';
    rutaSalida.direccion_bin.s_addr = 0;
    rutaSalida.longitud_prefijo = -1;
    rutaSalida.num_interfaz_salida = -1; // Lo guardaremos cuando lo conozcamos. Si finalmente sigue poniendo -1, quiere decir que no hemos encontrado un aru ta adecuada

    // --

    int num_linea = 0;

    char linea[TAMANHO_LINEA];

    // Bucle para leer la tabla de reenvío.
    while (fgets(linea, TAMANHO_LINEA, fp) != NULL)
    {
        num_linea++;

//        printf("\n[DEBUG] ###########################\n");
        printf("\n[DEBUG] Línea %3d : %s", num_linea, linea);

        if (linea[0] == '\n' || linea[0] == '\r' || linea[0] == '#') // Si la línea está vacía o es un comentario, la ignoramos.
        {
            continue;
        }

        // --

        struct EntradaTablaEnrutamiento entrada;

        // Leemos la línea de la tabla de reenvío.
        if (getEntradaTablaEnrutamiento(num_linea, linea, &entrada) == false)
        {
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        printf("[DEBUG] Procesado : %-16s / %2d -> %3d\n", entrada.direccion_txt, entrada.longitud_prefijo, entrada.num_interfaz_salida);

        // Comprobamos si se se trata de la ruta por defecto.
        if (entrada.longitud_prefijo == 0)
        { // Están indicándonos la ruta por defecto.

            printf("[DEBUG] Encontrada ruta por defecto. No comprobaremos si la IP hace match, porque sabemos que lo hará siempre.\n");
            printf("[DEBUG] Sólo usaremos esta ruta si no encontramos ninguna más adecuada.\n");

            // En el enunciado se nos indica admeás que "La interfaz por defecto debe ser la 0".
            // Vamos por lo tanto a confirmarlo. La aceptaremos aunque no sea la 0, pero mostraremos un aviso.
            if (entrada.num_interfaz_salida != 0)
            {
                fprintf(SALIDA_ERRORES, "[AVISO] Se ha indicado una interfaz por defecto (la %d) distinta de la esperada según el enunciado (la 0) en la línea %d. Aun así, será la %d que tomemos por defecto.\n", entrada.num_interfaz_salida, num_linea, entrada.num_interfaz_salida);
            }

            if (num_interfaz_ruta_por_defecto >= 0)
            {
                fprintf(SALIDA_ERRORES, "[AVISO] Se ha indicado más de una ruta por defecto en la tabla. Se utilizará la leída en la línea %d.\n", num_linea);
            }

            // No me hace falta para nada la dirección de salida de la ruta por defecto. Sólo me apunto el número de la interfaz

            num_interfaz_ruta_por_defecto = entrada.num_interfaz_salida;
        } else
        {
            // NO me voy a molestar en comprobar las entradas que sean rutas por defecto. Ya las usaría luego si no hay una mejor opción.
            // Pero el resto de rutas, sí tengo que ver si hacen "match" con mi dirección de destino.

            bool es_ruta_aplicable = false;

            if (comprobarSiEsUnaRutaAplicable(&entrada, &ipQueEnrutar, &es_ruta_aplicable) == false)
            {
                fclose(fp);
                exit(EXIT_FAILURE);
            }

            if (es_ruta_aplicable)
            {
                if (entrada.longitud_prefijo > rutaSalida.longitud_prefijo)
                {
                    printf(" [+]\n");

                    rutaSalida.longitud_prefijo = entrada.longitud_prefijo;
                    rutaSalida.num_interfaz_salida = entrada.num_interfaz_salida; // Ya tenemos una ruta adecuada. Puede que haya luego una mejor
                    strcpy(rutaSalida.direccion_txt, entrada.direccion_txt);
                    rutaSalida.direccion_bin = entrada.direccion_bin;

                } else if (entrada.longitud_prefijo == rutaSalida.longitud_prefijo)
                {
                    // Hemos encontrado una ruta igual de buena que la que ya teníamos. Nos quedamos con la primera
                    printf(" [=]\n");
                } else
                {
                    // La ruta que hemos encontrado es peor que la que ya teníamos. La ignoramos.
                    printf(" [-]\n");
                }
            } else
            {
                // La ruta no es adecuada para esta dirección
                printf(" [x]\n");
            }
        }
    }

    fclose(fp);

    printf("\n[DEBUG] ###########################\n");

    if (rutaSalida.num_interfaz_salida >= 0)
    {
        printf("Hemos encontrado una ruta adecuada para la IP a enrutar (%s).\n", ipQueEnrutar.direccion_txt);
        printf("Dirección de la tabla de enrutamiento                  : %s\n", rutaSalida.direccion_txt);
        printf("Interfaz de salida                                     : %d\n", rutaSalida.num_interfaz_salida);
        printf("Nº de bits del prefijo correspondiente a la interfaz   : %d\n", rutaSalida.longitud_prefijo);

    } else
    {
        printf("No se ha encontrado en la tabla de enrutamiento ninguna ruta que pueda ser utilizada coincida con la IP a enrutar (%s).\n", ipQueEnrutar.direccion_txt);

        if (num_interfaz_ruta_por_defecto < 0)
        {
            printf("Tampoco se ha indicado en la tabla de rutas una ruta por defecto, pero en el enunciado se indica que se use la 0 para este fin.\n");
            num_interfaz_ruta_por_defecto = 0;
        }

        printf("Por lo tanto se redireccionará a la ruta por defecto, vía la interfaz %d.\n", num_interfaz_ruta_por_defecto);
    }

    return 0;
}

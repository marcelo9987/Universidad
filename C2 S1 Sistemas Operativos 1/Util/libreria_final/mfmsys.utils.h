#pragma once

#define esperar() \
{                 \
    printf("\nContinuar: ");\
    while(getchar()!='\n');\
}

/**
 * @brief Imprime /proc/PID/maps en un archivo llamado maps<numUso>.mem
 * @param numUso Numero que se pondrá en el nombre del archivo.
 */
void procmap(int numUso);



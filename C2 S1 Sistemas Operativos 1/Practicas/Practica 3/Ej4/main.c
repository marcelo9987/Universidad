/*
 * Programa un proceso con un lazo infinito y que sustituya la acción asociada a CtrlC por la
 * impresión de una frase. Después de recibir 4 veces CtrlC, en las siguientes debe preguntar al
 * usuario si se debe volver a su funcionamiento habitual y hacerlo si la respuesta es afirmativa.
 * Para ello utiliza la opción SIG_DFL. Todas estas funcionalidades deben formar parte de la
 * función que captura la señal.
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void gestor(int);

//int vecesC = 0;

int main()
{
    signal(SIGINT, gestor);
    while (1);
    return 0;
}

void gestor(int senhal)
{
    static int vecesC=0;
    switch (senhal)
    {
        case SIGINT:
            vecesC++;
            
            printf("\nCTRL+C detectado\n");
            
            if (vecesC > 4)
            {
                char s[1000];
                printf("Desea volver al funcionamiento habitual de CTRL+C (s/n): ");
                scanf("%s", s);
                if (strncmp(s,"s",1)==0)
                {
                    printf("La próxima vez que se detecte CTRL+C se finalizará el programa.\n");
                    signal(SIGINT, SIG_DFL);
                }
            }
            break;
    }
}
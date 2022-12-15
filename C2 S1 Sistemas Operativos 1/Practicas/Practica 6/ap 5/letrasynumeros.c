#include <fcntl.h>
//#include <sched.h>
#include <signal.h>
//#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>

int i_senhalesCapturadas1 = 0;
int i_senhalesCapturadas2 = 0;

void signal_handler(int signal)
{
    printf("[ INFO ] | Proceso: %i | He capturado la señal número: %i\n", getpid(), signal);
    switch (signal)
    {
        case SIGUSR1:
            i_senhalesCapturadas1++;
            break;
        case SIGUSR2:
            i_senhalesCapturadas2++;
            break;
    }
}



//bool b_senhalRecibida[] = {false, false, false};




void proceso_padre(pid_t pid_procesoHijo, int fd_archivo, size_t szt_tamanho_archivo_original, size_t szt_tamanho_mitad_archivo_original, char *pc_contenido_archivo_mmap, char *pc_contenidoOriginalArchivo)
{//        unsigned long int li_mitadArchivo = (szt_tamanho_archivo_original - 1) / 2;
//    sleep(1);
    printf("[ DEBUG ] |PADRE| pid: %d\n", getpid());
    
    char *pc_buffer_temporal_padre = (char *) malloc(szt_tamanho_mitad_archivo_original * 3 * sizeof(char));
//        memcpy(pc_buffer_temporal_padre, pc_contenido_archivo_mmap, szt_tamanho_archivo_expandido);
    
    size_t szt_posActualEscritura;
    size_t szt_posActualLectura = 0;
    
    for (szt_posActualEscritura = 0; szt_posActualLectura < szt_tamanho_mitad_archivo_original; szt_posActualLectura++, szt_posActualEscritura++)
    {
        const char c_caracterOriginal = pc_contenidoOriginalArchivo[szt_posActualLectura];
        
        if (c_caracterOriginal >= '0' /*0x30*/ && c_caracterOriginal <= '9'/*0x39*/ )
        {
            //Aquí se ha detectado un número del 0 al 9
            if (0)
            {
                pc_buffer_temporal_padre[szt_posActualEscritura] = '_';
                pc_buffer_temporal_padre[szt_posActualEscritura + 1] = '_';
                pc_buffer_temporal_padre[szt_posActualEscritura + 2] = '_';
            }
            szt_posActualEscritura += 2;
            
        } else if (c_caracterOriginal >= 'A'/*0x41*/ && c_caracterOriginal <= 'Z' /*0x5a*/)
        {
            pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal - 'A' + 'a';
        } else if (c_caracterOriginal >= 'a' /*0x61*/ && c_caracterOriginal <= 'z' /*0x7a*/)
        {
            pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal - 'a' + 'A';
        } else
        {
            pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal;
        }
    }
    
    const size_t szt_bytesEscritos_mitad1 = szt_posActualEscritura;
    
    if (2)
    {
        memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_padre, szt_bytesEscritos_mitad1);
//        memcpy(pc_contenido_archivo_mmap + szt_bytesEscritos_mitad1, pc_contenidoOriginalArchivo + szt_posActualLectura, szt_tamanho_archivo_original - szt_posActualLectura);
//        msync(pc_contenido_archivo_mmap, szt_bytesEscritos_mitad1 + szt_tamanho_archivo_original - szt_posActualLectura, MS_SYNC);
//        msync(pc_contenido_archivo_mmap, szt_bytesEscritos_mitad1, MS_SYNC);
        
        printf("[ INFO ] |PADRE| ENVIANDO SEÑAL 1 AL HIJO.\n");
        if (kill(pid_procesoHijo, SIGUSR1) == -1)
        {
            perror("[ ERROR ] FALLO AL ENVIAR LA SEÑAL");
            exit(-8);
        }

//        printf("[ INFO ] |PADRE| Esperando senhal del hijo\n");
//        pause();
//        printf("[ INFO ] |PADRE| Señal del hijo recibida\n");
    
    }
    
    for (szt_posActualEscritura = 0; szt_posActualLectura < szt_tamanho_archivo_original; szt_posActualLectura++, szt_posActualEscritura++)
    {
        const char c_caracterOriginal = pc_contenidoOriginalArchivo[szt_posActualLectura];
        
        if (c_caracterOriginal >= '0' /*0x30*/ && c_caracterOriginal <= '9'/*0x39*/ )
        {
            //Aquí se ha detectado un número del 0 al 9
            if (1)
            {
                pc_buffer_temporal_padre[szt_posActualEscritura] = '_';
                pc_buffer_temporal_padre[szt_posActualEscritura + 1] = '_';
                pc_buffer_temporal_padre[szt_posActualEscritura + 2] = '_';
            }
            szt_posActualEscritura += 2;
            
        } else if (c_caracterOriginal >= 'A'/*0x41*/ && c_caracterOriginal <= 'Z' /*0x5a*/)
        {
            pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal - 'A' + 'a';
        } else if (c_caracterOriginal >= 'a' /*0x61*/ && c_caracterOriginal <= 'z' /*0x7a*/)
        {
            pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal - 'a' + 'A';
        } else
        {
            pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal;
        }
        
    }
    
    if (2)
    {
        memcpy(pc_contenido_archivo_mmap + szt_bytesEscritos_mitad1, pc_buffer_temporal_padre, szt_posActualEscritura);

//        msync(pc_contenido_archivo_mmap+szt_bytesEscritos_mitad1, (szt_posActualEscritura * sizeof(char)), MS_SYNC);

//        pause();
        printf("[ INFO ] |PADRE| ENVIANDO SEÑAL 2 AL HIJO.\n");
        if (kill(pid_procesoHijo, SIGUSR2) == -1)
        {
            perror("[ ERROR ] FALLO AL ENVIAR LA SEÑAL");
            exit(-8);
        }
        
        free(pc_buffer_temporal_padre);
        free(pc_contenidoOriginalArchivo);
        
        printf("[ INFO ] |PADRE| esperando muerte del hijo.\n");
        waitpid(pid_procesoHijo, NULL, 0);
        printf("[ INFO ] |PADRE| muerte del hijo confirmada\n");
    }
    
    ftruncate(fd_archivo, (szt_bytesEscritos_mitad1 + szt_posActualEscritura) * sizeof(char));
    
    munmap(pc_contenido_archivo_mmap, szt_tamanho_archivo_original * 3);
    close(fd_archivo);
    
    exit(0);
}

void proceso_hijo(/*pid_t pid_procesoPadre, */int fd_archivo, size_t szt_tamanho_archivo_original, size_t szt_tamanho_mitad_archivo_original, char *pc_contenido_archivo_mmap, char *pc_contenidoOriginalArchivo)
{
//    sigset_t senhalHijo;
//    sigaddset(&senhalHijo, SIGUSR1);
//    int sig_recibida;
    
    //  fprintf(stdout, "[ INFO ] | HIJO | Esperando SIGUSR1 del padre... \n");
    printf("[ DEBUG ] |HIJO| pid: %d\n", getpid());
    
    /*int resultado_espera = sigwait(&senhalHijo, &sig_recibida);
    if (resultado_espera == -1)
    {
        perror("Fallo en la pausa\n");
        exit(-20);
    }
    if (sig_recibida == SIGUSR1)
    {
        printf("SIGUSR1 was received\n");
    } else
    {
        printf("sigwait returned with sig: %d\n", sig_recibida);
        exit(-21);
    }*/
    printf("[ INFO ] |HIJO| Esperando senhal del padre\n");
    while (i_senhalesCapturadas1 == 0)
    {
        pause();
    }
    printf("[ INFO ] |HIJO| Señal del padre recibida\n");
    
    
    char *pc_buffer_temporal_hijo = (char *) malloc(szt_tamanho_mitad_archivo_original * 3 * sizeof(char));
    //memcpy(pc_buffer_temporal_hijo, pc_contenido_archivo_mmap, szt_tamanho_archivo_expandido);

/*        if (b_senhalRecibida[0] == true && b_senhalRecibida[1] == false)
        {*/
    size_t szt_posActualEscritura;
    size_t szt_posActualLectura = 0;
    
    for (szt_posActualEscritura = 0; szt_posActualLectura < szt_tamanho_mitad_archivo_original; szt_posActualEscritura++, szt_posActualLectura++)
    {
        /*if (pc_contenido_archivo_mmap[szt_posActualLectura] == szt_tamanho_archivo_original/2)
        {
            memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_hijo, (szt_posActualLectura) * sizeof(char));
            msync(pc_contenido_archivo_mmap, (szt_posActualLectura) * sizeof(char), MS_SYNC);
           // fre.e(pc_buffer_temporal_hijo);
           kill(pid_procesoPadre,SIGUSR2);
        }
           if (pc_contenido_archivo_mmap[szt_posActualLectura] == ' ' && (pc_contenido_archivo_mmap[szt_posActualLectura + 1] == ' ' || pc_contenido_archivo_mmap[szt_posActualLectura - 1] == ' '))
       if (pc_contenidoOriginalArchivo[szt_posActualLectura] - 'A' + 'a' != pc_contenido_archivo_mmap[szt_posActualEscritura] && pc_contenidoOriginalArchivo[szt_posActualLectura] - 'a' + 'A' != pc_contenido_archivo_mmap[szt_posActualEscritura] && pc_contenidoOriginalArchivo[szt_posActualLectura] != pc_contenido_archivo_mmap[szt_posActualEscritura])
       */
        
        if (pc_contenidoOriginalArchivo[szt_posActualLectura] >= '0' && pc_contenidoOriginalArchivo[szt_posActualLectura] <= '9')
        {

//            printf("[ DEBUG ] | HIJO | Cambiando número\n");
            pc_buffer_temporal_hijo[szt_posActualEscritura] = '*';
            pc_buffer_temporal_hijo[szt_posActualEscritura + 1] = '*';
            pc_buffer_temporal_hijo[szt_posActualEscritura + 2] = '*';
//            printf("--> HE insertado : %c,%c,%c\n", pc_buffer_temporal_hijo[szt_posActualEscritura], pc_buffer_temporal_hijo[szt_posActualEscritura + 1], pc_buffer_temporal_hijo[szt_posActualEscritura + 2]);
            
            szt_posActualEscritura += 2;
            
        } else //como el padre ya ha hecho trabajo en las letras, he de leer el caracter a insertar desde el fichero compartido y no desde la copia del archivo original.
        {
//            printf("[ DEBUG ] | HIJO | Letra puesta: %c\n", pc_contenido_archivo_mmap[szt_posActualEscritura]);
            pc_buffer_temporal_hijo[szt_posActualEscritura] = pc_contenido_archivo_mmap[szt_posActualEscritura];
            /*
            printf("[ INFO ] V1: ORIGINAL: %c CAMBIADO %c\n", pc_contenidoOriginalArchivo[szt_posActualLectura], pc_contenido_archivo_mmap[szt_posActualEscritura]);
            pc_buffer_temporal_hijo[szt_posActualEscritura] = '*';
            printf("--> HE insertado : %c\n", pc_buffer_temporal_hijo[szt_posActualEscritura]);
             */
        }
        
    }
    
//    fprintf(stdout, "[ INFO ] |HIJO| Contenido mmap:\n%s\n", pc_contenido_archivo_mmap);
    memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_hijo, szt_posActualEscritura);
//    fprintf(stdout, "[ INFO ] |HIJO| Contenido mmap:\n%s\n", pc_contenido_archivo_mmap);

//    msync(pc_contenido_archivo_mmap, szt_posActualEscritura, MS_SYNC);
    
    printf("[ INFO ] |HIJO| Esperando senhal del padre\n");
    while (i_senhalesCapturadas2 == 0)
    {
        pause();
    }
    printf("[ INFO ] |HIJO| Señal del padre recibida\n");
    
    const size_t szt_bytesEscritos_mitad1 = szt_posActualEscritura;
//    memcpy(pc_buffer_temporal_hijo, pc_contenido_archivo_mmap, szt_tamanho_archivo_expandido);
    
    
    for (szt_posActualEscritura = 0; szt_posActualLectura < szt_tamanho_archivo_original; szt_posActualEscritura++, szt_posActualLectura++)
    {
        
        if (pc_contenidoOriginalArchivo[szt_posActualLectura] >= '0' && pc_contenidoOriginalArchivo[szt_posActualLectura] <= '9')
        {

//            printf("[ DEBUG ] | HIJO | Cambiando número\n");
            pc_buffer_temporal_hijo[szt_posActualEscritura] = '*';
            pc_buffer_temporal_hijo[szt_posActualEscritura + 1] = '*';
            pc_buffer_temporal_hijo[szt_posActualEscritura + 2] = '*';
//            printf("--> HE insertado : %c,%c,%c\n", pc_buffer_temporal_hijo[szt_posActualEscritura], pc_buffer_temporal_hijo[szt_posActualEscritura + 1], pc_buffer_temporal_hijo[szt_posActualEscritura + 2]);
            
            szt_posActualEscritura += 2;
            
        } else //como el padre ya ha hecho trabajo en las letras, he de leer el caracter a insertar desde el fichero compartido y no desde la copia del archivo original.
        {
//            printf("[ DEBUG ] | HIJO | Letra puesta: %c\n", pc_contenido_archivo_mmap[szt_posActualEscritura]);
            pc_buffer_temporal_hijo[szt_posActualEscritura] = pc_contenido_archivo_mmap[szt_bytesEscritos_mitad1+szt_posActualEscritura];
            /*
            printf("[ INFO ] V1: ORIGINAL: %c CAMBIADO %c\n", pc_contenidoOriginalArchivo[szt_posActualLectura], pc_contenido_archivo_mmap[szt_posActualEscritura]);
            pc_buffer_temporal_hijo[szt_posActualEscritura] = '*';
            printf("--> HE insertado : %c\n", pc_buffer_temporal_hijo[szt_posActualEscritura]);
             */
        }
        
    }
    
//    fprintf(stdout, "[ INFO ] |HIJO| Contenido mmap:\n%s\n", pc_contenido_archivo_mmap);
    memcpy(pc_contenido_archivo_mmap + szt_bytesEscritos_mitad1, pc_buffer_temporal_hijo, szt_posActualEscritura);
//    fprintf(stdout, "[ INFO ] |HIJO| Contenido mmap:\n%s\n", pc_contenido_archivo_mmap);
//    memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_hijo, (szt_posActualEscritura) * sizeof(char));
//        msync(pc_contenido_archivo_mmap+szt_bytesEscritos_mitad1, (szt_posActualEscritura * sizeof(char)), MS_SYNC);
    
    free(pc_buffer_temporal_hijo);
    free(pc_contenidoOriginalArchivo);
    
    munmap(pc_contenido_archivo_mmap, szt_tamanho_archivo_original * 3);
    close(fd_archivo);
    
    exit(0);
}

int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        fprintf(stderr, "[ ERROR ] El número de argumentos introducido es distinto al requerido.");
        exit(-1);
    }
    
    
    struct sigaction sa_signal;
    sa_signal.sa_handler = signal_handler;
    /*scigset_t sgs_vacio;
    sigemptyset(&sgs_vacio);
    sa_signal.sa_mask = sgs_vacio;*/
    sa_signal.sa_flags = SA_RESTART;
    
    int signal_success;
    signal_success = sigaction(SIGUSR1, &sa_signal, NULL);
    if (signal_success == -1)
    {
        perror("[ ERROR ] La asignación de la señal no ha tenido éxito.");
        exit(-2);
    }
    signal_success = sigaction(SIGUSR2, &sa_signal, NULL);
    if (signal_success == -1)
    {
        perror("[ ERROR ] La asignación de la señal no ha tenido éxito.");
        exit(-2);
    }
    
    
    int fd_archivo;
    if ((fd_archivo = open(argv[1], O_RDWR)) == -1)
    {
        perror("[ ERROR ] No se ha podido abrir el fd_archivo:");
        exit(-3);
    }
    
    struct stat st_archivo;
    if ((fstat(fd_archivo, &st_archivo)) == -1)
    {
        perror("[ ERROR ] No se ha podido abrir el fd_archivo:");
        exit(-4);
    }
    
    size_t szt_tamanho_archivo_original = st_archivo.st_size;
    if(szt_tamanho_archivo_original==0)
    {
        printf("EL ARCHIVO ES DE LONGITUD 0. Fin del programa.\n");
        exit(0);
    }
    
    size_t szt_tamanho_mitad_archivo_original = (szt_tamanho_archivo_original + 1) / 2;
    printf("[ DEBUG ]El tamaño del archivo original es: %zd\n", szt_tamanho_archivo_original);
    printf("[ DEBUG ]El tamaño de la división es: %zd\n", szt_tamanho_mitad_archivo_original);
    
//    size_t szt_tamanho_mitad_archivo_original = (szt_tamanho_archivo_original) / 2 ;

/*    if (ftruncate(fd_archivo, szt_tamanho_archivo_original * 3) == -1)
    {
        perror("[ ERROR ] No se ha podido modificar el tamaño el archivo:");
        exit(-5);
    }*/
    
    char *pc_contenido_archivo_mmap = NULL;
    pc_contenido_archivo_mmap = mmap(pc_contenido_archivo_mmap, szt_tamanho_archivo_original * 3, PROT_READ | PROT_WRITE, MAP_SHARED, fd_archivo, 0);
    if (pc_contenido_archivo_mmap == MAP_FAILED)
    {
        perror("[ERROR] Fallo al intentar proyectar el fichero en memoria:");
        exit(-6);
    }
    
    char *pc_contenidoOriginalArchivo = (char *) malloc(szt_tamanho_archivo_original * sizeof(char));
    memcpy(pc_contenidoOriginalArchivo, pc_contenido_archivo_mmap, szt_tamanho_archivo_original);
    
    pid_t pid_procesoPadre = getpid();
    pid_t pid_procesoHijo;
    
    pid_procesoHijo = fork();
    if (pid_procesoHijo == -1)  // Fallo en la creación del hijo
    {
        perror("[ERROR] El fork ha fallado en su ejecución:");
        exit(-1);
    } else if (pid_procesoHijo == 0) //Proceso Hijo
    {
        proceso_hijo(/*pid_procesoPadre,*/ fd_archivo, szt_tamanho_archivo_original, szt_tamanho_mitad_archivo_original, pc_contenido_archivo_mmap, pc_contenidoOriginalArchivo);
    } //FIN HIJO
    else
    {
        proceso_padre(pid_procesoHijo, fd_archivo, szt_tamanho_archivo_original, szt_tamanho_mitad_archivo_original, pc_contenido_archivo_mmap, pc_contenidoOriginalArchivo);
        
        
    }// FIN PADRE
}


//int invertirLetra(char *cp_letra)
//{
//    char c_codigoLetra = *cp_letra;
//
//    const int i_tamanhoAbecedario = 0x19;
//
//    if (c_codigoLetra >= 'a' /*0x61*/ && c_codigoLetra <= 'z' /*0x7a*/)
//    {
//        short int si_diferenciaLetra = i_tamanhoAbecedario - (0x7a - c_codigoLetra);
//        *cp_letra = (char) (si_diferenciaLetra + 0x41);
//        return 0;
//    }
//    if (c_codigoLetra >= 'A' /*0x41*/ && c_codigoLetra <= 'Z' /*0x5a*/)
//    {
//        short int si_diferenciaLetra = i_tamanhoAbecedario - (0x5a - c_codigoLetra);
//        *cp_letra = (char) (si_diferenciaLetra + 0x61);
//        return 0;
//    }
//    //todo: ver como incluir letras acentuadas, ñ , etc...
//    /*
//    if (*cp_letra == 'ñ'\*(char) 0xc391 esto es UTF-8, no funciona*\)
//    {
//        *cp_letra = (char) 0xc3b1;
//        return 0;
//    }
//    if (*cp_letra == (char) 0xc3b1)
//    {
//        *cp_letra = (char) 0xc391;
//        return 0;
//    }*/
//    return -1;
//
//}

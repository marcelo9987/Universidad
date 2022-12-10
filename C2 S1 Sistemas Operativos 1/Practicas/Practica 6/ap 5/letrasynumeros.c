#include <fcntl.h>
#include <sched.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wait.h>


void signal_handler(int signal);

//bool b_senhalRecibida[] = {false, false, false};


int main(int argc, char *argv[])
{
    
    if (argc != 2)
    {
        fprintf(stderr, "[ ERROR ] El número de argumentos introducido es distinto al requerido");
        exit(-1);
    }
    
    
    struct sigaction sa_signal;
    sa_signal.sa_handler = signal_handler;
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
    size_t szt_tamanho_archivo_expandido = st_archivo.st_size * 3;
    size_t szt_tamanho_mitad_archivo_original = szt_tamanho_archivo_original / 2;
    
    if (ftruncate(fd_archivo, szt_tamanho_archivo_expandido) == -1)
    {
        perror("[ ERROR ] No se ha podido modificar el tamaño el archivo:");
        exit(-5);
    }
    
    char *pc_contenido_archivo_mmap = NULL;
    pc_contenido_archivo_mmap = mmap(pc_contenido_archivo_mmap, szt_tamanho_archivo_expandido, PROT_READ | PROT_WRITE, MAP_SHARED, fd_archivo, 0);
    if (pc_contenido_archivo_mmap == MAP_FAILED)
    {
        perror("[ERROR] Fallo al intentar proyectar el fichero en memoria:");
        exit(-6);
    }
    
    pid_t pid_procesoPadre = getpid();
    pid_t pid_procesoHijo;
    pid_procesoHijo = fork();
    if (pid_procesoHijo == -1)
    {
        perror("[ERROR] El fork ha fallado en su ejecución:");
        exit(-1);
    } else if (pid_procesoHijo == 0)
    {
        pause();
//        while (!b_senhalRecibida[0])
//        {
//            sched_yield();
//        }
        
        
        char *pc_buffer_temporal_hijo = (char *) malloc(szt_tamanho_archivo_expandido * sizeof(char));
        memcpy(pc_buffer_temporal_hijo, pc_contenido_archivo_mmap, (szt_tamanho_mitad_archivo_original * 3 * sizeof(char)));

//        if (b_senhalRecibida[0] == true && b_senhalRecibida[1] == false)
//        {
        size_t szt_posActualEscritura = 0;
        for (size_t szt_posActualLectura = 0; szt_posActualLectura < szt_tamanho_archivo_original; szt_posActualLectura++, szt_posActualEscritura++)
        {
            /* if (pc_contenido_archivo_mmap[szt_posActualLectura] == szt_tamanho_archivo_original/2)
             {
                 memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_hijo, (szt_posActualLectura) * sizeof(char));
                 msync(pc_contenido_archivo_mmap, (szt_posActualLectura) * sizeof(char), MS_SYNC);
                // free(pc_buffer_temporal_hijo);
                kill(pid_procesoPadre,SIGUSR2);
             }*/
            if (pc_contenido_archivo_mmap[szt_posActualLectura] == ' ' && (pc_contenido_archivo_mmap[szt_posActualLectura + 1] == ' ' || pc_contenido_archivo_mmap[szt_posActualLectura - 1] == ' '))
            {
                pc_buffer_temporal_hijo[szt_posActualLectura] = '*';
                printf("aquí \n");
                // pc_buffer_temporal_hijo[szt_posActualLectura] = pc_contenido_archivo_mmap[szt_posActualLectura];
            } else
            {
                pc_buffer_temporal_hijo[szt_posActualLectura] = pc_contenido_archivo_mmap[szt_posActualLectura];
            }
            memLeida = szt_posActualLectura;
        }
        memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_hijo, (memLeida) * sizeof(char));
        msync(pc_contenido_archivo_mmap, (memLeida) * sizeof(char), MS_SYNC);
        // free(pc_buffer_temporal_hijo);
        kill(pid_procesoPadre, SIGUSR2);
//        }

//        while (!b_senhalRecibida[1])
//        {
//            sched_yield();
//        }
        
        pause();
        
        if (b_senhalRecibida[0] == true && b_senhalRecibida[1] == true)
        {
            int memLeida = 0;
            for (long int li_posActualLectura = (szt_tamanho_archivo_original) / 2; li_posActualLectura < szt_tamanho_archivo_expandido; li_posActualLectura++)
            {
                /* if (pc_contenido_archivo_mmap[li_posActualLectura] == '\0')
                 {
                     memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_hijo, (li_posActualLectura) * sizeof(char));
                     msync(pc_contenido_archivo_mmap, (li_posActualLectura) * sizeof(char), MS_SYNC);
                     free(pc_buffer_temporal_hijo);
                     exit(0);
                 }*/
                if (pc_contenido_archivo_mmap[li_posActualLectura] == ' ' && (pc_contenido_archivo_mmap[li_posActualLectura + 1] == ' '))
                {
                    pc_buffer_temporal_hijo[li_posActualLectura] = '*';
                    // pc_buffer_temporal_hijo[li_posActualLectura] = pc_contenido_archivo_mmap[li_posActualLectura];
                } else
                {
                    pc_buffer_temporal_hijo[li_posActualLectura] = pc_contenido_archivo_mmap[li_posActualLectura];
                }
                
                memLeida = li_posActualLectura;
            }
            memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_hijo, (memLeida) * sizeof(char));
            msync(pc_contenido_archivo_mmap, (memLeida) * sizeof(char), MS_SYNC);
            free(pc_buffer_temporal_hijo);
            exit(0);
        }
        
        
    } else
    {

//        unsigned long int li_mitadArchivo = (szt_tamanho_archivo_original - 1) / 2;
        
        char *pc_buffer_temporal_padre = (char *) malloc(szt_tamanho_archivo_expandido * sizeof(char));
//        memcpy(pc_buffer_temporal_padre, pc_contenido_archivo_mmap, szt_tamanho_archivo_expandido);
        //todo: ¡Libérame!
        size_t szt_posActualEscritura = 0;
        for (size_t szt_posActualLectura = 0; szt_posActualLectura < szt_tamanho_archivo_original; szt_posActualLectura++, szt_posActualEscritura++)
        {
            if (szt_posActualLectura == szt_tamanho_mitad_archivo_original || szt_posActualLectura == szt_tamanho_archivo_original)
            {
                
                memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_padre, (szt_posActualEscritura * sizeof(char)));
                msync(pc_contenido_archivo_mmap, (szt_posActualEscritura * sizeof(char)), MS_SYNC);
                
                
                kill(pid_procesoHijo, SIGUSR1);
                if (szt_posActualLectura == (szt_tamanho_archivo_original) / 2)
                {
                    printf("esperando senhal del hijo\n");
                    while (b_senhalRecibida[2] == false)
                    {}
                    printf("señal del hijo recibida\n");

//                }else if (szt_posActualLectura == (szt_tamanho_archivo_original))
//                {
//                    printf("esperando hijo.\n");
//                    wait(NULL);
//                    printf("muerte del hijo confirmada\n");
//                }
                    memcpy(pc_buffer_temporal_padre, pc_contenido_archivo_mmap, szt_posActualEscritura * sizeof(char));
//                szt_posActualLectura++;
//                szt_posActualEscritura++;
                }
            }
            
            const char c_caracterOriginal = pc_contenido_archivo_mmap[szt_posActualLectura];
            if (c_caracterOriginal >= '0' /*0x30*/ && c_caracterOriginal <= '9'/*0x39*/ )
            {
                //todo: hacer algo(Aquí se ha detectado un número del 0 al 9)
                
                //     long li_posicion_numero = szt_posActualEscritura;
//                for (szt_posActualEscritura; szt_posActualEscritura < li_posicion_numero + 3; szt_posActualEscritura++)
//                {
//                    pc_buffer_temporal_padre[szt_posActualEscritura] = ' ';
//                }
                szt_posActualEscritura += 2;
                
            } else if (c_caracterOriginal >= 'A'/*0x41*/ && c_caracterOriginal <= 'Z' /*0x5a*/)
            {
//                short int si_diferenciaLetra = 'Z'-'A' - (0x5a - c_codigoLetra);
                pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal - 'A' + 'a';/*(char) (si_diferenciaLetra + 0x61);*/
            } else if (c_caracterOriginal >= 'a' /*0x61*/ && c_caracterOriginal <= 'z' /*0x7a*/)
            {
//                invertirLetra(&pc_buffer_temporal_padre[szt_posActualLectura]);
                pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal - 'a' + 'A';
            } else
            {
                pc_buffer_temporal_padre[szt_posActualEscritura] = c_caracterOriginal;
            }
            
            //todo: reajustar el tamaño del fd_archivo al terminar
        }//FIN FOR
        
        if (kill(pid_procesoHijo, SIGUSR1) == -1)
        {
            perror("[ ERROR ]");
            exit(-8);
        }
        printf("esperando hijo.\n");
        waitpid(pid_procesoHijo, NULL, 0);
        printf("muerte del hijo confirmada\n");
        
        for (int li_posActual = 0; li_posActual < szt_tamanho_archivo_original + 24; li_posActual++)
        {
            //printf("Estoy Aquí");
            printf("%c", pc_buffer_temporal_padre[li_posActual]);
            
        }
        
        memcpy(pc_contenido_archivo_mmap, pc_buffer_temporal_padre, (szt_posActualEscritura * sizeof(char)));
        msync(pc_contenido_archivo_mmap, (szt_posActualEscritura * sizeof(char)), MS_SYNC);
        munmap(pc_contenido_archivo_mmap, (szt_posActualEscritura * sizeof(char)));
        ftruncate(fd_archivo, szt_posActualEscritura * sizeof(char));
        exit(0);
    }// FIN PADRE
}//FIN MAIN

void signal_handler(int signal)
{
    printf("[ INFO ] | Proceso: %i | He capturado la señal número: %i\n", getpid(), signal);
//    switch (signal)
//    {
//        case SIGUSR1:
//            if (b_senhalRecibida[0] == false)
//            {
//                b_senhalRecibida[0] = true;
//            } else if (b_senhalRecibida[1] == false)
//            {
//                b_senhalRecibida[1] = true;
//            }
//            //b_senhalRecibida[0] = true;
//            break;
//        case SIGUSR2:
//            b_senhalRecibida[2] = true;
//            break;
//    }
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
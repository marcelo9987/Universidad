#opciones de compilación, muestra todos los warnings (-Wall)
#CC=gcc -DDEBUG -Wall
CC=gcc -Wall
#si incluye una librería estándar, en este caso la matemática (fichero libm.a)
#todas tienen el formato de fichero libNOMBRE.a
#y al incluirla en el compilador se pone -lNOMBRE
#si no hay librerías adicionales, se elimina esta línea
#LIBS = -lm
LIBS =
#carpeta de las cabeceras (si están en la actual, ponemos .)
HEADER_FILES_DIR = .
#opciones de compilación, indica dónde están los archivos .h
INCLUDES = -I $(HEADER_FILES_DIR)
#nombre del ejecutable o archivo de salida
OUTPUT = p0_e5
#ficheros .h. Si hay varios, se precede cada uno con $(HEADER_FILES_DIR)/
LIB_HEADERS = $(HEADER_FILES_DIR)/matriz.h
#FUENTES: todos los archivos .c necesarios
SRCS = main.c asignarElemento.c crearMatriz.c destruirMatriz.c imprimirMatriz.c obtenerElemento.c producto.c suma.c
#ficheros .o: todos los .o con un análogo .c en SRCS
OBJS = $(SRCS:.c=.o)

all: $(OUTPUT)


#REGLA 1: genera el ejecutable, dependencia de los .o
#si no hay librerías adicionales, no existe la variable $(LIBS),
#por lo que se elimina $(LIBS) de la regla siguiente
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)
#REGLA 2: genera los .o cuando es necesario, dependencia de los .c y .h
#sólo genera los .o necesarios por cambios en los .c o .h
#$@ es el nombre del fichero que se genera con la regla (.o)
#$< es el nombre del primer prerrequisito (archivo .c cuyo .o se está generando)
%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)
# REGLA 3: borra el ejecutable (prerrequisito: clean)
cleanall: clean
	rm -f $(OUTPUT)
# REGLA 4: borra los ficheros .o y los de backup (terminan en ~)
clean:
	rm -f *.o *~
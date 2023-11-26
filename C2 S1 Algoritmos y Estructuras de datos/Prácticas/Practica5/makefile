CC=gcc
PARAMS= -Wall -Werror


DIR_ENCAD = HashEncadenamiento/
DIR_RECOLOC = HashRecolocacion/


ARCHIVOS_E = $(DIR_ENCAD)main.c $(DIR_ENCAD)tabla_hash_encadenamiento.c $(DIR_ENCAD)tabla_hash_encadenamiento.h $(DIR_ENCAD)lista.h $(DIR_ENCAD)lista.c
ARCHIVOS_R = $(DIR_RECOLOC)main.c $(DIR_RECOLOC)tabla_hash_recolocacion.c $(DIR_RECOLOC)tabla_hash_recolocacion.h


#VALORES_DE_N_PRIMOS = 10007 11113 12503 14293 16673 20011 22229 25013 28573 33343 40009 49999
#VALORES_DE_N_NO_PRIMOS = 13248 20000 44444

VALORES_DE_N = 10007 11113 12503 14293 16673 20011 22229 25013 28573 33343 40009 49999 13248 20000 44444
VALORES_DE_N_AP3 = 49999

compilar_encadenamiento:

	for VAL in $(VALORES_DE_N); do \
		$(CC) $(PARAMS) -DN=$$VAL $(ARCHIVOS_E) -o $(DIR_ENCAD)exes/encadenamiento$$VAL; \
	done

ejecuta_1_encadenamiento: compilar_encadenamiento

    #                                             tipoFH    K/-
	for VAL in $(VALORES_DE_N); do \
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    2			 -;\
	done

compilar_recolocacion:

	for VAL in $(VALORES_DE_N); do \
		$(CC) $(PARAMS) -DN=$$VAL $(ARCHIVOS_R) -o $(DIR_RECOLOC)exes/recolocacion$$VAL; \
	done


ejecuta_1_recolocacion: compilar_recolocacion

    #                                          tipoFH K/- tipoR a/-
	for VAL in $(VALORES_DE_N); do \
		./$(DIR_RECOLOC)exes/recolocacion$$VAL 2       -     1   1;\
	done


ejecuta_2_encadenamiento: compilar_encadenamiento

    #                                             tipoFH       K/-
	for VAL in $(VALORES_DE_N); do \
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    1            -;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    2            -;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3          500;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3          503;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3         1024;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3     	1031;\
	done


ejecuta_2_4_encadenamiento: compilar_encadenamiento

	#                                             tipoFH    K/-    CLAVE
	for VAL in $(VALORES_DE_N); do \
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    1            -   C;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    2            -   C;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3          500   C;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3          503   C;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3         1024   C;\
		./$(DIR_ENCAD)exes/encadenamiento$$VAL    3     	1031   C;\
	done


ejecuta_2_recolocacion: compilar_recolocacion

    #                                          tipoFH   K/-   tipoR  a/-
	for VAL in $(VALORES_DE_N); do \
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    1      -      1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      500    1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3     1024    1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3     1031    1    1;\
	done


ejecuta_2_4_recolocacion: compilar_recolocacion

	#                                          tipoFH   K/-   tipoR  a/-   CLAVE
	for VAL in $(VALORES_DE_N); do \
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    1      -      1    1   C;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1    1   C;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      500    1    1   C;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1    1   C;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3     1024    1    1   C;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3     1031    1    1   C;\
	done

ejecuta_3: compilar_recolocacion

    #                                          tipoFH   K/-   tipoR  a/-   CLAVE
	for VAL in $(VALORES_DE_N_AP3); do \
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1     1   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1     7   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1    15   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      2     -   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1     1   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1     7   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1    15   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    2     -   A;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1     1   C;\
        ./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1     7   C;\
        ./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1    15   C;\
        ./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      2     -   C;\
        ./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1     1   C;\
        ./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1     7   C;\
        ./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1    15   C;\
        ./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    2     -   C;\
	done


ejecuta_4_adicional: compilar_recolocacion

    #                                          tipoFH   K/-   tipoR  a/-
	for VAL in $(VALORES_DE_N); do \
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    1      -      1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    1      -      1    7;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    1      -      1   15;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1    7;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      1   15;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      500    1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      500    1    7;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      500    1   15;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1    1;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1    7;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    1   15;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    1      -      2    -;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    2      -      2    -;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      500    2    -;\
		./$(DIR_RECOLOC)exes/recolocacion$$VAL    3      503    2    -;\
	done


cleanRecoloc:

	rm $(DIR_RECOLOC)exes/recolocacion*


cleanEncadenamiento:

	rm $(DIR_ENCAD)exes/encadenamiento*


clean: cleanEncadenamiento cleanRecoloc


all: compilar_encadenamiento compilar_recolocacion


ej1: ejecuta_1_encadenamiento ejecuta_1_recolocacion


ej2: ejecuta_2_encadenamiento ejecuta_2_recolocacion ejecuta_2_4_encadenamiento ejecuta_2_4_recolocacion

ej3: ejecuta_3

ej4: ejecuta_2_encadenamiento ejecuta_2_recolocacion ejecuta_4_adicional

all: ejecutable
	del milibreria.o main.o

clean:
	del milibreria.o main.o ejecutable.exe

ejecutable: milibreria.o main.o
	gcc milibreria.o main.o -o ejecutable.exe

milibreria.o: milibreria.c milibreria.h
	gcc -c milibreria.c

main.o: main.c milibreria.h
	gcc -c main.c


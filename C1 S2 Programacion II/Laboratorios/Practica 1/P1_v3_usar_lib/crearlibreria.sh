gcc -static -c -o vectordinamico.o vectordinamico.c

ar -rcsv -o libvectordinamico.a vectordinamico.o
ar -tv libvectordinamico.a

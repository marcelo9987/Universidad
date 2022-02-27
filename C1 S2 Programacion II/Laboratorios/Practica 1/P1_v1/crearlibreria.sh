gcc -static -c -o vectordinamico.o vectordinamico.c

ar -rcs -o libvectordinamico.a vectordinamico.o
ar -t libvectordinamico.a
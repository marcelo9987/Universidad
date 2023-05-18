CC=gcc
CFLAGS=-lrt -Wall -pedantic

EJECUTABLES_FIFO=consumidor_FIFO productor_FIFO
EJECUTABLES_LIFO=consumidor_LIFO productor_LIFO

all: comp_fifo comp_lifo

comp_fifo: $(EJECUTABLES_FIFO)
#	$(CC) $(OPCIONES) consumidor_FIFO.c -o consumidor_FIFO
#	$(CC) $(OPCIONES) productor_FIFO.c  -o productor_FIFO

comp_lifo: $(EJECUTABLES_LIFO)
#	$(CC) $(OPCIONES) consumidor_LIFO.c -o consumidor_LIFO
#	$(CC) $(OPCIONES) productor_LIFO.c  -o productor_LIFO



clean:
	rm -f $(EJECUTABLES_FIFO) $(EJECUTABLES_LIFO)

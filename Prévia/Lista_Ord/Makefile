# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_lista.o lib_listaordenada.o 
     
all: testa_lista.o lib_listaordenada.o
	$(CC) -o testa_lista testa_lista.o lib_listaordenada.o $(LDFLAGS)

lib_listaordenada.o: lib_listaordenada.c
	$(CC) -c $(CFLAGS) lib_listaordenada.c

testa_lista.o: testa_lista.c
	$(CC) -c $(CFLAGS) testa_lista.c

clean:
	rm -f $(objects) testa_lista



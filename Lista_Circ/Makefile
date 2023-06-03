# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = testa_lista.o lib_listacircular.o 
     
all: testa_lista.o lib_listacircular.o
	$(CC) -o testa_lista testa_lista.o lib_listacircular.o $(LDFLAGS)

lib_listacircular.o: lib_listacircular.c
	$(CC) -c $(CFLAGS) lib_listacircular.c

testa_lista.o: testa_lista.c
	$(CC) -c $(CFLAGS) testa_lista.c

clean:
	rm -f $(objects) testa_lista



# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -std=c90 -g  # flags de compilacao
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = main.o libagenda.o 
     
all: main.o libagenda.o
	$(CC) -o main main.o libagenda.o $(LDFLAGS)

libagenda.o: libagenda.c
	$(CC) -c $(CFLAGS) libagenda.c

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects) main
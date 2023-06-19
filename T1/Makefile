# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -g  # flags de compilacao
LDFLAGS = 

CC = gcc

# arquivos-objeto
	objects = agenda.o libagenda.o 
     
all: agenda.o libagenda.o
	$(CC) -o agenda agenda.o libagenda.o $(LDFLAGS)

libagenda.o: libagenda.c
	$(CC) -c $(CFLAGS) libagenda.c

agenda.o: agenda.c
	$(CC) -c $(CFLAGS) agenda.c

clean:
	rm -f $(objects) agenda
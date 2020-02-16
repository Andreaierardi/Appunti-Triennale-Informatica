#definizione variabili
CFLAGS = -Wall -std=c99 -g -o
CC = gcc

#eseguibili
EXECS = scrivi

all: $(EXECS)

scrivi: scrivi.o
	$(CC) $(CFLAGS) -o scrivi scrivi.o

leggi:  leggi.o
	$(CC) $(CFLAGS) -o leggi leggi.o
	
clean:
	rm *.o $(EXECS)
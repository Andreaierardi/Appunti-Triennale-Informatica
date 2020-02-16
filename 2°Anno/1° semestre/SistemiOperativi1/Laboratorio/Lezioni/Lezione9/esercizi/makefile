CFLAGS=-Wall -std=c99 -g -O -lm -pthread 
CC=gcc

# eseguibili da creare
EXECS=sommaQuadrati


all: $(EXECS)


# segnali Real Time
sommaQuadrati: sommaQuadrati.o  xerrors.o
	$(CC) $(CFLAGS) -o sommaQuadrati sommaQuadrati.o xerrors.o 

sommaQuadrati.o: sommaQuadrati.c  xerrors.h
	$(CC) $(CFLAGS) -o sommaQuadrati.o -c sommaQuadrati.c


# xerrors.o
xerrors.o: xerrors.c  xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c


clean:
	rm *.o $(EXECS)


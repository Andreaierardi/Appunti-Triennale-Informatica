# makefile che utilizza regole implicite e variabili
#
# usare 
#    make <nome_eseguibile> 
# per compilare un unico programma, o semplicemente
#    make
# per compilarli tutti 
#
CFLAGS=-Wall -std=c99 -g -O
LDFLAGS=-lpthread
CC=gcc

# eseguibili da creare
EXECS=massimo


all: $(EXECS)


# segnali Real Time
massimo: massimo.o  xerrors.o
	$(CC) $(CFLAGS) -o massimo massimo.o xerrors.o $(LDFLAGS)

massimo.o: massimo.c  xerrors.h
	$(CC) $(CFLAGS) -o massimo.o -c massimo.c


# xerrors.o
xerrors.o: xerrors.c  xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c


clean:
	rm *.o $(EXECS)


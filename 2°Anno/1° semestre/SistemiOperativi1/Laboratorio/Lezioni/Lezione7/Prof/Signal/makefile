# makefile che utilizza regole implicite e variabili
#
# usare 
#    make <nome_eseguibile> 
# per compilare un unico programma, o semplicemente
#    make
# per compilarli tutti 
#
CFLAGS=-Wall -std=c99 -g -O
CC=gcc

# eseguibili da creare
EXECS=segnaliRT


all: $(EXECS)


# segnali Real Time
segnaliRT: segnaliRT.o  xerrors.o
	$(CC) $(CFLAGS) -o segnaliRT segnaliRT.o xerrors.o 

segnaliRT.o: segnaliRT.c  xerrors.h
	$(CC) $(CFLAGS) -o segnaliRT.o -c segnaliRT.c


# xerrors.o
xerrors.o: xerrors.c  xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c


clean:
	rm *.o $(EXECS)


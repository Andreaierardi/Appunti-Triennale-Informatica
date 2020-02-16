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
EXECS=prova24-01-17


all: $(EXECS)


# segnali Real Time
prova24-01-17: prova24-01-17.o  xerrors.o
	$(CC) $(CFLAGS) -o prova24-01-17 prova24-01-17.o xerrors.o 

prova24-01-17.c.o: prova24-01-17.c  xerrors.h
	$(CC) $(CFLAGS) -o prova24-01-17.o -c prova24-01-17..c


# xerrors.o
xerrors.o: xerrors.c  xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c


clean:
	rm *.o $(EXECS)


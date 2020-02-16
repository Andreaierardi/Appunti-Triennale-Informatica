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
EXECS=es1 es2


all: $(EXECS)


# es1
es1: es1.o  xerrors.o
	$(CC) $(CFLAGS) -o es1 es1.o xerrors.o $(LDFLAGS)

es1.o: es1.c  xerrors.h
	$(CC) $(CFLAGS) -o es1.o -c es1.c

# es2
es2: es2.o  xerrors.o
	$(CC) $(CFLAGS) -o es2 es2.o xerrors.o $(LDFLAGS)

es2.o: es2.c  xerrors.h
	$(CC) $(CFLAGS) -o es2.o -c es2.c


# xerrors.o
xerrors.o: xerrors.c  xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c


clean:
	rm *.o $(EXECS)


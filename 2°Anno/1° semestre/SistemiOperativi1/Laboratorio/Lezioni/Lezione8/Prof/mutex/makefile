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
EXECS=somma_primi tabella_primi


all: $(EXECS)


# somma_primi
somma_primi: somma_primi.o  xerrors.o
	$(CC) $(CFLAGS) -o somma_primi somma_primi.o xerrors.o $(LDFLAGS)

somma_primi.o: somma_primi.c  xerrors.h
	$(CC) $(CFLAGS) -o somma_primi.o -c somma_primi.c

# tabella_primi
tabella_primi: tabella_primi.o  xerrors.o
	$(CC) $(CFLAGS) -o tabella_primi tabella_primi.o xerrors.o $(LDFLAGS)

tabella_primi.o: tabella_primi.c  xerrors.h
	$(CC) $(CFLAGS) -o tabella_primi.o -c tabella_primi.c


# xerrors.o
xerrors.o: xerrors.c  xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c


clean:
	rm *.o $(EXECS)


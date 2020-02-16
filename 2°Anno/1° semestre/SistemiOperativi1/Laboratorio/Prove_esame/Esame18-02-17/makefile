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
EXECS=sommeT sommeP


all: $(EXECS)


# sommeT
sommeT: sommeT.o  xerrors.o
	$(CC) $(CFLAGS) -o sommeT sommeT.o xerrors.o $(LDFLAGS)

sommeT.o: sommeT.c  xerrors.h
	$(CC) $(CFLAGS) -o sommeT.o -c sommeT.c

# tabella_primi
sommeP: sommeP.o  xerrors.o
	$(CC) $(CFLAGS) -o sommeP sommeP.o xerrors.o $(LDFLAGS)

sommeP.o: sommeP.c  xerrors.h
	$(CC) $(CFLAGS) -o sommeP.o -c sommeP.c


# xerrors.o
xerrors.o: xerrors.c  xerrors.h
	$(CC) $(CFLAGS) -o xerrors.o -c xerrors.c


clean:
	rm *.o $(EXECS)


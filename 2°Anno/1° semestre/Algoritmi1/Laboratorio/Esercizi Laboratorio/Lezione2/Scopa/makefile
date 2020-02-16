CC=gcc
CFLAGS=-Wall -std=c99 -g -O
# eseguibili da creare
EXECS=main


all: $(EXECS)

main: main.o scopa.o
	$(CC) $(CFLAGS) -o main main.o scopa.o

main.o: main.c scopa.h 
	$(CC) $(CFLAGS) -c main.c -o main.o

clean:
	rm *.o $(EXECS)


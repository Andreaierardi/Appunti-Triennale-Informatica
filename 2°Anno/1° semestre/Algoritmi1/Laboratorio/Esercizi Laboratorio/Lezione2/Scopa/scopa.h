#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
typedef struct elemento {
	int valore;
	char seme; // (C = Cuori; Q = Quadri; F = Fiori; P = Picche)
	} Carta;

typedef struct Nodo_lista {
	Carta *inf;
	struct Nodo_lista *next;
	} Lista;

typedef struct coda {
	Lista *primo;
	Lista *ultimo;
	} Coda;

typedef Lista Pila;


Lista *makeLista() ;
Pila *makePila();
Coda *makeCoda();

int emptyL(Lista *l) ;
int emptyP(Pila *p);
int emptyC(Coda *c);
Carta *primo(Lista *l);
Carta *first(Coda *c);
Lista *creaNodo (Carta *el) ;
Lista *inserisci(Carta *el,Lista *l);
void enqueue(Carta *el, Coda *c);
Lista *rimuovi(Lista *lptr);
Carta *dequeue(Coda *c);
Pila *push(Carta *el,Pila *p);
Carta *top(Pila *p);
Carta *pop(Pila **p);

///METODI
void stampa(Lista *head);
void Mescola(Coda *c);
Coda *creaMazzo(int n);
Carta *creaCarta( char seme,int valore);
Pila *DaiCarte(Coda *c,Pila *p);
Lista *CarteSulTavolo(Coda *c);



//BEATRICE CAVAGNOLO 20014185
//GIULIA TONUSSI 20016373



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


typedef struct elemento {
	int valore;
	char seme; // (C = Cuori; Q = Quadri; F = Fiori; P = Picche)
	} Carta;

typedef struct Nodo_lista {
	Carta inf;
	struct Nodo_lista *next;
	} Lista;

typedef struct coda {
	Lista *primo;
	Lista *ultimo;
	} Coda; 

typedef Lista Pila; 

Lista *makeLista() {
	return NULL;
	}


Pila *makePila(){
	return makeLista();
	}


Coda *makeCoda(){
	Coda *c = (Coda *)malloc (sizeof(Coda));
	c->primo= c->ultimo= NULL;
	return c;
	}

int emptyL(Lista *l) {
return (l == NULL);
}

int emptyP(Pila *p){
return emptyL(p);
}

int emptyC(Coda *c){
return emptyL(c->primo);
}

Carta primo(Lista *l){
if (l != NULL)
 return (l->inf);
}

Carta first(Coda *c){
return primo(c->primo);
}

Lista *creaNodo (Carta el) {
	Lista *l;
	l = (Lista *) malloc(sizeof(Lista));
	if (l != NULL) {
		l->inf = el;
		l->next = NULL;
	}
return l;
}

Lista *inserisci(Carta el,Lista *l){
	Lista *l1;
	l1 = creaNodo (el);
	if (l1 != NULL) {
 		l1->next = l;
 		l= l1;
	}
	return l;
}

void enqueue(Carta el, Coda *c){
	Lista *l;
	l= creaNodo(el);
	if (l != NULL) {
		if(emptyC(c)) {
			c->primo = l;
			c->ultimo = l;
		} else {
			c->ultimo->next = l;
			c->ultimo = l;
		}
	}
}


Lista *rimuovi(Lista *lptr){
	if (lptr != NULL) {
		Lista *l = lptr;
		lptr= lptr->next;
		free(l);
		}
	return lptr;
	}


Carta dequeue(Coda *c){
	Carta el;
	if (!emptyC(c)) {
		el = first(c);
		c->primo= rimuovi(c->primo);
		return el;
	}
}



Pila *push(Carta el,Pila *p){
	return inserisci(el, p);
	}

Carta top(Pila *p){
	if (!emptyP(p))
		return primo(p);
	}

Carta pop(Pila **p){
	Carta el;
	if (!emptyP(*p)) {
		el= primo(*p);
		*p= rimuovi(*p);
		return el;
	}
}

Lista *ennesimo(int n, Coda *m){
	 int pos = 1;
	 Lista *p = m->primo;
	 while((pos<n) && (p!=NULL)){
		p = p->next;
		pos++;
		}
	return p;
	}



void mescolaMazzo(Coda mazzo){
	srand (time(NULL));
	for(int i=0; i<40; i++){
		int a = rand() % 40;
		int b = rand() % 40;
		Lista *cartaA= ennesimo(a,&mazzo);
		Lista *cartaB= ennesimo(b,&mazzo);
		Carta tmp;
		tmp.valore = cartaA->inf.valore;
		tmp.seme = cartaA->inf.seme;
		cartaA->inf.valore = cartaB->inf.valore;
		cartaA->inf.seme = cartaB->inf.seme;
		cartaB->inf.valore = tmp.valore;
		cartaB->inf.seme = tmp.seme;
	}
}

void stampa(Lista *head){
    Lista *p=head;
    while(p!=NULL){
        printf("%d%c ", p->inf.valore, p->inf.seme);
        p=p->next;
    }
	puts("");
}





int main(){

	//INIZIALIZZO OGNI ELEMENTO CHE MI SERVE PER GIOCARE

	Pila *giocatore1= makePila();
	Pila *giocatore2= makePila();
	Pila *giocatore3= makePila();
	Pila *giocatore4= makePila();
	Coda *mazzo = makeCoda();
	Lista *tavolo = makeLista();
	
	Carta carta1;
	//RIEMPO IL MAZZO
	for(int i=0; i<4; i++){
		for(int j=1; j<=10; j++){
			if(i==0){
				carta1.seme = 'C';
				carta1.valore = j;
			}
			if(i==1){
				carta1.seme = 'Q';
				carta1.valore = j;
			}
			if(i==2){
				carta1.seme = 'F';
				carta1.valore = j;
			}
			if(i==3){
				carta1.seme = 'P';
				carta1.valore = j;
			}
			enqueue(carta1, mazzo);
		}
	}
	puts("\nMAZZO NORMALE");
	stampa(mazzo->primo);
	
	//MESCOLO IL MAZZO
	mescolaMazzo(*mazzo);
	puts("--------------------");
	puts("MAZZO MESCOLATO");
	stampa(mazzo->primo);

	//PRIMA MANO
	puts("\n------PRIMA MANO------");
	for(int i=0;i<3;i++){
		giocatore1 = push(dequeue(mazzo), giocatore1);
		giocatore2 = push(dequeue(mazzo), giocatore2);
		giocatore3 = push(dequeue(mazzo), giocatore3);
		giocatore4 = push(dequeue(mazzo), giocatore4);
	}
	puts("GIOCATORE 1");
	stampa(giocatore1);
	puts("GIOCATORE 2");
	stampa(giocatore2);
	puts("GIOCATORE 3");
	stampa(giocatore3);
	puts("GIOCATORE 4");
	stampa(giocatore4);

	for(int i=0; i<4; i++)
		tavolo = inserisci(dequeue(mazzo), tavolo);
		
	puts("TAVOLO");
	stampa(tavolo);

	//FASE DI GIOCO

	puts("\n------FASE DI GIOCO------");


	Carta c1;
	while(mazzo->primo!=NULL){
		
		if(giocatore1==NULL){
			for(int i=0;i<3;i++){
				giocatore1 = push(dequeue(mazzo), giocatore1);
				giocatore2 = push(dequeue(mazzo), giocatore2);
				giocatore3 = push(dequeue(mazzo), giocatore3);
				giocatore4 = push(dequeue(mazzo), giocatore4);
			}
		}
		for(int i=0; i<3; i++){
			puts("----TURNO SUCCESSIVO----");
			puts("GIOCATORE 1");
			stampa(giocatore1);
			puts("GIOCATORE 2");
			stampa(giocatore2);
			puts("GIOCATORE 3");
			stampa(giocatore3);
			puts("GIOCATORE 4");
			stampa(giocatore4);
			puts("TAVOLO");
			stampa(tavolo);

			tavolo = inserisci(pop(&giocatore1), tavolo);
			c1 = primo(tavolo);
			printf("\n   Giocatore1 gioca %d%c\n", c1.valore, c1.seme);
			tavolo = inserisci(pop(&giocatore2), tavolo);
			c1 = primo(tavolo);
			printf("   Giocatore2 gioca %d%c\n", c1.valore, c1.seme);
			tavolo = inserisci(pop(&giocatore3), tavolo);
			c1 = primo(tavolo);
			printf("   Giocatore3 gioca %d%c\n", c1.valore, c1.seme);
			tavolo = inserisci(pop(&giocatore4), tavolo);
			c1 = primo(tavolo);
			printf("   Giocatore4 gioca %d%c\n", c1.valore, c1.seme);
			puts("");
			}
		
		}

	puts("---SITUAZIONE FINALE DEL GIOCO, I GIOCATORI NON HANNO PIU CARTE, IL TAVOLO LE HA TUTTE----\n");
	puts("GIOCATORE 1");
	stampa(giocatore1);
	puts("GIOCATORE 2");
	stampa(giocatore2);
	puts("GIOCATORE 3");
	stampa(giocatore3);
	puts("GIOCATORE 4");
	stampa(giocatore4);
	puts("TAVOLO");
	stampa(tavolo);
	puts("\n-----FINE DEL GIOCO-----");

	return 0;
}

	
	
	
		
































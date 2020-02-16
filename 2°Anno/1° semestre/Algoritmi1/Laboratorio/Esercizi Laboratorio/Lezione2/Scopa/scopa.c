#include "scopa.h"
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

Carta *primo(Lista *l){
 if (l != NULL)
 return (l->inf);
}

Carta *first(Coda *c){
return primo(c->primo);
}

Lista *creaNodo (Carta *el) {
	Lista *l;
	l = (Lista *) malloc(sizeof(Lista));
	if (l != NULL) {
		l->inf = el;
		l->next = NULL;
	}
return l;
}

Lista *inserisci(Carta *el,Lista *l){
	Lista *l1;
	l1 = creaNodo (el);
	if (l1 != NULL) {
 		l1->next = l;
 		l= l1;
	}
	return l;
}

void enqueue(Carta *el, Coda *c){
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


Carta *dequeue(Coda *c){
	Carta *el;
	if (!emptyC(c)) {
		el = first(c);
		c->primo= rimuovi(c->primo);
		return el;
	}
}



Pila *push(Carta *el,Pila *p){
	return inserisci(el, p);
	}

Carta *top(Pila *p){
	if (!emptyP(p))
		return primo(p);
	}

Carta *pop(Pila **p){
	Carta *el;
	if (!emptyP(*p)) {
		el= primo(*p);
		*p= rimuovi(*p);
		return el;
	}
}

///METODI ESERCIZIO
void stampa(Lista *head){
    Lista *p=head;
    while(p!=NULL){
        printf("%d%c ", p->inf->valore, p->inf->seme);
        p=p->next;
    }
	puts("");
}
Carta *creaCarta( char seme,int valore)
{
    Carta *carta= malloc(sizeof(Carta));
    carta->seme = seme;
    carta->valore= valore;
    return carta;
}
Coda *creaMazzo(int n)
{
    Coda *mazzo= makeCoda();
    char semi[4] = {'P','Q','C','F'};
     for (int j= 0; j<4; j++)
            for (int i = 1 ; i<=10;i++)
            {
                enqueue(creaCarta(semi[j], i),mazzo);
            }
    return mazzo;
}

void Mescola(Coda *c){
    srand(time(NULL));
    Lista *c2= c->primo;


    Lista *p1= NULL;
    Lista *p2= NULL;
    for (int j = 0 ; j<40 ; j++)
    {

        Carta *tmp=NULL;
        int i=rand()%40;
        int h=rand()%40;
       for(int z=0;z<40;z++)
        {
            if (i==z)
                    p1=c2;
            else if(h==z)
                    p2=c2;
            else
                c2 = c2->next;
      }
    tmp= p1->inf;
    p1->inf= p2->inf;
    p2->inf= tmp;
    c2= c->primo;

    }


}

Pila *DaiCarte(Coda *c, Pila *p)
{
    p=push(dequeue(c),p);
    return p;

}

Lista *CarteSulTavolo(Coda *c)
{
    Lista *tmp=makeLista();
    for (int i = 0 ; i<4 ; i++)
    {
        tmp= inserisci(dequeue(c),tmp);
    }
    return tmp;
}

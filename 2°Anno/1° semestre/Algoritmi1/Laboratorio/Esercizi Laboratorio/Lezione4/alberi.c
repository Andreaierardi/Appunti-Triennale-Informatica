#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
///Andrea Ierardi Matricola: 20018785
///Edoardo Favorido Matricola: 20018971
///Marco Rizzi Matricola: 20019238

///Funzioni per la creazione di nodi
typedef int Elemento;

//Struttura nodo di un albero con campi elemento, puntatore a ramo sinistro e puntatore a ramo destro
typedef struct Nodo
{
    Elemento  inf;
    struct Nodo *sinistro;
    struct Nodo *destro;
} Nodo;

//Creazione di nodo utilizzando la malloc quindi occupazione di memoria
Nodo *makeNodo (int inf) //Passo il dato da inserire nel nodo
{
    Nodo *al = (Nodo *) malloc(sizeof(Nodo)); //Alloco Nodo memoria per la creazione
    if (al != NULL) //Se allocazione avviene con successo allora ramo destro e sinistro vengono posti a null
    {
        al -> destro = al -> sinistro = NULL; 
        al -> inf = inf; //Viene assegnato l'intero inf al campo inf del nodo
    }
    return al; //Ritorno il nodo appena creato

}
///Funzioni per la creazione di alberi

Nodo *makeTree(int n) //Creazione di un albero passando il numero di nodi da creare
{
    if (n >0) 
    {
        int numFigliSX= (n-1)/2; //divido i nodi tra i figli destro e sinitro "quasi" equamente
        int numFigliDX= (n-1)-numFigliSX; 
        Nodo *nuovoNodo = makeNodo(rand()%10); //Assegno un numero casuale da passare come parametro quindi per generare un numero casuale da inserire nel nodo (in modulo 10 quindi che va da 0 a 10)
        nuovoNodo->sinistro =makeTree(numFigliSX); //Richiamo la funzione maketree sul ramo sinistro per la generazione dei nodi di ogni figlio
        nuovoNodo->destro = makeTree(numFigliDX); //Idem per il figlio destro
        return nuovoNodo; //ritorno la radice dell'albero

    }
    else return NULL; //Se passo un valore minore o uguale a zero la radice ritornata è NULL
}
///Funzioni per la creazione di liste e pile
typedef struct Nodo_lista  //Struttura di un nodo di una lista
{ 
    Nodo *inf; //Passo il riferimento al nodo
    struct Nodo_lista *next; //Puntatore a nodo successivo
} Lista;

typedef Lista Pila; //Lista e Pila hanno la stessa implementazione


Lista *makeLista() //Metodo per la creazione di una lista vuota
{
    return NULL;
}


Pila *makePila() //Metodo per la creazione di un pila vuota richiamando il makeLista()
{
    return makeLista();
}


int emptyL(Lista *l) //Verifica che la lista sia vuota
{
    return (l == NULL); //Se lista vuota allora ritorna uno --> in C in booleani vengono visti come numeri
}

int emptyP(Pila *p) //Idem per la pila
{
    return emptyL(p);
}

Nodo *primo(Lista *l) //ritorna il primo nodo in lista
{
    if (l != NULL)
        return (l->inf);
    else return NULL;
}

Lista *creaNodo (Nodo *el) //Creazione di un nodo di una lista passando el come elemento da inserire
{
    Lista *l;
    l = (Lista *) malloc(sizeof(Lista)); //Allocazione di una lista l
    if (l != NULL) 
    {
        l->inf = el; //Riempo il campo inf con il valore di el
        l->next = NULL;
    }
    return l;
}

Lista *inserisci(Nodo *el,Lista *l) //Inserimento di un nodo in lista
{
    Lista *l1;
    l1 = creaNodo (el); //Per inserire devo creare nuovo nodo
    if (l1 != NULL)
    {
        l1->next = l; 
        l= l1;
    }
    return l;
}

//Metodo per la rimozione di un nodo in lista
Lista *rimuovi(Lista *lptr)
{
    if (lptr != NULL) 
    {
        Lista *l = lptr;  //In pratica assegno una lista all'elemento
        lptr= lptr->next; //Assegno l'elemento successivo come testa
	//E infine cancello elemento con la free
        free(l); //Eliminazione di un nodo in lista --> si può anche trovare sulle slide di fondamenti di programmazione 2
    }
    return lptr; //ritorno la testa della nuova lsita
}
//Funzione per il push di un nodo in una pila --> che equivale a inserirlo in una lista
Pila *push(Nodo *el,Pila *p)
{
    return inserisci(el, p);
}
//Ritorno il nodo al top di una pila --> equivale a ritornare il primo elemento di una lista
Nodo *top(Pila *p)
{
    if (!emptyP(p))
        return primo(p);
    else return 0;
}
//Eliminazione di un nodo in una pila--> equivale a eleminare il nodo di una lista
Nodo *pop(Pila **p)
{
    Nodo *el;
    if (!emptyP(*p))
    {
        el= primo(*p);
        *p= rimuovi(*p);
        return el;
    }
    else return 0;
}


///Richiami di funzione
int max (int x ,int y);
int altezza(Nodo *r);
int foglie (Nodo *r);
int fogliePari (Nodo *r);
int contaNodi(Nodo *r);
bool cerca(Nodo *r,int x);
int sommaNodi_ric(Nodo *r);
int sommaNodi_ite(Nodo *r);

///Funzione main
int main()
{

    Nodo *Albero = makeTree(10); //Creazione di un albero di 10 nodi --> con valore interno casuale 
///1)
    int h = altezza(Albero); //Richiamo la funzione altezza che ritorna l'altezza dell'albero appena creato
    printf("Altezza : %d\n",h); //Stampo l'altezza appena trovata

///2)
    int foglia= foglie(Albero); //Funzione foglie ritorna il numero di foglie dell'albero e stampo il valore 
    printf("Numero foglie: %d\n",foglia);
///2a)
    int fogliaPari=fogliePari(Albero); //Funzione fogliePari ritorna il numero di foglie con chiave pari nell'albero e stampo
    printf("Numero foglie pari: %d\n",fogliaPari);

///3)
    int numNodi = contaNodi(Albero); //Funzione della conta dei nodi dell'albero e stampo il numero
    printf("Numero nodi dell'albero: %d\n",numNodi);

///4)
    int x = 2; //Per esempio vorremmo cercare il nodo con chiave= 2 nell'albero
    if(cerca(Albero, x)) printf ("Elemento: %d trovato!\n", x); //Funzione per la ricerca di un elemento x nell'albero
    else printf("Elemento %d non trovato! :( ",x);  //Se non trovo l'elemtno stampo che non l'ho trovato

///5a)
    int sommaRic = sommaNodi_ric(Albero);//Somma dei nodi in ricorsione di ogni chiave dei nodi dell'albero
    printf("Somma ricorsiva nodi dell'albero: %d\n",sommaRic);
 
///5b)
    int sommaIte = sommaNodi_ite(Albero); //Somma dei nodi in iterazione di ogni chiave dei nodi dell'albero
    printf("Somma iterativa nodi dell'albero: %d\n",sommaIte);

    return 0;
}

///1. Calcolare l’altezza di un albero binario
int max (int x ,int y) //Semplice funzione max che permette di trovare il massimo tra due numeri
{
    if (x>=y) return x; //Se primo maggiore del secondo allora ritorno primo 
    else return y; //Altrimenti ritorno il secondo 
}
///Questa funzione è stata fatta anche nel corso di algoritmi sperimentazioni
int altezza(Nodo *r) 
{
    if (r==NULL) return -1; //Se l'albero ha nodo null allora ritorno -1
    int sx = altezza(r->sinistro); //Scavo in ricorsione i nodi del ramo a sinistra
    int dx = altezza (r->destro); //Scavo in ricorsione i nodi del ramo a destra
    return (1+max(sx,dx)); //Ritorno il massimo poichè l'altezza dell'albero totale è data dal massimo tra l'altezza del ramo sinistro e tra l'altezza ramo destro dell'albero 
}
///2. Calcolare il numero di foglie di un albero binario.
int foglie (Nodo *r) 
{
    if (r == NULL) return 0; //Se sono in una foglia e scorro al ramo destro e sinitro di una foglia scopro che sono uguale a NULL --> quindi non devono essere contati
    if ((r->sinistro==NULL) && (r->destro==NULL)) return 1; //Se trovo che il ramo destro e sinistro di un nodo sono a NULL mi trovo in un nodo foglia
    int sx = foglie(r->sinistro); //Se ramo destro e sinistro != NULL vuol dire che non sono in una foglia e devo scorrere nel ramo successivo
    int dx = foglie(r->destro);
    return (sx+dx); //Ritorno infinte la somma del numero di foglie nel ramo destro e sinistro che partono dalla radice
}
///2a. Variante: calcolare il numero di foglie con chiave pari di un albero binario.
int fogliePari (Nodo *r) //Stesso di sopra con controllo che la chiave della foglia sia pari
{
    if (r == NULL) return 0;
    if ((r->sinistro==NULL) && (r->destro==NULL)&&(r->inf%2==0)) return 1;
    int sx = fogliePari(r->sinistro);
    int dx = fogliePari(r->destro);
    return (sx+dx);
}

///3. Calcolare il numero di nodi di un albero binario.
int contaNodi(Nodo *r)
{
    if(r==NULL) return 0; //Caso base
	//Scorro i nodi  sia a destra che a sinistra e ad ogni richiamo ricorsivo vi sarà la somma tra i nodi dei rami sinistro e destro di ogni nodo passato in esame
    int sin=contaNodi(r->sinistro);
    int des=contaNodi(r->destro);
    return sin+des+1;
}

///4. Cercare un elemento x tra le chiavi di un albero binario.

bool cerca(Nodo *r,int x) //Funzione cerca di una chiave x nell'albero
{
    if (r == NULL) return false; //Se arrivo ad una foglia ritorno false perchè non ho trovato la chiave che cercavo
    if (r->inf == x) return true; //Se trovo che il nodo contiene la chiave x interrompo la funzione e ritorno true
    if (cerca(r->sinistro,x))return true; //Continuo a scorrere nel ramo sinistro ricorsivamente--> se verrà confermata una delle cerca (r->inf == x) allora verrà ritornato il valore true
    if (cerca(r->destro,x))return true; //Stesso per il ramo destro di ogni nodo
    return false; //Se nessuna delle cerca in modo ricorsivo ha trovato la chiave che cercavamo allora viene ritornato false --> quindi la chiave non è stata trovata 

}

///5a. Sommare le chiavi di un albero binario - Ricorsivamente

int sommaNodi_ric(Nodo *r)
{
    if(r==NULL)return 0; //Scorro e se vado oltre ad una voglia non vi è una chiave quindi non la conto --> caso base
    return (sommaNodi_ric(r->sinistro)+sommaNodi_ric(r->destro)+r->inf); //somma tra il risultato di ogni chiamata ricorsiva sul ramo destro + chiamata ricorsiva ramo sinistro + la chiave
	//Alla fine avremo la somma di tutti i nodi dell'albero

}

///5b. Sommare le chiavi di un albero binario - Iterativamente 
///Per la somma dei nodi iterativa c'è bisogno di una Pila per tenere traccia delle chiavi
int sommaNodi_ite(Nodo *r)
{
    int somma=0; //variabile d'appoggio somma 
    Pila *p=makePila(); //Creo una pila vuota
    Nodo *n=NULL; //e creo un albero nullo (Un albero è un puntatore ad un nodo)
    if(r!=NULL) //Se la radice non è nulla
    {
        p = push(r,p); //Carico sulla pila il nodo r
        while(!emptyP(p)) //Se la pila non è vuota "consumo" il nodo appena caricato
        {
            n=pop(&p); //n avrà il valore della testa della Pila
            if(n!=NULL) //Se è diverso da null
            {

                somma=somma+(n->inf); //Sommo il valore della chiave alla variabile di appoggio
                p = push(n->destro,p); //carico sulla pila il ramo destro e sinistro dell'albero e continuo a ciclare su quest'ultimi
                p = push(n->sinistro,p);

            }
        }
    }
    return somma; //Appena finita la visita dell'albero ritorno il valore della somma 
}


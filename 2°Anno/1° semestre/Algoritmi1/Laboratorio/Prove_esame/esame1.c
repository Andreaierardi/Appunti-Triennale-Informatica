#include <stdlib.h>
#include <stdio.h>
//Strutture
struct nodo
{
    int inforadice; //Valore del nodo
    struct nodo *sinistro,*destro; //Link del nodo ai due figli
};

struct nodo *radice;

struct nodo *inserisci( struct nodo *radice, int e ) //Funzione di inserimento del nodo
{
    struct nodo *aux; //Nodo ausiliario
    if (radice == NULL) //Se passata radice vuota
    {
        aux = malloc(sizeof(struct nodo)); //alloco memoria di un nodo
        if (aux) //Se allocazione avviene con successo
        {
            aux->inforadice = e; //Inserisco il valore nel nodo
            aux->destro = aux->sinistro = NULL; //figlio destro e sinistro sono nulli
            return aux; //Ritorno la costruzione del nodo
        }
        else
        {
            printf("Memoria non allocata\n");
        }
    }

    else if (e < radice->inforadice)
        radice->sinistro = inserisci(radice->sinistro,e);
    else if(e> radice->inforadice)
        radice->destro = inserisci (radice->destro,e);

    return radice; //Infine ritorno la radice
}

//Richiami di funzione
void printDispari (struct nodo *radice );
int cercaValore(struct nodo *radice, int V);
struct nodo *ricercaABR(struct nodo *radice, int V);
void PrecESucc(struct nodo *radice, int V, int *prec, int *succ);
//Main
int main ()
{
    //Costruzione dell'albero inserendo tutti i nodi
    struct nodo *root= NULL;
    root = inserisci (root, 50);
    root = inserisci (root, 72);
    root = inserisci (root, 76);
    root = inserisci (root, 54);
    root = inserisci (root, 67);
    root = inserisci (root, 17);
    root = inserisci (root, 12);
    root = inserisci (root, 23);
    root = inserisci (root, 9);
    root = inserisci (root, 19);
    root = inserisci (root, 14);

    printf("Stampa dei numeri dispari in ordine decrescente: ");
    printDispari(root);

    int val = 994;
    int e = cercaValore(root, val);
    if (e== 1) printf("\nValore %d-> trovato è foglia\n",val);
    else if (e==0) printf("\nValore %d -> trovato e non è foglia\n",val);
    else
        printf("\nValore %d ->non trovato \n",val);


    val = 14;
    e = cercaValore(root, val);
    if (e== 1) printf("Valore %d -> trovato è foglia\n",val);
    else if (e==0) printf("Valore %d -> trovato e non è foglia\n",val);
    else
        printf("Valore %d ->non trovato \n",val);


    val = 50;
    e = cercaValore(root, val);
    if (e== 1) printf("Valore %d -> trovato è foglia\n",val);
    else if (e==0) printf("Valore %d -> trovato e non è foglia\n",val);
    else
        printf("Valore %d ->non trovato \n",val);

    val= 23;
    int precedente, successivo;
    PrecESucc(root,val,&precedente,&successivo);
    printf("Precedente e successivo di %d-> %d - %d\n",val,precedente,successivo);

    return 0;
}

//Funzioni utili
//Funzione che ritorna il nodo se trova che il valore è uguale a V
struct nodo *ricercaABR(struct nodo *radice, int V)
{
    if (radice == NULL ) return NULL;
    if (radice ->inforadice == V) return radice;
    if (radice->inforadice > V) return ricercaABR(radice->sinistro,V);
    return ricercaABR(radice->destro, V);

}

//1) Data in ingresso la root di un ABR, stampare i valori
void printDispari (struct nodo *radice )
{
    if (radice != NULL) //Scorro albero
    {
        printDispari(radice->destro);
        if (radice->inforadice%2!= 0)
            printf("%d ",radice->inforadice);
        printDispari(radice->sinistro);
    }

}
//2) Data in ingresso la root di un ABR e un valore intero V, restituire (se esistono) il predecessore e il successore di V.
int predecessore(struct nodo *radice)
{
    if (radice->sinistro==NULL) return -1;
    struct nodo *tmp = radice->sinistro;
    while (tmp->destro != NULL)
        tmp = tmp->destro;
    return tmp->inforadice;

}
int successore(struct nodo *radice)
{
    if (radice->destro==NULL) return -1;
    struct nodo *tmp = radice->destro;
    while (tmp->sinistro != NULL)
        tmp = tmp->sinistro;
    return tmp->inforadice;

}

void PrecESucc(struct nodo *radice, int V, int *prec, int *succ)
{
    struct nodo *tmp = ricercaABR(radice, V);
    if (tmp ==NULL)
        *prec = *succ = -1;
    else
    {
        *prec = predecessore(tmp);
        *succ= successore(tmp);
    }
}
//Esercizio3
int cercaValore(struct nodo *radice, int V)
{
    struct nodo *tmp = ricercaABR(radice, V);
    if(tmp == NULL) return -1;
    if (tmp->destro == NULL && tmp->sinistro==NULL) return 1;
    return 0 ;
}

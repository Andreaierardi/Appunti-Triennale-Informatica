#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

#define dim_array 100   //definisco dim_array=200

bool primo(int n);
void visualizza_array(int a[], int n);
int conta(int a[], int n, int val);


// legge n da riga di comando e costruisce
// array con i pirmi <= n
int main(int argc, char *argv[])
{
    if(argc!=2) {
        printf("Uso: %s numero\n",argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    ///int a[dim_array];


    int b[dim_array], c[n];

    int *a;
    a=(int *)malloc(n*sizeof(int));
    assert(a!=NULL);


    //===================
    //int a[dim_array];
                          /// il puntatore occupa 8 byte per le macchine con più di 4 GB di RAM
    int *a;              // a non è una variabile intera ma dico che è una variabile dove posso metterci un indirizzo dove inizia un array di interi(E' UN PUNTATORE AD UN INTERO)
    int capacita = 100;

    a = (int *) malloc(100*sizeof(int));  ///FUNZIONE MALLOC--> gli passo come argomento un certo numero di byte e cerca nel sistema un blocco libero da assegnare al programma
                                          //100 * dimensione degli interi(4byte) --> 400 byte   (se scelgo posizione troppo grande resistuisce il valore NULL
    if (a==NULL){
        puts("Meromria insufficiente");    //quindi se mi restituisce il valore NULL scrive puts--> (come printf perchè mette automatico \n ma non posso assegnare variabile %d , %s ecc..)
        return 1;                          ///int * poichè la malloc restituisce un puntatore generico e lo trasforma in un puntatore intero e lo assegna ad "a"
    }                                      // QUESTO E' UN ARRAY DINAMICO CHE QUINDI NON DEVO PER FORZA UTILIZZARE TUTTE LE POSIZIONI

    // se  a non mi serve più
    ///free(a);                            ///il blocco di memoria a cui punta a non mi serve più e la rende nuovamente disponibile e perde ogni valore(Non posso più recuperarli)

    // se mi serve di dimensione diversa
    ///a = (int *) realloc(a,200*sizeof(int));   /// se trova spazio di altri 400 byte li aggiunge alla posizione di prima. Se non trovo 400 byte dopo rialloca tutti e 800 byte
                                                 /// in un'altra porzione di memoria e li copia e incolla. Il problema è che è più lenta come operazione.



    int messi=0;
    for(int i=2;i<=n;i++) {
        if(primo(i)) {
            if(messi == capacita) {          // se messi arriva alla capacità massima ingrandisco array
                puts("Ingrandisco");
                capacita += 100;
                a = (int *) realloc(a,capacita*sizeof(int));
                if (a == NULL){
                    printf("Memoria Insuf. cambia computer\n");
                    return 2;
                }
            }
            assert(messi<capacita);

            a[messi]=i;
            messi += 1; //incremento messi per aumentare il numero di oggetti
        }
    }
    printf("Inseriti %d primi, l'ultimo e' %d\n",messi, a[messi-1]);
    visualizza_array(a,messi);
    printf("Il valore 19 compare %d volte\n",conta(a,messi,19));


    return 0;
}


// funzione che conta quante volte il valore val compare dentro
// il vettore a[] di lunghezza n
int conta(int a[], int n, int val)
{
    int volte=0; //tiene conto di quante volte ho visto val
    for(int i=0;i<n;i++) {
        if(a[i]==val) {
          volte += 1;
        }
    }
    return volte;
}


// visualizza il contenuto dell'array a[]
void visualizza_array(int a[], int n)
{   int x[10];
    printf("--- array di %d elementi ----\n",n);
    for(int i=0;i<n;i++)
        printf("%d\n",a[i]);
    printf("--------- fine -----------------\n");
    // return;
}


// verifica se l'intero n e' primo
// confrontare con la versione Python
bool primo(int n) {
    if(n<2) {
        return false;
    }
    else if(n%2==0) { ///n pari
        if(n==2)
            return true;
        else
            return false;
    }
    else {   /// n dispari >= 3
        assert(n%2!=0);
        for(int i=3;i<n;i+=2) {
            if(n%i==0) return false;
            if(i*i>n)
              break;
        }
        return true;
    }
}






/* PUNTATORI

variabile del codice a indirizzo nella memoria. Ogni cella di memoria contiene un byte. Ognuna di queste celle per essere identificata si utilizza un numero progressivo(cella0, cella 1, cella 2...cella n).
In un puntatore si scrive un intero (ex 1200) che punta a quella posizione nella memoria.
Al momento di creare un array di 100 elementi, abbiamo 400 byte poichè ogni posizione dell'intero occupa 4 byte. Il sistema cerca un blocco di 400 byte liberi e assegna l'array.
I primi 4 byte fanno array[0], i secondi 4 byte fanno array[1] ecc...
Dalla main alla funzione visualizza viene passato 1200 ossia la posizione in memoria di quell'array. Ciò che passa è il puntatore che punta a quell'array.
La funzione visualizza array riceve la posizione 1200 e il valore messi che determina quante posizioni nell'array sono realmente occupate.
La funzione visualizza array non sa la capacità massima di a[] quindi oltre a passare l'array devo anche passare la dimensione(in python non era così).
Passare l'array significa dire il valore di partenza dell'array.

a[100] --> creo un array di dimensione fissa.

Posso definire array in un metodo diverso in modo tale che non sia di dimentsione fissa

--------------------
RIGA24

Sono funzioni definite pericolose poichè int *a non è un array ma dico che sto per crearlo. Quindi se ritorno a mi da errori anomali.
In questo modo posso richiedere grossi pezzi di memoria e posso creare programmi che utilizzano pezzi di memoria enorme.
Se malloc a e poi malloc a di nuovo il primo blocco di memoria rimane inutilizzabile dal sistema e quindi potrebbe appensantire il sistema.

In python:

a= [1,2,3]
a=[5,6,7]

quindi a di prima non è più utilizzato e occupa una posizione nella memoria.
In Python vi sono algoritmi che eliminano la memoria "spazzatura" e li rimette a disposizione del sistema. In C questo non è possibile.
*/



/*
Nella memoria stack vengono inserite le variabili

MAIN
___________
b 100 int |
__________|
c 30 int  |
__________|          ///questo riguarda il MAIN
n,p       |
__________|


VISUALIZZA
__________
a  8 byte|
_________|          /// questo riguarda la funzione VISUALIZZA
i        |
_________|
n        |
_________|
x 10 int |
_________|


HEAP
__________
n  int 30|
         |
_________|




main b[100],c[n]


quando la funzione visualizza tutti i termini vengono rilasciati e termina la funzione


Il puntatore a punta ad n nella funzione HEAP
*/









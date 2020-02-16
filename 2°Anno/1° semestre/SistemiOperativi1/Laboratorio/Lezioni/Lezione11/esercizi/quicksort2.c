#define _GNU_SOURCE
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>

#define Buf_size 10
// genera array di n elementi con interi random tra 0 e 999999
int *random_array(int n, int seed)
{
    assert(n>0);
    srandom(seed);
    int *a = malloc(n* sizeof(int));
    assert(a!=NULL);
    for(int i=0; i<n; i++)
        a[i] = (int) random() % 1000000;
    return a;
}

// crea una copia dell'array a
int *copy_array(int *a, int n)
{
    int *b = (int *) malloc(n* sizeof(int));
    assert(b!=NULL);
    for(int i=0; i<n; i++)
        b[i] = a[i];
    return b;
}

// verifica che l'array a[0..n] sia uguale a b[0..n]
bool check_sort(int *a, int *b, int n)
{
    for(int i=0; i<n; i++)
        if(a[i]!=b[i]) return false;
    return true;
}

// funzione di confronto tra interi passata a qsort
int intcmp(const void *a, const void *b)
{
    return *((int *) a) - *((int *) b);
}
typedef struct dato
{
    int p;
    int r;
} DATO;

// struct contenente i parametri di input e output di ogni thread
typedef struct
{
    DATO pr;
    int limite;
    int *A;
} dati;
// prototipo quicksort e partition


void quicksort(int a[], int, int );
int partition(int A[], int p, int r);
void very_quicksort(int *A,int p,int r, int limite);
// funzione eseguita dai thread consumer


void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    very_quicksort(a->A,a->pr.p,a->pr.r,a->limite);//,a->limite);
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{

    int numel , limite, seed;
    if((argc<3)||(argc>4))
    {
        fprintf(stderr,"USO:  %s numel numth limite [seed]\n\n",argv[0]);
        exit(1);
    }
    numel = atoi(argv[1]);
    if(numel<1)
    {
        fprintf(stderr,"Input non valido (main)\n");
        exit(1);
    }
    limite = atoi(argv[2]);
    /* ----------- legge il seme per i numeri casuali ----------- */
    if(argc==4)
        seed = atol(argv[3]);
    else
        seed = 3141562;
    ///----Definizione threads e struttura dati-----
    ///-----Creazione semafori------
    // genera array random
    int *array = random_array(numel,seed);
    // copia array e ordina la copia usando la funzione di libreria
    int *copia = copy_array(array,numel);
    qsort(copia,numel,sizeof(int), intcmp);

    very_quicksort(array,0,numel-1,limite);
    // segnalo terminazione
    ///-------Controllo che array sia ordinato-------
        for (int i = 0 ; i <numel; i++)printf("ARRAY: %d\n",array[i]);
        for (int i = 0 ; i <numel; i++)printf("----COPIA: %d\n",copia[i]);
        if(check_sort(array,copia,numel))
            fprintf(stderr,"Sort OK\n");
        else
            fprintf(stderr,"Sorting fallito\n");
        return 0;

}
//Ci vuole una struct di due valore p e r nel buffer
///-------Funzione veryquicksort-------
    void very_quicksort(int *A,int p,int r, int limite)
    {
       pthread_t t;

       dati a;
        int q;

        if(p < r)
        {
            bool aiutato = false;
            q =  partition(A,p,r);
            if ((r - q) >limite)
            {
                a.A=A;
                a.pr.p=q+1;
                a.pr.r=r;
                a.limite = limite;
                int e = pthread_create(&t, NULL, tbody, (void *) &a);
                assert(e==0);
                aiutato= true;
            }
            else
               very_quicksort(A,q+1,r,limite);

            very_quicksort(A,p,q,limite);
            if (aiutato)
              pthread_join(t, NULL);

        }
    }

// Quicksort: ordina A[p]...A[r] (p<=r)
// il numero di elementi totale da ordinare e' 1+r-p
    void quicksort(int *A, int p, int r)
    {
        int q;

        if(p<r)    // se p==r  c'e'un solo elemento e quindi non si deve ordinare
        {
            ///Qua va fatta la modifica, quando array ha meno di
            ///20 elementi non lo ordino con la partition ma con un thread
            ///num el array -- num thread -- limite ordinamento passato al thread -- seed per i numeri casuali
            ///
            q = partition(A,p,r);
            quicksort(A,p,q);
            quicksort(A,q+1,r);
        }
    }


    /* ***********************************************************
       partition con scelta pivot mediano di 3
       per evitare l'uso di random che e' lenta e non thread safe
       *********************************************************** */
    int partition(int A[], int p, int r)
    {
        int t,x;
        int i,j;

        // il pivot sara' il mediano tra A[p],A[i],A[r]
        i = (p+r)/2;
        if( A[p] > A[i] )
        {
            t=A[i];    // scambia A[i]<->A[p]
            A[i]=A[p];
            A[p]=t;
        }
        if( A[p] > A[r] )
        {
            t=A[r];    // scambia A[r]<->A[p], ora A[p] e' il minino
            A[r]=A[p];
            A[p]=t;
        }
        if( A[i] > A[r] )
        {
            t=A[r];    // scambia A[r]<->A[i], ora A[p]<= A[i] <= A[r]
            A[r]=A[i];
            A[i]=t;
        }

        x = A[i];                   // pivot
        t=A[i];
        A[i]=A[p];
        A[p]=t;    // scambia A[i]<->A[p]

        i= p-1;
        j= r+1;
        while(1)
        {
            while(A[--j]>x) ; // scan da destra a sinistra: esce se A[j]<=x
            while(A[++i]<x) ; // scan da sinistra a destra: esce se A[i]>=x
            if(i<j)
            {
                t=A[i];
                A[i]=A[j];
                A[j]=t;  // scambia A[i] <-> A[j] e riprendi scansioni
            }
            else break;       // se i>=j termina
        }
        return j;
    }

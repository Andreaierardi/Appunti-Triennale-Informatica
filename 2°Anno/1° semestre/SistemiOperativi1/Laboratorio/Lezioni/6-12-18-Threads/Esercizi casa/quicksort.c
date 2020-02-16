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
#include "xerrors.c"
#include "xerrors.h"
#define Buf_size 10
// genera array di n elementi con interi random tra 0 e 1999
int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  if(a==NULL) die("errore allocazione");
  for(int i=0;i < n;i++)
    a[i] = (int) random() % 2000;
  return a;
}


// crea una copia dell'array a
int *copy_array(int *a,int *b, int n)
{
    for(int i=0; i<n; i++)
        b[i] = a[i];
    return b;
}

// verifica che array a[0..n-1] sia ordinato 
bool check_sort(int a[], int n)
{
  for(int i=0; i < n-1; i++)
     if(a[i] > a[i+1]) return false;
  return true;
}

// funzione di confronto tra interi passata a qsort
int intcmp(const void *a, const void *b)
{
    return *((int *) a) - *((int *) b);
}


// struct contenente i parametri di input e output di ogni thread
typedef struct
{
    int p;
    int q;
    int limite;
    int *A;
} dati;
// prototipo quicksort e partition


void quicksort(int a[], int, int );
int partition(int A[], int p, int r);
void mt_qsort(int *A,int p,int r, int limite);
// funzione eseguita dai thread consumer

///CORPO DEL THREAD

void *tbody(void *arg)
{
	//Assegno la struttura dati del thread ad una variabile
    dati *a = (dati *)arg;
    //Richiamo la mt_qsort dal thread passando i dati della struttura dati "dati"
    //Infatti in a->A conterrà l'array, in a->p avrà il valore di p e così via
    //Richiamo la mt_qsort passando p,q,limite come definito dalla consegna
    mt_qsort(a->A,a->p,a->q,a->limite);
    
    //Termino il thread
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{

//Se passo un numero di parametri divero da tre errore
    if(argc!=3)
        die("USO:  %s numel limite \n\n");
     
//Se passo un numero di parametri adeguato allora li assegno a delle variabili
    int numel = numel = atoi(argv[1]);
    int limite = atoi(argv[2]);

//verifico che i parametri siano interi maggiori di 1, altrimenti errore
    if(numel<1 || limite < 1)
        die("Input non valido (main)\n");
 
// genera array random e lo stampo
    int *array = random_array(numel);
	printf("\n======ARRAY INZIALE========\n");
	for (int i = 0 ; i <numel; i++)printf("ARRAY: %d\n",array[i]);

//Richiamo di funzione della mt_qsort dal main passando array,p,r e limite
    mt_qsort(array,0,numel-1,limite);

///-------Controllo che array sia ordinato-------
	printf("\n======ARRAY ORDINATO========\n");
	for (int i = 0 ; i <numel; i++)printf("ARRAY: %d\n",array[i]);
	
//Se array ordinato allora conferma il sort altimenti stampa sorting fallito
	if(check_sort(array,numel))
		fprintf(stderr,"\nSort OK - SORTING AVVENUTO CON SUCCESSO\n");
	else
		fprintf(stderr,"\nSorting fallito\n");
		
	return 0;

}
//Ci vuole una struct di due valore p e r nel buffer
///-------Funzione mt_qsort-------
    void mt_qsort(int *A,int p,int r, int limite)
    {
//Dichiaro la variabile thread e le strutture dati utili per la creazione del thread ausiliario
       pthread_t t;
       dati a;
		
	   ///PASSO BASE 
        if(r-p+1 <=limite) 
				qsort(A+p,r-p+1,sizeof(int),intcmp); //Una volta arrivato al caso base ordino una parte di array dalla posizione p dell'array A in poi per r-p+1 elementi
	
	   ///PASSO RICORSIVO
		else
        {
			//  // invoca la procedura partition per mettere in 
      // a[p] ... a[q] gli elementi "piccoli" e in a[q+1]...a[r] gli elementi "grandi" 
				int q =  partition(A,p,r);
           //assegno i valori passati come parametro e q ottenuto dalla partition al thread nella struttura dati.
                a.A=A;
                a.p=p;       
                a.q = q;
                a.limite = limite;
                
         //Creo processo ausiliario che si occupa degli elementi da p a q
                xpthread_create(&t, NULL, tbody, (void *) &a,__LINE__,__FILE__);
                
         //Il thread "padre" invece si occupa degli elementi da q+1 a r
                mt_qsort(A,q+1,r,limite);
///ASPETTO TERMINAZIONE DEL THREAD AUSILIARIO
                pthread_join(t, NULL);

               

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

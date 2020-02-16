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
#include "xerrors.h"
#include "xerrors.c"

#define Buf_size 10
// genera array di n elementi con interi random tra 0 e 1999
int *random_array(int n, int seed)
{
  assert(n>0);
  srandom(seed);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i<n;i++)
    a[i] = (int) random() % 2000;
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
typedef struct dato
{
    int p;
    int r;
    int q;
} PQR;

// struct contenente i parametri di input e output di ogni thread
typedef struct
{
    PQR pr;
    PQR *buffer;
    int *cindex;
	int *pindex;
    int limite;
    int *A;
    pthread_mutex_t *mutex_consumers;
    sem_t *sem_free_slots;
    sem_t *sem_data_items;
} dati;
// prototipo quicksort e partition


void quicksort(int a[], int, int );
int partition(int A[], int p, int r);
void very_quicksort(int *A,int p,int r, int limite, PQR *buffer, int *pindex,pthread_mutex_t *mutex_consumers, sem_t *sem_data_items, sem_t *sem_free_slots);
// funzione eseguita dai thread consumer

void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    printf("		THREAD %d %d\n",a->pr.p,a->pr.q);
    very_quicksort(a->A,a->pr.p,a->pr.q,a->limite, a->buffer,  a->pindex, a->mutex_consumers, a->sem_data_items, a->sem_free_slots);

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

    // genera array random
    int *array = random_array(numel,seed);
    
    
     ///----Creazione buffer con indice produttore e consumatore------
	PQR buffer[Buf_size];
	int cindex=0;
	int pindex=0;
    sem_t sem_free_slots, sem_data_items;
    // inizializzazione semafori
    xsem_init(&sem_free_slots, 0, Buf_size,__LINE__,__FILE__);
    xsem_init(&sem_data_items, 0, 0,__LINE__,__FILE__);
    pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;

    very_quicksort(array,0,numel-1,limite,buffer,&pindex, &mutex_consumers, &sem_data_items,&sem_free_slots);
    // segnalo terminazione
  
	
	PQR n = buffer[cindex];
	printf("p %d r:%d\n",n.p,n.r);
	
  ///-------Controllo che array sia ordinato-------
  
  //Rilascio le strutture dati
  sem_destroy(&sem_data_items);
  sem_destroy(&sem_free_slots);
  pthread_mutex_destroy(&mutex_consumers);

  for (int i = 0; i<numel ; i++)
	printf("%d\n",array[i]);
  if(check_sort(array,numel))
    fprintf(stderr,"Sort OK\n");
  else
    fprintf(stderr,"Sorting fallito\n");
  return 0;

}
//Ci vuole una struct di due valore p e r nel buffer
///-------Funzione veryquicksort-------
void very_quicksort(int *A,int p,int r, int limite, PQR *buffer, int *pindex,pthread_mutex_t *mutex_consumers, sem_t *sem_data_items, sem_t *sem_free_slots)
 {
  dati a;
  int q;
  pthread_t t;

  if(p < r)
  {
    if ((r - p) <= limite)
    {
		
	  PQR n;
	  xsem_wait(sem_free_slots,__LINE__,__FILE__);
      
      n.r= r;
      n.p =p ;
      printf("Scrivo %d e %d\n",p,r);
      //Inserisco il nuovo DATO n nel buffer

      buffer[*pindex] = n;
      //Incremento il numero di item prodotti
      *pindex = (*pindex+1)%Buf_size;

      //Incremento (up) il semaforo perchè ho prodotto un items
      xsem_post(sem_data_items,__LINE__,__FILE__);
     }
    

    else
    {

      q =  partition(A,p,r);
	  a.A=A;
      a.pr.p=p;
      a.pr.q=q;
      
      a.sem_data_items  = sem_data_items;
      a.sem_free_slots  = sem_free_slots;
      a.limite = limite;
      		printf("CREO THREAD\n");
      xpthread_create(&t, NULL, tbody, (void *) &a,__LINE__,__FILE__);
	printf("ORA\n");
      very_quicksort(A,q+1,r,limite,buffer , pindex, mutex_consumers, sem_data_items,sem_free_slots);
     xpthread_join(t, NULL,__LINE__,__FILE__);
     printf("JOINATO\n");

    }
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

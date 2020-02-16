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
// genera array di n elementi con interi random tra 0 e 999999
int *random_array(int n, int seed)
{
  assert(n>0);
  srandom(seed);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i<n;i++)
    a[i] = (int) random() % 1000000;
  return a;
}

// crea una copia dell'array a
int *copy_array(int *a, int n)
{
  int *b = (int *) malloc(n* sizeof(int));
  assert(b!=NULL);
  for(int i=0;i<n;i++)
    b[i] = a[i];
  return b;
}

// verifica che l'array a[0..n] sia uguale a b[0..n]
bool check_sort(int *a, int *b, int n)
{
  for(int i=0;i<n;i++)
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
}DATO;

// prototipo quicksort e partition
void quicksort(int a[], int, int );
int partition(int A[], int p, int r);
void very_quicksort(int *A,int p,int r, int limite, DATO *buffer, int *pindex, sem_t *sem_data_items, sem_t *sem_free_slots);


// struct contenente i parametri di input e output di ogni thread
typedef struct {
  DATO *buffer;
  int *cindex;
  DATO pr;
  int *A;
  pthread_mutex_t *mutex_consumers;
  sem_t *sem_free_slots;
  sem_t *sem_data_items;
} dati;

// funzione eseguita dai thread consumer
void *tbody(void *arg)
{
  dati *a = (dati *)arg;
  while(1)
    {
      //aspetta che compaia una coppia (p,r) sul buffer
          xsem_wait(a->sem_data_items,__LINE__,__FILE__);
          xpthread_mutex_lock(a->mutex_consumers,__LINE__,__FILE__);
          DATO n= a->buffer[*(a->cindex)];
          *(a->cindex) = (*(a->cindex) + 1) % Buf_size;

          xpthread_mutex_unlock(a->mutex_consumers,__LINE__,__FILE__);
          xsem_post(a->sem_free_slots,__LINE__,__FILE__);

         if ((n.p<0)&&(n.r<0)) break;
         quicksort(a->A,n.p,n.r);

    }
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  int numel, numth , limite, seed;
  if((argc<4)||(argc>5)) {
    fprintf(stderr,"USO:  %s numel numth limite [seed]\n\n",argv[0]);
    exit(1);
  }
  numel = atoi(argv[1]);
  if(numel<1) {
    fprintf(stderr,"Input non valido (main)\n");
    exit(1);
  }
  numth= atoi(argv[2]);
  limite = atoi(argv[3]);
  /* ----------- legge il seme per i numeri casuali ----------- */
  if(argc==5)
    seed = atol(argv[4]);
  else
    seed = 3141562;
    ///----Creazione buffer------
  DATO buffer[Buf_size];
  int cindex=0;
  int pindex=0;
  ///----Definizione threads e struttura dati-----
  pthread_t t[numth];
  dati a[numth];
  ///-----Creazione semafori------
  sem_t sem_free_slots, sem_data_items;
  pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
  // inizializzazione semafori
  xsem_init(&sem_free_slots, 0, Buf_size,__LINE__,__FILE__);
  xsem_init(&sem_data_items, 0, 0,__LINE__,__FILE__);
  // genera array random
  int *array = random_array(numel,seed);
  // copia array e ordina la copia usando la funzione di libreria
  int *copia = copy_array(array,numel);
  for(int i=0;i<numth;i++) {
        a[i].A=array;
        a[i].buffer = buffer;
        a[i].cindex = &cindex;
        a[i].mutex_consumers = &mutex_consumers;
        a[i].sem_data_items  = &sem_data_items;
        a[i].sem_free_slots  = &sem_free_slots;
        xpthread_create(&t[i], NULL, tbody, (void *) &a[i],__LINE__,__FILE__);
      }
  qsort(copia,numel,sizeof(int), intcmp);

  // eseguo il mio algoritmo di ordinamento
  if (numth == 0 )quicksort(array,0,numel-1);
  ///------Richiamo funzione-----
  very_quicksort(array,0,numel-1,limite, buffer,&pindex,&sem_data_items,&sem_free_slots);
   // segnalo terminazione

  for(int i=0;i<numth;i++) {
    xsem_wait(&sem_free_slots,__LINE__,__FILE__);
    DATO n;
    n.p = -1;
    n.r = -1;
    buffer[pindex] =n ;
    pindex = (pindex+1)%Buf_size;
    xsem_post(&sem_data_items,__LINE__,__FILE__);
  }

   ///-----Aspetta risultato-----
  for(int i=0;i<numth;i++)
    xpthread_join(t[i], NULL,__LINE__,__FILE__);


  ///-------Controllo che array sia ordinato-------
  sem_destroy(&sem_data_items);
  sem_destroy(&sem_free_slots);
  pthread_mutex_destroy(&mutex_consumers);
  if(check_sort(array,copia,numel))
    fprintf(stderr,"Sort OK\n");
  else
    fprintf(stderr,"Sorting fallito\n");
  return 0;
}
//Ci vuole una struct di due valore p e r nel buffer
///-------Funzione veryquicksort-------
void very_quicksort(int *A,int p,int r, int limite, DATO *buffer, int *pindex, sem_t *sem_data_items, sem_t *sem_free_slots)
 {
  DATO n ;
  int q;

  if(p < r)
  {
    if ((r - p) <= limite)
    {

      xsem_wait(sem_free_slots,__LINE__,__FILE__);
      n.r= r;
      n.p =p ;
      buffer[*pindex] = n;
      *pindex = (*pindex+1)%Buf_size;
      xsem_post(sem_data_items,__LINE__,__FILE__);
    }
    else
    {

      q =  partition(A,p,r);

      very_quicksort(A,p,q,limite, buffer , pindex,sem_data_items,sem_free_slots);
      very_quicksort(A,q+1,r,limite,buffer , pindex,sem_data_items,sem_free_slots);
    }
  }
 }

// Quicksort: ordina A[p]...A[r] (p<=r)
// il numero di elementi totale da ordinare e' 1+r-p
void quicksort(int *A, int p, int r)       {
  int q;

  if(p<r) {  // se p==r  c'e'un solo elemento e quindi non si deve ordinare
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
      {t=A[i];A[i]=A[p];A[p]=t;} // scambia A[i]<->A[p]
  if( A[p] > A[r] )
      {t=A[r];A[r]=A[p];A[p]=t;} // scambia A[r]<->A[p], ora A[p] e' il minino
  if( A[i] > A[r] )
      {t=A[r];A[r]=A[i];A[i]=t;} // scambia A[r]<->A[i], ora A[p]<= A[i] <= A[r]

  x = A[i];                   // pivot
  t=A[i];A[i]=A[p];A[p]=t;    // scambia A[i]<->A[p]

  i= p-1; j= r+1;
  while(1) {
    while(A[--j]>x) ; // scan da destra a sinistra: esce se A[j]<=x
    while(A[++i]<x) ; // scan da sinistra a destra: esce se A[i]>=x
    if(i<j) {
      t=A[i]; A[i]=A[j]; A[j]=t;  // scambia A[i] <-> A[j] e riprendi scansioni
    }
    else break;       // se i>=j termina
  }
  return j;
}

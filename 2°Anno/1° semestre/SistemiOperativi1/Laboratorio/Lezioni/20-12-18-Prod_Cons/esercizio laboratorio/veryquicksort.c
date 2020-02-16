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
// genera array di n elementi con interi random tra 0 e 2000
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
  for(int i=0;i<n;i++)
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

///STRUTTURA DATO
//In questo modo, consumando una posizione nel buffer condiviso senza dover distinguere p o r per la quicksort
//INfatti se avessimo p e r passati da due thread in modo contemporaneo non si saprebbe a quale dei due threads appartiene così si impacchetta tutto in un'unica struttura dati
typedef struct dato
{
    int p;
    int r;
}DATO;

// prototipo quicksort e partition e veryquicksort
void quicksort(int a[], int, int );
int partition(int A[], int p, int r);
void very_quicksort(int *A,int p,int r, int limite, DATO *buffer, int *pindex, sem_t *sem_data_items, sem_t *sem_free_slots);


// struct contenente i parametri di input e output di ogni thread
typedef struct {
	//Buffer per garantire lo scambio tra produttore e consumatore
  DATO *buffer;
  //Cindex è l'indice del consumatore che ci dice quanti oggetti ci sono da consumare
  int *cindex;
  //Passo la struttura dati pr
  DATO pr;
  //Passo l'array A  da ordinare
  int *A;
  //Passo mutex, semafori consumatore e produttore
  pthread_mutex_t *mutex_consumers;
  sem_t *sem_free_slots;
  sem_t *sem_data_items;
} dati;

// funzione eseguita dai thread consumer
void *tbody(void *arg)
{
	//assegno la struttura dati ad una variabile locale per poterla utilizzare all'interno del thread
  dati *a = (dati *)arg;
  
  ///while(1) {
  ///aspetta che compaia una coppia (p,r) sul buffer
  ///quicksort(A,p,r)

//While true che cicla fino a che si trova una copia p,r sul buffer (ovvero finchè si trova un DATO)
  while(1)
    {
      //aspetta che compaia una coppia (p,r) sul buffer
      //Verifica che il semaforo data items abbia posizioni da consumare (quindi ci siano elementi da consumare sul buffer (il buffer non è vuoto)
          xsem_wait(a->sem_data_items,__LINE__,__FILE__);
          //Mutex per l'accesso in mutua esclusione sul buffer
          xpthread_mutex_lock(a->mutex_consumers,__LINE__,__FILE__);
          //Prelevo dal buffer il valore DATO per poter utilizzare dopo
          DATO n= a->buffer[*(a->cindex)];
          //Aumento indice dei valori consumati di uno visto che ne ho prelevato uno
          *(a->cindex) = (*(a->cindex) + 1) % Buf_size;

		  //Sblocco mutex visto che ho finito di lavorare sul buffer
          xpthread_mutex_unlock(a->mutex_consumers,__LINE__,__FILE__);
		
		  //Faccio up sul semaforo free_slots(quindi dico che c'è una posizione libera in più sul buffer)
          xsem_post(a->sem_free_slots,__LINE__,__FILE__);

		//Controllo che ci permette di terminare ciclo quando ho consumato tutti gli item del buffer 
		///Il produttore, infatti, andrà a produrre valori di -1 quando ha terminato i valori da inserire, di conseguenza se i valori da produrre sono terminati allora il consumer troverà sul buffer valori minore di 0
         if ((n.p<0)&&(n.r<0)) break;
         
         //RICHIAMO DELLA FUNZIONE quicksort(A,p,r) come richiesto in consegna

         quicksort(a->A,n.p,n.r);

    }
    //CHIUSURA del thread
  pthread_exit(NULL);
}

///CODICE MAIN 
int main(int argc, char *argv[])
{
	
  int numel, numth , limite, seed;
  
  //Siccome abbiamo bisogno di almeno numel(valori nell'array), numth(numero thread) e limite allora argc deve essere uguale a 4, mentre se andassi ad aggiungere pure il seed allora avrei 5 item in argc. 
  //Quindi se il valore di argc è minore di 4 e maggiore di 5 è sbagliato.
  if((argc<4)||(argc>5)) 
    die("USO:  numel numth limite [seed]\n\n");
  
  
  //Assegno il numero di elementi a numel e poi verifico che sia maggiore di 1
  numel = atoi(argv[1]);
  if(numel<1)
     die("Input non valido (main)\n");
  
  //Assegno numero thread a numth e limite
  numth= atoi(argv[2]);
  limite = atoi(argv[3]);
  /* ----------- legge il seme per i numeri casuali ----------- */
  if(argc==5)
    seed = atol(argv[4]);
  else
    seed = 3141562; //Seed può essere un numero qualsiasi
  
    ///----Creazione buffer con indice produttore e consumatore------
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

//PASSO TUTTE LE STRUTTURE DATI PER OGNI THREAD
  for(int i=0;i<numth;i++) {
        a[i].A=array;
        a[i].buffer = buffer;
        a[i].cindex = &cindex;
        a[i].mutex_consumers = &mutex_consumers;
        a[i].sem_data_items  = &sem_data_items;
        a[i].sem_free_slots  = &sem_free_slots;
        xpthread_create(&t[i], NULL, tbody, (void *) &a[i],__LINE__,__FILE__);
      }

  // eseguo il mio algoritmo di ordinamento se il numero di processi indicati è 0 (quindi è una quicksort normale)
  if (numth == 0 )quicksort(array,0,numel-1);
  
  ///------Richiamo funzione-----
  very_quicksort(array,0,numel-1,limite, buffer,&pindex,&sem_data_items,&sem_free_slots);
   // segnalo terminazione

//Thread produttore nel MAIN

  for(int i=0;i<numth;i++) {
	  
	  //Faccio down sul semaforo se ci sono posti liberi nel buffer
    xsem_wait(&sem_free_slots,__LINE__,__FILE__);
    //Carico dato a -1 sul buffer in modo tale che quando i consumatori avranno finito di lavorare sul buffer potranno terminare il ciclo.
    //NB. C'è bisogno di inserire un -1 per ogni thread consumatore
    DATO n;
    n.p = -1;
    n.r = -1;
    //Inseriesco il DATO nel buffer e incremneto indice di 1
    buffer[pindex] =n ;
    pindex = (pindex+1)%Buf_size;
    //Faccio up su data_items perchè ho occupato una posizione nel buffer
    xsem_post(&sem_data_items,__LINE__,__FILE__);
  }

   ///-----Aspetto che tutti i thread abbiamo terminato-----
  for(int i=0;i<numth;i++)
    xpthread_join(t[i], NULL,__LINE__,__FILE__);


  ///-------Controllo che array sia ordinato-------
  
  //Rilascio le strutture dati
  sem_destroy(&sem_data_items);
  sem_destroy(&sem_free_slots);
  pthread_mutex_destroy(&mutex_consumers);
  
  
  if(check_sort(array,numel))
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

///if(p < r) {
   /// if (numero di elementi da ordinare <= limite)
      ///scrivi coppia (p,r) sul buffer
  if(p < r)
  {
    if ((r - p) <= limite)
    {
//Per scrivere copia sul buffer devo prima verificare che ci siano slot liberi
      xsem_wait(sem_free_slots,__LINE__,__FILE__);
      
      n.r= r;
      n.p =p ;
      
      //Inserisco il nuovo DATO n nel buffer
      buffer[*pindex] = n;
      //Incremento il numero di item prodotti
      *pindex = (*pindex+1)%Buf_size;
      //Incremento (up) il semaforo perchè ho prodotto un items
      xsem_post(sem_data_items,__LINE__,__FILE__);
    }
    
  /// else {
  ///    q =  partition(A,p,r);
  ///    ordina ricorsivamente A[p] ... A[q]
  ///    ordina ricorsivamente A[q+1] .. A[r]
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

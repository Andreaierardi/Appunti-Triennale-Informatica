/*
 * Esempio semplice paradigma produttore consumatori
 * 
 * Usare il numeri.py per generare lunghi elenchi di interi positivi su cui testare il programma
 * 
 * Programma di esempio del paradigma 1 producer N consumer
 * i dati letti dal file vengono messi su un buffer in cui il producer scrive 
 * e i consumer leggono. In principio il buffer va bene di qualsiasi dimensione: 
 * piu' e' grande maggiore e' il lavoro pronto da svolgere nel caso
 * il produttore rimanga bloccato (ad esempio a leggere dal disco)
 * 
 * */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>      
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>

#define Buf_size 10


// funzione per stabilire se n e' primo  
bool primo(int n)
{
  if(n<2) return false;
  if(n%2==0) return (n==2);
  for (int i=3; i*i<=n; i += 2)
      if(n%i==0) return false;
  return true;
}

// struct contenente i parametri di input e output di ogni thread 
typedef struct {
  int quanti;   // output
  long somma;   // output
  int *buffer; 
  int *cindex;
  pthread_mutex_t *mutex_consumers;
  sem_t *sem_free_slots;
  sem_t *sem_data_items;  
} dati;



// funzione eseguita dai thread consumer
void *tbody(void *arg)
{  
  dati *a = (dati *)arg;
  
  a->quanti = a->somma = 0;
  while(true) {
    int e = sem_wait(a->sem_data_items);
    assert(e==0);
    pthread_mutex_lock(a->mutex_consumers);
    int n = a->buffer[*(a->cindex)];
    *(a->cindex) = (*(a->cindex) + 1) % Buf_size;
    pthread_mutex_unlock(a->mutex_consumers);
    e = sem_post(a->sem_free_slots);
    assert(e==0);
    if(n<0) break;
    if(primo(n)) {
      a->quanti += 1;
      a->somma += n;
    }
  }
  pthread_exit(NULL); 
}     


int main(int argc, char *argv[])
{
  // leggi input
  if(argc!=3) {
    printf("Uso\n\t%s file numthread\n", argv[0]);
    exit(1);
  }
  int p = atoi(argv[2]);
  assert(p>=0);
  int tot_primi = 0;
  long tot_somma = 0;
  int i,e,n;    
  // threads related
  int buffer[Buf_size];
  int cindex=0, pindex=0;
  pthread_t t[p];
  dati a[p];
  sem_t sem_free_slots, sem_data_items;
  pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
  
  // inizializzazione semafori
  e = sem_init(&sem_free_slots, 0, Buf_size);
  assert(e==0);
  e = sem_init(&sem_data_items, 0, 0);
  assert(e==0);
  //  creo i thread consumatori
  for(i=0;i<p;i++) {
    a[i].buffer = buffer;
    a[i].cindex = &cindex;
    a[i].mutex_consumers = &mutex_consumers;
    a[i].sem_data_items  = &sem_data_items;
    a[i].sem_free_slots  = &sem_free_slots;
    e = pthread_create(&t[i], NULL, tbody, (void *) &a[i]);
    assert(e==0);
  }

  // read file and count primes 
  FILE *f = fopen(argv[1],"r");
  if(f==NULL) {perror("Errore apertura file"); return 1;}
  while(true) {
    e = fscanf(f,"%d", &n);
    if(e!=1) break; // se il valore e' letto correttamente e==1
    assert(n>0);    // i valori del file devono essere positivi
    // se p==0 non usa i thread consumatori
    if(p==0) {
      if(primo(n)) {
        tot_primi += 1;
        tot_somma += n;
      }
    }
    else {
      e = sem_wait(&sem_free_slots);
      assert(e==0);
      buffer[pindex] = n;
      pindex = (pindex+1)%Buf_size;
      e = sem_post(&sem_data_items);
      assert(e==0);
    }
  }
  // segnalo terminazione
  for(int i=0;i<p;i++) {
    e = sem_wait(&sem_free_slots);
    assert(e==0);
    buffer[pindex] = -1;
    pindex = (pindex+1)%Buf_size;
    e = sem_post(&sem_data_items);
    assert(e==0);
  }

  // join dei thread e calcolo risultato
  for(i=0;i<p;i++) {
    e = pthread_join(t[i], NULL);
    if(e==0) {
      fprintf(stderr,"Thread %d terminato\n",i);
      tot_primi += a[i].quanti;
      tot_somma += a[i].somma;
    }
    else 
      fprintf(stderr,"Errore join %d\n",e);
  }

  fprintf(stderr,"Trovati %d primi con somma %ld\n",tot_primi,tot_somma);
  return 0;
}


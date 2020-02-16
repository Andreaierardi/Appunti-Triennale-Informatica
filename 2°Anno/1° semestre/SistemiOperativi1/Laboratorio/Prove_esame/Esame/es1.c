#define _GNU_SOURCE
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "xerrors.h"
#define Buf_size 10

// es1: ok
// es2: non terminava la lettura e manca mutex su file di output

// voto: 28



// struct contenente i parametri di input e output di ogni thread
typedef struct {
  FILE *fp;
  int *buffer;
  int *cindex;
  pthread_mutex_t *mutex_consumers;
  pthread_mutex_t *file;
  sem_t *sem_free_slots;
  sem_t *sem_data_items;
} dati;


int divisori(int n)
{ int count = 0 ;
  for (int i = 1; i<=n ; i++)
  if (n %i == 0 )
     count++;
  return count ;
}

// funzione eseguita dai thread consumer
void *tbody(void *arg)
{
  dati *a = (dati *)arg;
  int div;
  while(true) {

    xsem_wait(a->sem_data_items,__LINE__,__FILE__);
    xpthread_mutex_lock(a->mutex_consumers,__LINE__,__FILE__);
    int n = a->buffer[*(a->cindex)];
    *(a->cindex) = (*(a->cindex) + 1) % Buf_size;
    xpthread_mutex_unlock(a->mutex_consumers,__LINE__,__FILE__);
    xsem_post(a->sem_free_slots,__LINE__,__FILE__);

    if(n<0) break;
    div = divisori(n);
    xpthread_mutex_lock(a->file,__LINE__,__FILE__);
    fprintf(a->fp,"%d %d\n",n,div);
    xpthread_mutex_unlock(a->file,__LINE__,__FILE__);
  }
  pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
  // leggi input
  if(argc!=4) {
    printf("Uso\n\t%s infile outfile nthreads\n", argv[0]);
    exit(1);
  }
  int p= atoi(argv[3]);
  assert(p>=0);
  int i,e;
  // threads related
  int buffer[Buf_size];
  int cindex=0, pindex=0;
  pthread_t t[p];
  dati a[p];
  sem_t sem_free_slots, sem_data_items;
  pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
  pthread_mutex_t mutex_file = PTHREAD_MUTEX_INITIALIZER;

  // inizializzazione semafori
  xsem_init(&sem_free_slots, 0, Buf_size,__LINE__,__FILE__);
  xsem_init(&sem_data_items, 0, 0,__LINE__,__FILE__);
  FILE *fp = fopen(argv[2],"w");
  //  creo i thread consumatori
  for(i=0;i<p;i++) {
    a[i].fp = fp;
    a[i].buffer = buffer;
    a[i].cindex = &cindex;
    a[i].mutex_consumers = &mutex_consumers;
    a[i].file= &mutex_file;
    a[i].sem_data_items  = &sem_data_items;
    a[i].sem_free_slots  = &sem_free_slots;
    xpthread_create(&t[i], NULL, tbody, (void *) &a[i],__LINE__,__FILE__);
  }

  // read file and count primes
  FILE *f = fopen(argv[1],"r");
  if(f==NULL) {perror("Errore apertura file"); return 1;}
  while(!feof(f)) {
      int n;
      xsem_wait(&sem_free_slots,__LINE__,__FILE__);
      e = fscanf(f,"%d", &n);
      if(e!=1) break; // se il valore e' letto correttamente e==1
      buffer[pindex] = n;
      pindex = (pindex+1)%Buf_size;
      xsem_post(&sem_data_items,__LINE__,__FILE__);
  }

  // segnalo terminazione
  for(int i=0;i<p;i++) {
    xsem_wait(&sem_free_slots,__LINE__,__FILE__);
    buffer[pindex] = -1;
    pindex = (pindex+1)%Buf_size;
    xsem_post(&sem_data_items,__LINE__,__FILE__);
  }

  // join dei thread
  for(i=0;i<p;i++) {
    xpthread_join(t[i], NULL,__LINE__,__FILE__);
    printf("Thread %d terminato \n",i);
    }
    e = fclose(f);
    if (e!=0 ){ perror("Errore chisura file");exit(1);}
    e = fclose(fp);
    if (e!=0 ){ perror("Errore chisura file");exit(1);}
    xpthread_mutex_destroy(&mutex_consumers,__LINE__,__FILE__);
    xpthread_mutex_destroy(&mutex_file,__LINE__,__FILE__);

  return 0;
}


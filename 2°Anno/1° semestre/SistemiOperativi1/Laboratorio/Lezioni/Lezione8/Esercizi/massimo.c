#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <pthread.h>
#include "xerrors.h"

// prototipi di funzione
int *random_array(int n);
int massimo(int *a, int n, int p);

typedef struct {
  int inizio;   // input
  int fine;
  int *array;     // puntatore alla tabella dei primi
  int *pmax;  // puntatore a messi
  pthread_mutex_t *pmutex_max; // mutex per regolare l'accesso alla tabella
  int massimo ;
} dati;

void *tbody(void *a)
{
  int e=0;
  dati *arg = (dati *)a;
  fprintf(stderr,"Thread cerca da %d a %d\n",arg->inizio,arg->fine);
  arg->massimo=0;
  for (int j=arg->inizio;j<arg->fine;j++)
    if(arg->array[j] > arg->massimo) arg->massimo = (arg->array[j]);

  e = pthread_mutex_lock(arg->pmutex_max);
  assert(e==0);
  if ((arg->massimo) > *(arg->pmax))
          *(arg->pmax) = (arg->massimo);
        // fine zona critica
  e = pthread_mutex_unlock(arg->pmutex_max);
  assert(e==0);
  pthread_exit(NULL);
}
// main
int main(int argc, char **argv)
{
  if(argc!= 3)
  {
    fprintf(stderr,"Uso:\n\t %s n p\n",argv[0]);
    exit(1);
  }
  int n= atoi(argv[1]);
  assert(n > 0);
  int p = atoi(argv[2]);
  assert(p > 0);

  int *a = random_array(n);
  int max = a[0];
  for(int i=1; i < n ;i++)
    if(a[i]>max) max=a[i];

  printf("\nMassimo calcolato con un thread: %d\n---------------\n",max);
  // questa e' la funzione da scrivere per esercizio
  int max2 = massimo(a,n,p);
  printf("Massimo calcolato con %d thread: %d\n",p, max2);
  if (max == max2)printf("Il massimo con i thread è GIUSTO\n");
  else{printf("Massimo ERRATO\n");}
  free(a);
  return 0;
}
// calcola il massimo dell'array a[] di n elementi
// utilizzando p thread
// ogni thread deve leggere al piu' (n/p)+1 elementi
int massimo(int *a, int n, int p) {

    pthread_t t[p];
    dati argomenti[p];
    int max = 0;
    pthread_mutex_t mutex_max = PTHREAD_MUTEX_INITIALIZER;
     ///argomenti[i].inizio = i*(n/p);
     ///argomenti[i].fine =  (i==p-1) ? n : (i+1)*(n/p);
    int parti= n/p;
    int resto= n%p;
    for(int i=0;i<p;i++)
    {
        argomenti[i].inizio = i*parti;
        argomenti[i].fine = (i>=p-resto) ? parti*i+parti+1 : parti*i+parti;
        argomenti[i].pmax = &max;
        argomenti[i].array= a;
        argomenti[i].pmutex_max =&mutex_max;
        xpthread_create(&t[i], NULL, tbody, (void *) &argomenti[i],__LINE__,__FILE__);
    }
    fprintf(stderr,"%d thread creati\n", p);

    for(int i=0;i<p;i++)
    {
        xpthread_join(t[i], NULL,__LINE__,__FILE__);
        fprintf(stderr,"Thread %d terminato\n",i);
        max = *(argomenti->pmax);
    }
    xpthread_mutex_destroy(&mutex_max,__LINE__,__FILE__);
    return max;
}
// genera array di n elementi con interi random tra -100000 e 100000
int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0; i < n ;i++)
    a[i] = (random()%200001) - 100000;
  return a;
}

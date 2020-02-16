#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "xerrors.h"

// prototipi di funzione
int *random_array(int n);
int intcmp(const void *a, const void *b);
void array_sort(int *a, int n);
bool check_sort(int *a, int n);

// main
int main(int argc, char **argv)
{
  if(argc!= 2)
  {
    fprintf(stderr,"Uso: nomefile n\n");
    exit(1);
  }
  int n= atoi(argv[1]);
  assert(n>0);
  int e, shmid;
  pid_t pid;
  // creazione array di memoria condivisa
  shmid = shmget(IPC_PRIVATE,n*sizeof(int),0600);
  if(shmid == -1) { perror("shared memory allocation"); exit(1);}
  int *a = shmat(shmid,NULL,0); // ora a punta all'array di memoria condivisa
  // visualizza pid per controllo memoria condivisa
  printf("Il pid di questo processo e': %d, l'id della memoria: %d\n",getpid(),shmid);
  // creazione array random
  int *array = random_array(n);
  // creazione processo figlio
  pid= xfork(__LINE__, __FILE__);
  // codice processo figlio
  if(pid==0)
  {
    int j=0;
    ///Scorro tutto l'array con un ciclo for da 0 a n
    for(int i=0;i<n;i++) if(array[i]>= RAND_MAX/2) array[j++] = array[i];
    ///Riempo array con indice j e lo ordino
    array_sort(array, j);
    // copia elementi
    ///Copio elementi di array in a con indice (i+ n - Elementi figlio)
    /// i da 0 a MAX figlio
    /// j = Max figlio
    /// n = Max array
    /// a[0 + 8 -4]
    ///
    for(int i=0;i<j;i++)
      a[i+n-j] = array[i];
    // detach memoria condivisa
    e = shmdt(a);
    if(e<0) {perror("shmdt"); exit(1);}
    exit(0);
  }
  // codice processo padre
  int j=0;
  for(int i=0;i<n;i++) if(array[i]< RAND_MAX/2) array[j++] = array[i];
  array_sort(array, j);
  for(int i=0;i<j;i++) a[i] = array[i];
  // aspetta che abbia finito il figlio
  pid  = xwait(NULL,__LINE__,__FILE__);
  // ora l'array e' ordinato
  puts(check_sort(a,n)? "ok\n" : "errore\n");
  // detach e rimozione memoria condivisa
  e = shmdt(a);
  if(e<0) {perror("shmdt"); exit(1);}
  e = shmctl(shmid, IPC_RMID,  NULL);
  if(e == -1) {perror("shmctl"); exit(1);}
  return 0;
}


// genera array di n elementi con interi random tra 0 e RAND_MAX
int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i < n;i++)
    a[i] = (int) random();
  return a;
}

// funzione di confronto tra interi passata da array_sort a qsort
int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}

// esegue il sort dell'array a[0..n] utilizzando la funzione di libreria qsort
void array_sort(int *a, int n)
{
  qsort(a,n,sizeof(int), intcmp);
}

// verifica che array a[0..n] sia ordinato
bool check_sort(int *a, int n)
{
  for(int i=0; i < n-1; i++)
     if(a[i] > a[i+1]) return false;
  return true;
}

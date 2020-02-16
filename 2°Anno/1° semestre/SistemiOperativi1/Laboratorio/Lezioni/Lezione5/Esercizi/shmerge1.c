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
#include "xerrors.c"
// prototipi di funzione
int *random_array(int n);
int intcmp(const void *a, const void *b);
void array_sort(int *a, int n);
bool check_sort(int *a, int n);
void mergesort(int a[], int left, int right);
void merge(int a[], int left, int center, int right);
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
  int shmid;
  pid_t pid;
  // creazione array di memoria condivisa
  shmid = shmget(IPC_PRIVATE,n*sizeof(int),0600);
  if(shmid == -1) { perror("shared memory allocation"); exit(1);}
  int *a = xshmat(shmid,NULL,0,__LINE__,__FILE__); // ora a punta all'array di memoria condivisa
  // visualizza pid per controllo memoria condivisa
  printf("Il pid di questo processo e': %d, l'id della memoria: %d\n",getpid(),shmid);
  // creazione array random
   int *array = random_array(n);
   for(int i=0; i<n; i++)
        a[i]=array[i];

    free(array);
  // creazione processo figlio
  pid= xfork(__LINE__, __FILE__);
  // codice processo figlio
  if(pid==0)
  {
    array_sort(&a[n/2+1],n/2-1);
    xshmdt(a,__LINE__,__FILE__);
    exit(0);
  }
   // codice processo padre
  array_sort(a,n/2+1);
  pid  = xwait(NULL,__LINE__,__FILE__);

  // ora l'array e' ordinato
  printf("\n---------FINE--------\n");
  for (int i = 0 ; i<n ; i++)
  printf("%d\n",a[i]);
  merge(a,0,n/2,n-1);
  puts(check_sort(a,n)? "ok\n" : "errore\n");

  // detach e rimozione memoria condivisa
  xshmdt(a,__LINE__,__FILE__);
  xshmctl(shmid, IPC_RMID,  NULL,__LINE__,__FILE__);

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

void mergesort(int a[], int left, int right){                                       //da qui in poi ho problemi                             int center;
   if (left<right){
   int center = (left+right)/2;
   mergesort(a, left, center);
   mergesort(a, center+1, right);
   merge(a, left, center, right);
   }
}

void merge(int a[], int left, int center, int right) {
int i, j, k;
int b[999];
i = left;
j = center+1;
k = 0;
   while ((i<=center) && (j<=right)){
      if (a[i] <= a[j]) {
         b[k] = a[i]; i++;
      } else {
         b[k] = a[j]; j++;}
         k++;
      }
   while (i<=center) {
      b[k] = a[i];
      i++;
      k++;
   }
   while (j<=right) {
      b[k] = a[j];
      j++;
      k++;
   }

      for (k=left; k<=right; k++)
         a[k] = b[k-left];
}

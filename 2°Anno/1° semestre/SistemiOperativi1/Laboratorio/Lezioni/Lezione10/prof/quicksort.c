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

// prototipo quicksort e partition 
void quicksort(int a[], int, int );
int partition(int A[], int p, int r);


int main(int argc, char *argv[])
{
  int n, seed;

  if((argc<2)||(argc>3)) {
    fprintf(stderr,"USO:  %s numel [seed]\n\n",argv[0]);
    exit(1);
  }
  n = atoi(argv[1]);
  if(n<1) {
    fprintf(stderr,"Input non valido (main)\n");
    exit(1);
  }

  /* ----------- legge il seme per i numeri casuali ----------- */
  if(argc==3)
    seed = atol(argv[2]);
  else
    seed = 3141562;

  // genera array random
  int *a = random_array(n,seed);
  // copia array e ordina la copia usando la funzione di libreria
  int *copia = copy_array(a,n);
  qsort(copia,n,sizeof(int), intcmp);
  
  // eseguo il mio algoritmo di ordinamento
  quicksort(a,0,n-1);
  
  // confronto a[] ordinato da me con copia[]
  if(check_sort(a,copia,n))
    fprintf(stderr,"Sort OK\n");
  else
    fprintf(stderr,"Sorting fallito\n");
  return 0;
}


// Quicksort: ordina A[p]...A[r] (p<=r)
// il numero di elementi totale da ordinare e' 1+r-p
void quicksort(int *A, int p, int r)       {
  int q;
  
  if(p<r) {  // se p==r  c'e'un solo elemento e quindi non si deve ordinare
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

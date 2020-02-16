

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
void handler(int s)
{

  while (s!=SIGUSR1) {
    // dopo aver fatto girare il programma la prima volta
    // s-commentate l'istruzione kill e osservate cosa succe
    //printf("Segnale %d ricevuto dal processo %d\n", s, getpid());
    pause();
  }
  printf("Segnale %d ricevuto dal processo %d ora posso terminare\n", s, getpid());
}


// main
int main(int argc, char **argv)
{
  if(argc!= 2)
  {
    fprintf(stderr,"Uso: nomefile n\n");
    exit(1);
  }
   // definisce signal handler
  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);     // setta a "insieme vuoto" sa.sa_mask maschera di segnali da bloccare
  sa.sa_flags = SA_RESTART;     // restart system calls  if interrupted
  sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
  sigaction(SIGUSR2,&sa,NULL);  // handler per USR2
  sigaction(SIGINT,&sa,NULL);   // handler per Control-C
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
  pid_t pidpadre=getpid();
  // creazione array random
  int *array = random_array(n);
  // creazione processo figlio
  pid= xfork(__LINE__, __FILE__);
  // codice processo figlio
  if(pid==0)
  {
    for(int i=0;i<n;i++) a[i] = array[i];
    array_sort(&a[1+n/2], n/2-1);
    // copia elementi
    // detach memoria condivisa
    e = shmdt(a);
    if(e<0) {perror("shmdt"); exit(1);}
    kill(pidpadre,SIGUSR1);
    exit(0);
  }
  // codice processo padre

  array_sort(a, n/2+1);
  // aspetta che abbia finito il figlio
  //pause();

  pause();
  for(int i=0;i<n;i++){
    array[i]=a[i];
  }
  e = shmdt(a);
  if(e<0) {perror("shmdt"); exit(1);}
  e = shmctl(shmid, IPC_RMID,  NULL);
  if(e == -1) {perror("shmctl"); exit(1);}
  mergesort(array,0,n);
  puts(check_sort(array,n)? "ok\n" : "errore\n");

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
/*void MergeSort(int A[],int p,int r){
    int q;
    if(p<r){
        q=(p+r)/2;
        MergeSort(A,p,q);
        MergeSort(A,q+1,r);
        Merge(A,p,q,r);
    }

}
void Merge(int A[],int p,int q,int r){
    int B[r];
    int i,j,k;
    i=p;j=q+i;k=p;
    while(i<=q && j<=r){
        if(A[i]<A[j]) B[k++]=A[j++];
        else B[k++]=A[j++];
    }
    while(i<=q) B[k++]=A[i++];
    while(j<=r) B[k++]=A[j++];
    for(k=p;k<=r;k++) A[k]=B[k];
}*/
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

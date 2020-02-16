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
void merge(int arr[], int l, int m, int r);

int tot_segnali = 0;
volatile bool continua = true; // il perche' della keyword volatile lo vediamo a lezione

// funzione che viene invocata quando viene ricevuto un segnale USR1 USR2 o INT (Control-C)
void handler(int s)
{
   if(s==SIGUSR1)
    {
        tot_segnali++;
        printf("Segnale %d ricevuto dal processo %d\n", s, getpid());
    }

}

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
  pid_t pid , pidpadre ;
  pidpadre=getpid();
  // creazione array di memoria condivisa
  shmid = shmget(IPC_PRIVATE,n*sizeof(int),0600);
  if(shmid == -1) { perror("shared memory allocation"); exit(1);}
  int *a = shmat(shmid,NULL,0); // ora a punta all'array di memoria condivisa
  // visualizza pid per controllo memoria condivisa
  printf("Il pid di questo processo e': %d, l'id della memoria: %d\n",getpid(),shmid);
  // creazione array random
  int *array= random_array(n);
  for(int i=0;i<n;i++)
      a[i] = array[i];
  struct sigaction sa;
  sa.sa_handler= handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags= SA_RESTART;
  sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
 // sigaction(SIGUSR2,&sa,NULL);  // handler per USR2
  //sigaction(SIGINT,&sa,NULL);
  // creazione processo figlio
  pid= xfork(__LINE__, __FILE__);
  // codice processo figlio
  if(pid==0)
  {
    // detach memoria condivisa
    array_sort(&a[n/2],n-n/2);
    if (!check_sort(&a[n/2],n-n/2)){perror("Figlio non ha ordinato l'array");exit(1);}
    e = shmdt(a);
    if(e<0) {perror("shmdt"); exit(1);}
    kill(pidpadre,SIGUSR1);
    exit(0);
  }
  // codice processo padre
  // aspetta che abbia finito il figlio
  while(tot_segnali<1)
  {
      sleep(1);
  }
  array_sort(a, n/2+1);
  if (!check_sort(a,n/2)){perror("Padre non ha ordinato l'array");exit(1);}
  printf("\n---------ARRAY CONDIVISO PRIMA DELLA MERGE--------\n");
  for (int i = 0 ; i<n ; i++)
  {
    printf("%d\n",a[i]);
  }
  // detach e rimozione memoria condivisa

  merge(a,0,n/2,n-1);
  printf("\n---------ARRAY DOPO MERGE--------\n");
  for (int i = 0 ; i<n ; i++)
    printf("%d\n",a[i]);
  puts(check_sort(a,n)? "ok\n" : "errore\n");

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

//merge della Montani 'sukia wea'
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include "xerrors.h"
#include "xerrors.c"

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


int cerca_lesbig(int *array, int n , int *lesser)
{
    int les = 0;
    int big=0;
    for (int i = 0 ; i<n ; i++)
    {
        if (array[i]<RAND_MAX/2)
        {
            les++;
        }
        else
        {
            big++;
        }
    }
    *lesser= les;
    return big;
}

int main (int argc , char **argv)
{
    if(argc!=2) {
    printf("Uso\n\t%s limite numprocessi\n", argv[0]);
    exit(1);
  }
    int n = atoi(argv[1]);
    assert(n>0 );

///CREAZIONE ARRAY INIZIALE CON NUMERI RANDOM
    int *array = random_array(n);
    int e ;
///crea zona di memoria condivisa
    int *a , shmid;
    shmid = shmget(IPC_PRIVATE, n *sizeof(int),0600);
    if (shmid ==-1){perror("Shared memory allocation"); exit(1);}
    a = shmat(shmid, NULL, 0); ///ora a punta all'array di memoria condivisa
    assert(a!=NULL);
    ///Ora l'array non è più distinto ma condiviso tra processi padre e figlio

  // crea processi
   pid_t pid;

  ///CREO PROCESSO FIGLIO
    pid = xfork(__LINE__,__FILE__);
    if (pid==0)
    {
      //fprintf(stderr,"F Figlio %d con pid %d cerca fra %d e %d\n",1,getpid(), a,b);
      int j = 0;

///CREO ARRAY PER IL FIGLIO
      for (int i = 0 ; i<n; i++)
      {

          if(array[i]>=RAND_MAX/2){array[j++]=array[i];}
          array_sort(array,j);
          assert(check_sort(array,j));
          for (int i = 0 ; i<j ; i++)a[n-j+i]= array[i];
          e = shmd(a);
          exit(0);
      }

    }
    int j = 0;
    for (int i = 0 ; i<n ; i++)if (array[i]<RAND_MAX/2)array[j++] = array[i];
    array_sort(array,j);
    assert(check_sort(array,j));

    for ( int i = 0 ; i<j ; i++) a[i]=array[i];
    pid = xwait(NULL,__LINE__,__FILE__);
    puts("%s\n",check_sort(a,n)? "OK ORDINATO \n" : "Errore\n");

   return 0;
}

///shmsort 25

/*
ipcs -m

ipcrm -m 1835020 --> elimino pezzo di memoria condivisa
*/


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
     if(array == NULL){perror("Errore crezione array");exit(1);}
    printf("\n-----ARRAY INIZIALE-----\n");
    for (int i =0 ; i<n ; i++)
    {
        printf("%d\n",array[i]);
    }


  // crea processi
   int e;
   int lesser;
   int bigger = cerca_lesbig(array, n, &lesser);

   printf("\nRAND_MAX: %d\nBIGGER: %d\nLESSER : %d\n",RAND_MAX/2, bigger,lesser);

   int *figlio= (int *)malloc(sizeof(int )*bigger);
   if(figlio == NULL){perror("Errore crezione array");exit(1);}

   int *padre= (int *)malloc(sizeof(int)*lesser);
   if(padre == NULL){perror("Errore crezione array");exit(1);}

   int *finale= (int *)malloc(sizeof(int)*n);
   if(finale == NULL){perror("Errore crezione array");exit(1);}

   pid_t pid;

  /// CREO PIPE
    int up[2];
    xpipe(up,__LINE__,__FILE__);

  ///CREO PROCESSO FIGLIO
    pid = xfork(__LINE__,__FILE__);
    int index = 0;
    if (pid==0) {
      //fprintf(stderr,"F Figlio %d con pid %d cerca fra %d e %d\n",1,getpid(), a,b);

///CREO ARRAY PER IL FIGLIO
      for (int i = 0 ; i<n; i++)
      {
          if(array[i]>=RAND_MAX/2)
          {
            figlio[index]=array[i];
            index ++;
          }

      }
///ORDINO FIGLIO
      array_sort(figlio,index);
      if (check_sort(figlio,index)==false)
      {
          perror("Errore ordinamento figlio");
          exit(1);
      }

///STAMPO FIGLIO ORDINATO
      printf("\n-----FIGLIO----\n");
       for (int j =0 ; j<index ; j++)
    {
        printf("%d\n",figlio[j]);
    }
      close(up[0]);

///SCRIVO ARRAY FIGLIO ORDINATO IN PIPE
      e  = write(up[1],figlio,sizeof(int)*bigger    );
      assert(e==sizeof(int)*bigger);
      free(figlio);
      close(up[1]);
      exit(0);
    }

  // codice del processo padre
  // legge i risultati dalla pipe
  close(up[1]);

///CREO ARRAY PER IL PADRE
  int indice= 0;
  for (int z = 0; z<n ; z++)
  {
      if(array[z]<RAND_MAX/2)
          {
            padre[indice]=array[z];
            indice++;
          }

  }
///ORDINO IL PADRE
  array_sort(padre,indice);
  if (check_sort(padre,indice)==false)
      {
          perror("Errore ordinamento padre");
          exit(1);
      }

///STAMPO PADRE ORDINATO
  printf("\n-----PADRE-----\n");
   for (int ind= 0 ; ind<indice ; ind++)
  {
      printf("%d\n",padre[ind]);
  }

///METTO NELLE PRIME POSIZIONI DELL'ARRAY FINALE IL PADRE ORDINATO
  finale = padre;

 // while(true) {
    //int x;
    e = read(up[0],&finale[indice],sizeof(int)*bigger); //Leggo gli interi dell'array figlio scritti in pipe e li assegno alla variabile 'x'
    if(e==0) {perror("Errore lettura");exit(1);};
    if(e!=sizeof(int)*bigger) {perror("Errore lettura pipe"); exit(1);}

    //finale[indice]=x;
    //indice++;

  //}

///STAMPA ARRAY FINALE
  printf("---------------FINALE------------\n");
  for (int i =0 ; i<n ; i++)
    {
        printf("%d\n",finale[i]);
    }
/// Si può utilizzare fprintf(stderr,"%s\n",check_sort(array,n)? "OK ORDINATO\n" : "Errore\n");
  if(check_sort(finale,indice))
            printf("\nOK! - FINALE ORDINATO\n");
  else
        {perror("FINALE NON ORDINATO");exit(1);}
   //free(padre);
   //free(finale);

   return 0;
}


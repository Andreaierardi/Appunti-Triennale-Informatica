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
#include "xerrors.h"
#include "xerrors.c"


void mt_mergesort(int array[], int n, int limite);
void merge(int a[], int m,  int n) ;

// genera array di n elementi con interi random tra 0 e 1999

int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  if(a==NULL) die("errore allocazione");
  for(int i=0;i < n;i++)
    a[i] = (int) random() % 2000;
  return a;
}

// verifica che array a[0..n-1] sia ordinato 
bool check_sort(int a[], int n)
{
  for(int i=0; i < n-1; i++)
     if(a[i] > a[i+1]) return false;
  return true;
}

// funzione di confronto tra interi passata a qsort
int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}


// struct contenente i parametri di input e output di ogni thread
typedef struct {
 
  int *array;
  int n;
  int limite;
  int *b;
} dati;


///BODY DEL THREAD   
void *tbody(void *arg)
{
	//Associo la struttura dati passata dal main a quella del thread
  dati *a = (dati *)arg;
  int n = a->n;
  
  //Da 0 a n/2 ci pensa il thread a gestire la parte dell'array dalla posizione 0 alla posizione n/2
  for(int i = 0 ; i<n/2; i++)
		a->b[i] = a->array[i];
	///Richiamo di funzione dal thread
   mt_mergesort(a->b,n/2,a->limite);
 
//chiusura del thread
  pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	//Verifico che i parametri in input siano tre
  if((argc!=3)) {
    fprintf(stderr,"USO:  %s n limite\n\n",argv[0]);
    exit(1);
  }
  int n= atoi(argv[1]);
  int limite = atoi(argv[2]);

//Se uno dei due valori è minore di 1 errore!
  if(n<1 || limite <1) {
    die("Input non valido (main)");  }

 

  // genera array random
  int *array = random_array(n);

  ///------Richiamo funzione-----
  mt_mergesort(array,n,limite);


//Stampo array ordinato
   printf("============ARRAY ORDINATO=========\n");
   for (int i = 0; i<n ;i++)
		printf("ordinato : %d\n",array[i]);

     
  ///-------Controllo che array sia ordinato-------
  
  if(check_sort(array,n))
    fprintf(stderr,"Sort OK\n");
  else
    fprintf(stderr,"Sorting fallito\n");
  return 0;
}

///METODO RICHIESTO DALLA CONSEGNA
void mt_mergesort(int array[], int n, int limite)
{
   dati a;
   pthread_t t;

///PASSO BASE IN CUI ORDINO UNA PARTE DELL'ARRAY
   if(n<=limite) 
    qsort(array,n,sizeof(int),intcmp);

///PASSO RICORSIVO
    else {
		 // alloca due array b e c di lunghezza n/2 e n-n/2 
      // in parallelo:
      //   copia i primi n/2 elementi di a in b
      //   invoca mt_mergesort(b,n/2,limite)
      //   copia i secondi  n-n/2 elementi di a in c
      //   invoca mt_mergesort(c,n-n/2,limite)
      // quando entrambi i thread hanno finito   
      // esegui il merge di b[] e c[] in a[]
      // dealloca b[] e c[]
		int *b = (int *) malloc(n/2*sizeof(int));
		int *c = (int *) malloc((n-n/2)*sizeof(int));
		//Passo i dati al thread in modo che possa utilizzarli nel suo body
        a.array=array;
        a.n = n;
        a.limite = limite;
        a.b = b;
		printf("CREO THREAD\n");
		///Creo thread ausiliario per lo svolgimento della merge_sort
        xpthread_create(&t, NULL, tbody, (void *) &a,__LINE__,__FILE__);
      
      //Il thread dovrà svolgere i seguenti compiti:
       //   copia i primi n/2 elementi di a in b
      //   invoca mt_mergesort(b,n/2,limite)
      
      //Il padre invece 
          //   copia i secondi  n-n/2 elementi di a in c
      //   invoca mt_mergesort(c,n-n/2,limite)
      
      //Quindi qui avviene la copia di n-n/2 elementi di a in c
       int ind = 0;
	   for (int i = n/2; i<n ;i++)
			c[ind++] = array[i];
     	
     	//   invoca mt_mergesort(c,n-n/2,limite)
        mt_mergesort(c,n-(n/2),limite);
        
        //Aspetta che il thread ausiliario abbia finito tutti i suoi ordinamenti
        pthread_join(t, NULL);
	
	//Inserisco i valori dell'array b nelle prime n/2 posizioni di a
        for(int i = 0 ; i<n/2; i++)
			array[i] = a.b[i];
			
	//Inserisco i valore dell'array c dalla posizione n/2 a n di a.
		int index =0 ;
		for(int i = n/2; i<n;i++)
			array[i] = c[index++];
			
	//Stampo il premerge, quindi ho un array composto da due parti: la prima ordinata da 0 a N/2, la seconda ordinata da N/2 a N.
		for (int i = 0; i<n ;i++)
			printf("pre merge : %d\n",array[i]);
	//A questo punto devo fare il merge dei due array e utilizzo una funzione di merge
	  //Passo l'array da cui fare il merge, le lunghezze dei due array e l'array 
	  merge(array,n/2,n-(n/2));
	
	  
	//Dealloco i due array
      free(b);
	  free(c);
      }
    
} 

///FUNZIONE MERGE CHE SI PUÒ TROVARE ANCHE SU INTERNET DATO CHE E' UN ALGORITMO COMUNE E CHE ABBIAMO FATTO ANCHE NEL CORSO DI ALGORITMI1
///ALL'ESAME LA SI PUÒ PORTARE TRANQUILLAMENTE


void merge(int a[], int m, int n) {
	//Dichiaro tre variabili da utilizzare in seguito
  int i, j, k;
  //Dichiaro un array sorted che conterrà il risultato finale
  int sorted[m+n];
  j = k = 0;
  //b conterrà la seconda parte dell'array a in modo da "spezzare" a in due array
  int b[n];
  for(int i = 0 ; i<n;i++)
		 b[i]=a[m+i];
		 
//Inizio merge
///E' lo stesso problema che si presentava con le due liste: L1 != NULL e L2 != NULL (j<m e k<n) allora visito le due liste
///Se L1 == NULL (j==m  quindi ho aggiunto la fine dell'array) allora aggiungo tutti i valori di L2 fino alla fine(quindi aggiungo b[k])
///Se L2== NULL (k==n ovvero l'else - quindi ho aggiunto la fine dell'array) allora aggiungo tutti i valori di L1 fino alla fine(quindi aggiungo a[j])

  for (i = 0; i < m + n;) {
	  //Se i valori di j minore di m(limite dimensione del primo array) e k<n (dimensione del secondo array)
    if (j < m && k < n) {
      if (a[j] < b[k]) { //Allora controllo che se il valore di a[j] (primo array) < b[k] (secondo array)
        sorted[i] = a[j]; //Aggiungo a[j] all'array finale e scorro la posizione di 1(j++)
        j++;
      }
      else { //Altrimenti aggiungo b[k] a quello finale e incremnto l'indice di 1
        sorted[i] = b[k];
        k++;
      }
      i++;
    }
    else if (j == m) { //Se ho raggiunto 
      for (; i < m + n;) {
        sorted[i] = b[k];
        k++;
        i++;
      }
    }
    else {
      for ( ;i < m + n;) {
        sorted[i] = a[j];
        j++;
        i++;
      }
    }
  }
 // FINE MERGE
 
 //RICOPIO I VALORI DI SORTED IN A DATO CHE SARÀ L'OUTPUT FINALE CHE OTTERREMO
  for (int i = 0  ; i<n+m; i++)
	a[i] = sorted[i];
}

/*
 * Programma per il calcolo multithread 
 * della somma dei numeri primi fino ad n
 * */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>      
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>


// funzione per stabilire se n e' primo  
bool primo(int n)
{
  if(n<2) return false;
  if(n%2==0) return (n==2);
  for (int i=3; i*i<=n; i += 2)
      if(n%i==0) return false;
  return true;
}

// struct contenente i parametri di input e output di ogni thread 
typedef struct {
  int inizio;// input
  int fine;
  int quanti; // output
  long somma;
} dati;


// funzione eseguita dal thread
void *tbody(void *a)
{  
  dati *arg = (dati *)a; 
  fprintf(stderr,"Thread cerca da %d a %d\n",arg->inizio,arg->fine);
  arg->quanti = 0;
  arg->somma = 0;
  for (int j=arg->inizio;j<arg->fine;j++)
    if(primo(j)) {
      arg->quanti++;
      arg->somma += j;
    }
  pthread_exit(NULL); 
}


int main(int argc, char *argv[])
{
  // leggi input
  if(argc!=3) {
    printf("Uso\n\t%s limite numthread\n", argv[0]);
    exit(1);
  }
  int n = atoi(argv[1]);
  int p = atoi(argv[2]);
  assert(n>10 && p>0);
  int i,e;
  pthread_t t[p];
  dati argomenti[p];


  // creazione di p thread con il loro range di numeri
  for(i=0;i<p;i++) {
    argomenti[i].inizio = i*(n/p);
    argomenti[i].fine =  (i==p-1) ? n : (i+1)*(n/p);
    pthread_create(&t[i], NULL, tbody, (void *) &argomenti[i]);
    assert(e==0);
  }
  fprintf(stderr,"%d thread creati\n", p);
  
  // attende terminazione thread e calcola somma dei primi
  int quanti=0;
  long somma = 0;
  for(i=0;i<p;i++) {
    e = pthread_join(t[i], NULL);
    if(e==0) {
      fprintf(stderr,"Thread %d terminato\n",i);
      quanti += argomenti[i].quanti;
      somma += argomenti[i].somma;
    }
    else 
      fprintf(stderr,"Errore join %d\n",e);
  }
  fprintf(stderr,"Trovati %d primi con somma %ld\n",quanti,somma);
  return 0;
}

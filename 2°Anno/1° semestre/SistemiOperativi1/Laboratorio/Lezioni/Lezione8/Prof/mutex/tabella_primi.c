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

#define DIMTABELLA 10000000

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
  int inizio;   // input
  int fine;
  int *tab;     // puntatore alla tabella dei primi 
  int *pmessi;  // puntatore a messi
  pthread_mutex_t *pmutex_tabella; // mutex per regolare l'accesso alla tabella
  int quanti;   // output
  long somma;
} dati;


// funzione eseguita dal thread
void *tbody(void *a)
{  
	int e=0;
  dati *arg = (dati *)a; 
  fprintf(stderr,"Thread cerca da %d a %d\n",arg->inizio,arg->fine);
  arg->quanti = 0;
  arg->somma = 0;
  for (int j=arg->inizio;j<arg->fine;j++)
    if(primo(j)) {
      arg->quanti++;
      arg->somma += j;
      if(*(arg->pmessi) >= DIMTABELLA) {
        fprintf(stderr,"Tabella piena\n"); exit(1);
      }
      // zona critica: tutti i thread accedono a messi e tabella
      // se le istruzioni mutex_lock e mutex_unlock sono comemntate 
      // la tabella puo' non essere riempita correttamente  
      // e = pthread_mutex_lock(arg->pmutex_tabella);
      assert(e==0);
      arg->tab[*(arg->pmessi)] = j;
      *(arg->pmessi) += 1;
      // e = pthread_mutex_unlock(arg->pmutex_tabella);
      assert(e==0);
      // fine zona critica
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
  int *tabella = malloc(DIMTABELLA*sizeof(int));
  assert(tabella!=NULL);
  int messi = 0;
  pthread_mutex_t mutex_tabella = PTHREAD_MUTEX_INITIALIZER;

  // creazione di p thread ognuno con un range di numeri
  for(i=0;i<p;i++) {
    argomenti[i].inizio = i*(n/p);
    argomenti[i].fine =  (i==p-1) ? n : (i+1)*(n/p);
    argomenti[i].tab = tabella;
    argomenti[i].pmessi = &messi;
    argomenti[i].pmutex_tabella = &mutex_tabella;
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
  e = pthread_mutex_destroy(&mutex_tabella);
  assert(e==0);
  fprintf(stderr,"Trovati %d primi con somma %ld\n",quanti,somma);
  // --- ricalcolo la somma dei primi guardando la tabella
  somma = 0;
  for(int i=0;i<messi;i++) 
    somma += tabella[i];
  fprintf(stderr,"Dentro la tabella trovati %d primi con somma %ld\n",messi,somma);  
  return 0;
}

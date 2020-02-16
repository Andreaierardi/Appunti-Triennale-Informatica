#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*
 * Per poter usare la stessa funzione di sort con oggetti diversi 
 * il C usa dei puntatori generici, quindi il tipo  void *
 *  
     void qsort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *));  

   il tipo  __compar_fn_t e' definito come il tipo dell'ultimo argomento
   cioe' il puntatore a una funzione che prende come input due const void *
   e restituisce un intero  
 */

// funzione con prototipo non corretto
// devo usare il cast a __compar_fn_t dentro la qsort
int lex(char **x, char **y) {
  return strcmp(*x,*y);
}

// funzione con prototipo corretto
// deve usare il cast internamente
int lunghezza(const void *x, const void *y) {
  const char **sx = (const char **) x;
  const char **sy = (const char **) y;
  return strlen(*sx) - strlen(*sy);
}


int main(int argc, char *argv[]) {

  int n = argc-1;
  char **a = argv + 1;
  assert(n>1);

  // A differenza di Python e Java
  // in C non esiste un ordinamento di default
  // anche per ordinare un array di interi e' necessario
  // passare una funzione di confronto
  // vedi esempio fatto a lezione

  // passo la funzione che confronta lessicograficamente 
  puts("Ordinamento stringhe lessicografico");
  qsort(a,n,sizeof(a[0]), (__compar_fn_t) lex);
  for(int i=0;i<n; puts(a[i++])) ;
  
  // passo la funzione che confronta le lunghezze
  puts("Ordinamento per lunghezza");
  qsort(a,n,sizeof(a[0]), lunghezza);
  for(int i=0;i<n; puts(a[i++])) ;
  
  return 0;
}

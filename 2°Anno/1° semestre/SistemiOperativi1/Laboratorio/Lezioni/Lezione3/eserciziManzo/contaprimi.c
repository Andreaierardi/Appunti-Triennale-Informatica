#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

// programma per il conteggio di numero dei primi in un
// itervallo usando un unico processo e le tecniche di Prog 1


// restituisce true/false a seconda che n sia primo o composto
bool primo(int n);

// conta quanti sono i primi tra argv[1] (compreso) e argv[2] (escluso)
int main(int argc, char *argv[]) {
  if(argc!=3) {
    printf("Uso:\n\t%s n1 n2\n",argv[0]);
    exit(1);
  }
  int n0 = atoi(argv[1]);
  int n1 = atoi(argv[2]);
  assert(n0>0 && n1>=n0);
  int tot=0;
  
  for(int i=n0;i<n1;i++)
    if(primo(i))tot++;
  printf("Numero primi p tali che  %d <= p < %d è: %d\n",n0,n1,tot);
  return 0;
}

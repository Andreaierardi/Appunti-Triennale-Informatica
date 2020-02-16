
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
#include <string.h>
#define SIZE 100
void leggi_interi(char *nome);

void leggi_interi(char *nome)
{   int somma=0;
    // apre il file in lettura
    FILE *f = fopen(nome,"r");
    // verifica che non ci siano errori
    if(f==NULL) {
      printf("Impossibile aprire il file %s\n", nome);
      return;
    }
    // definisce un buffer di 100 caratteri
    char s[SIZE], *r;
    // legge una riga alla volta fino alla fine del file
    while(true) {
      r = fgets(s,SIZE,f);
      // verifica se ci sono altre righe
      if(r==NULL)
        break; // non ci sono altre righe esco dal while
      // stampa la lunghezza della linea corrente
      somma+=atoi(s);
    }
    printf("\n%d\n",somma);
    fclose(f); // chiudo il file
    return;
}


int main(int argc, char *argv[])
{
    leggi_interi(argv[1]);
    return 0;
}

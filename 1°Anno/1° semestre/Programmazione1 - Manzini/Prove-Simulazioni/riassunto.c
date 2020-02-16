#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare la funzione assert
void frequenze(char *nome);

int main(int argc, char *argv[])
{

  if(argc>1)
    // visualizza le lunghezze delle righe del file argv[1]
    frequenze(argv[1]);
  return 0;
}


void frequenze(char *nome)
{

    // apre il file in lettura
    FILE *f = fopen(nome,"r");
    // verifica che non ci siano errori
    if(f==NULL) {
      printf("Impossibile aprire il file %s\n", nome);
      return;
    }
    // definisce un buffer di 100 caratteri
    char s[123], *r;
    // legge una riga alla volta fino alla fine del file
    for (int i=0;i<=sizeof(s);i++){
        char t = s[i];
        printf("%s\n",t);
    }
    fclose(f); // chiudo il file
    return;
}

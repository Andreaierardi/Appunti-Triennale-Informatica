#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>

void ciao(char *nome)
{
    FILE *f= fopen(nome,"r");
    if (f==NULL){
        printf("Impossibile aprire il file");
        return ;
    }
    // FUNZIONE

    fclose(f);
    return;
}

int main (int argc, char *argv[]){
    if (argc>1)
        //ciao(argv[1]);
            ;
    if (argc>2)
        //ciao(argv[2])
            ;
    return 0;
}

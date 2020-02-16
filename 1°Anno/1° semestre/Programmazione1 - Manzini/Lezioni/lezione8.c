#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
#include <string.h>

int main (int argc, char *argv[]){

    char cognome[10], nome[10];
    int letti;

    printf("Indirizzi: nome=%ld cognome=%ld\"", (long) nome, (long) cognome);
    printf("Inserisci nome: ");
    letti = scanf("%9s",nome); // legge i primi nove e ci mette lo "/0" in fondo  termina stringa
    printf("Valori letti: %d\n", letti);
    printf("Inserisci cognome: ");
    letti = scanf("%s",cognome);
    printf("Valori letti: %d\n", letti);
    // nome[1]="X"; sostituisce il carattere X
    printf("Ti chiami (%s %s)\n", nome , cognome);

    return 0;
}


/*
   Cognome punta alla posizione 1824
   Il nome punta alla posizione 1840

   dopo il 1840 comincia l'array

   con scanf ho problemi se metto spazii (per esempio "pier luigi")
   prenderà luigi come cognome

   se scrivo stringa troppo lunga sostiuisce il nome con la continuazione del cognome
   (scrive 10 posizioni e poi altre 10 e le restanti le ha sostiute dentro la stringa nome)


   scanf("%d",&n); // leggo da terminale un intero

   fscanf(f,"%d",&n); // leggo dal file f un intero

*/



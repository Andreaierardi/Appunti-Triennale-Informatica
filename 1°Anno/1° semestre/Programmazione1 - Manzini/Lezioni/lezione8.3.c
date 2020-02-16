#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
#include <string.h>


// esempio scrittura su file
void scrivi_quadrati(char *nome, int n)
{
    // apre il file in scrittua
    FILE *f = fopen(nome,"w");  /// a per fare append(aggiungi)
    // verifica che non ci siano stati errori in apertura
    if (f==NULL){
        printf("Impossibile prire il file!");
        return ;
    }
    //scrive sul file i quadrati dei numeri tra 1 e n
    for (int i=1; i<=n;i++){
        // notare he la scrittura è molto simile alla printf
        fprintf(f,"%d al quadrato guguale a %d\n",i,i*i);
    }
    // chiude il file
    fclose(f);  //chiudo il file
    return;
}

/*

NOTA: per tornare a leggere il file dall'inizio
usare rewind(f);
in python f.seek(0);

*/
#define SIZE 100

void visualizza_lunghezze_righe(char *nome)
{
    FILE *f=fopen(nome,"r");     /// SONO PUNTATORI AI MIEI FILE
    if (f==NULL){
        printf("Impossibile aprire il file %s\n", nome);
        return;
    }
    FILE *g=fopen("copia","w");     /// SONO PUNTATORI AI MIEI FILE
    if (g==NULL){
        printf("Impossibile aprire il file copa %s\n", nome);
        return;
    }
    char s[SIZE], *r;
    while(true){
        r = fgets(s,SIZE,f);
        if(r==NULL)
            break;

        // stampa su g riga + lunghezza
        fprintf(g,"%s %d\n",s,(int)strlen(s)+1);  //%s, s non va bene perchè mi va a capo perchè stampa
    }
    return;
}

///CONCATENARE STRINGHE CON UNA FUNZIONE

// char s[100];
// snprintf(s,100,"prova.%d.txt",n);   //invece di stampare a schermo, la scrive in un array


void esercizio(char *nome){

 //apre il file in lettura
    FILE *f=fopen(nome,"r");     /// SONO PUNTATORI AI MIEI FILE
    // verifica che non ci siano errori
    if (f==NULL){
        printf("Impossibile aprire il file %s\n", nome);
        return;
    }

// definisce un buffer di 100 caratteri

    char s[SIZE], *r;

    //legge una riga alla volta fino alla fine del file
    while(true){

        r = fgets(s,SIZE,f); /// funzione che legge una riga dal file
                            // deve esserci una zona di memoria grande almeno di 99 caratteri(con "/0" finale)
                            // dove scrivere i caratteri da inserire nel file


        // verifica se ci sono altre righe
        if(r==NULL)
            break; //non ci sOno altre righe

        // stampa la lunghezza della linea corrente
        printf("Lunghezza: %d\n",strlen(s));
    }
    return;
}



int main(int argc, char *argv[]){

    if (argc>1)
        esercizio(argv[1]);
    if (argc>2)
        scrivi_quadrati((argv[2]),10);
    return 0;
}

/* SI PUò LEGGERE ANCHE CON FSCANF

scanf("%d",&n); // leggo da terminale un intero

fscanf(f,"%d",&n); // leggo dal file f un intero */

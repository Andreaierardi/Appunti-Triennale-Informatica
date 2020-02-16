/*scrivere programmi che usano processi e thread
Threads tra di loro si possono influenzare

Comando man --> cercare istruzioni col terminale

man printf uso chiamate di sistema della printf della shell
printf del C --> man 3 printf
Vi sono più nomi perchè vi sono più printf legate a stringhe e file.

#include <stdio.h> va messo nel file sorgente --> Quando non c'è prototipo della funzione dà alla funzione una RETURN di un intero assegnandogli un prototipo di default
quando si accorge che comunque gli passiamo delle stringhe ci darebbe degli errori poichè non corrisponde al prototipo( Perchè non è stato dichiarato)

--------------------------
man fread

fread, fwrite
scrivere/leggere file binari

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
dimensione singolo elemento, numero oggetti di dati , FILE passato --> valori letti scritti nel ptr passato nel primo argomento

Se io leggo un unico valore devo passsargli una zona di memoria con un solo valore.  (devo mettere & per ripassare valore)


alcuni tipi di variabile sono size_t --> quello è un tipo che specifica il tipo per indicare la dimensione degli oggetti.

Guardare per ogni funzione il RETURN VALUE perchè dice cosa restituisce la funzione ma anche perchè c'è  sempre un modo per dire
se si è verificato un errore in quella funzione.
Messaggi di errore sono molto utili!
GESTIONE DEGLI ERRORI E' OBBLIGATORIA

per ex in fread() --> RETURN numero di oggetti letti dal file , questo numero non è detto che sia uguale al numero di bytes letti,
è uguale se la dimentizione del singolo oggetto è 1.

Voglio leggere oggetti di dimensione 4.  10 oggetti di dimensione 4.  40 bytes quindi ma fread--> RETURN 10 (n oggetti)
OUTPUT fread da verificare se == 10
se < 10 non è riuscito a leggerli tutti --> non è andato a termine come speravo     ---- CONTROLLI SONO IMPORTANTI

Se fread RETURN 0 --> non ha letto nulla perchè file vuoto oppure c'è stato un ERRORE (cancellato da un altro ecc..)
feof  e ferror aiutano a determinare un controllo migliore
-----------------------------
Secondo strumento essenziale --> IL COMPILATORE

ERRORI-> compilazione non terminata
WARNING -> compilazione eseguita ma ci sono dei problemi

MAI ignorare un warning di cui non si è capito completamente il significato

gcc  -Wall  -std=c99 -g -O prog.c -o prog
------------------------------
TOOL VALGRIN
Mi suggerisce errori di programmazione e di realizzazione

-----------------------------
gdp DEBUGGER
*/

//ESERCIZIO 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void scrivi();

int main (int argc, char **argv)
{
    int n = argc -1;


    scrivi();

    return 0;


}
void scrivi()
{
     FILE *f= fopen("scrivibin","wb");


      for (int i = 1 ; i<6; i++)
      {
           write(fileno_unlocked(f), &i,sizeof(i));
      }

    fclose(f);
    FILE *fp = fopen("scrivibin","rb");

    int l=0;
    for (int i = 1; i<6; i++)
    {
         read(fileno_unlocked(f),&l,  sizeof(int));
         printf("%d --  %d\n",l, i );
    }


}

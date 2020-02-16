#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
#include <string.h>

//FUNZIONE CONFRONTO TRA STRINGHE
int main(int argc, char *argv[])
/// l'importa in questo programma è il segno per vedere se la stringa è maggiore o minore
/// il numero dipende da macchina a macchina quindi non è importante
{
    // confronto argv[1] con argv[2]
    if(argc!=3)
    {
        printf("Uso: %s stringa1 stringa2\n",argv[0]);
        return 1;
    }
    int c= strcmp(argv[1],argv[2]);
    printf("%d\n",c);
    if (c>0)
        printf("%s\n",argv[2]);
    if (c<0)
        printf("%s\n",argv[1]);
    return 0;
}
// funzione che stampa l'argomento più piccolo lessicograficamente


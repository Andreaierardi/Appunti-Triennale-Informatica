#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <math.h>
#include <string.h>

/// sprintf(char *str, const char *format)  --> posso scrivere una stringa dove voglio(
/// snprintf(char *str, size_t size, const char*)
/*
    con snprintf determino una posizione dove allocale la stringa e se supera cancella tutto cioò che c'è dopo
    mentre con sprintf mi da segmentation fault.

    #define SIZE 100
    char s[SIZE];
    snprintf(s,SIZE,"prova.%d.txt",i);
    f = fopen(s,"w");

 */
 /// con int k= snprintf(s,SIZE,"prova.%d.txt",i)     K---> mi da il numero di caratteri scritti(come strlen)

 /* HO UN STRINGA S CON DENTRO "ABC74IU3\0"

    mi piacerebbe aggiungerci qualcosa con snprintf -->per esempio "1027"

    0 1 2 3 4
    c i a o \0
        |
        |
        v
    quindi devo far partire la seconda stringa dalla posizione 4 con \0
    */
/**
   #define SIZE 100
    char s[SIZE];
    snprintf(s, SIZE, "Combinazione della cassaforte:");

    // voglio aggiungere n convertito in stringa
    n = calcola_combinazione();

    snprintf(&s[strlen(s)], SIZE-strlen(s), "%d",n)*/

    // non posso passargli s[strlen(s)] da sola perchè è la zona dove punta quindi devo utilizzare la &
    // utilizzo SIZE-strlen(s) in modo che parta dalla posizione 4 di ciao con \0



///FUNZIONE STRCMP
/*

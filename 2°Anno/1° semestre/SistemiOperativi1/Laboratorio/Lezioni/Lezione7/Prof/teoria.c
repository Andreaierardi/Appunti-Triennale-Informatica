#include <stdbool.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "xerrors.h"
#include "xerrors.c"
#include <signal.h>
///THREAD
///Il terzo parametro di applica è un puntatore ad una funzione. Applica prende i due interi e il terzo parametro e applica la funzione.
///Quando chiamo applica non devo utilizzare la '&' sui puntatori perchè me lo fa in automatico
///Il tipo del terzo argomento è dato dall'argomento di  int (*f) (int, int) --> dati due interi mi restituisce un intero
///La funzion qsort  --> primo parametro puntatore a void, num elementi array da ordinare, dim singolo elemento, puntatore ad una funzione che restituisce un intero
///Puntatori a void --> Apparentemente un puntatore ad una variabile che non esiste ---> in realtà sono utilizzati per un puntatore generico.
///Quindi può prendere qualsiasi var puntatore -- qsort si può utilizzare sia per ordinare array di interi, sia di char ecc...
///In questo modo si può definire una sola unica funzione di puntatore generico
///Funzione di confronto --> compare , prende puntatori a void e restituisce un intero per definire qual è il più grande tra i due

/// THREAD --> funzionano con il meccanismo dei puntatori a void
/// man pthread_create (pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
///Compilare con -pthread
///Crea un thread . 3° parametro indica la funzione da far eseguire al thread --> prende come argomento un puntatore a void e restituisce un puntatore a void.
/// Struttura dati --> 'char *s' stringa da passare e 'int len' lunghezza stringa
/// Per ogni stringa passata calcola la lunghezza della stringa tramite un thread
/// in void *tbody ( void *arg) -->  body del thread in cui è scritto il codice per calcolare la lunghezza della stringa e si restituisce il valore tramite EXIT
/// ---------
///Nel main --> creo un array di dati e di thread --- dati[n] , pthread_t t[n]
///Da argv passo le stringhe a dati[n] -->  d[i].s = argv[i+1]
///e = pthread_create ( &t[i] , NULL, tbody , (void *), &d[i]);
/// controllo su e!=0 . Se 0 errore nella creazione di thread
/// Con il (void *) converte in puntatore generico
/// In tbody dati *d = (dati *) arg ---> me lo trasforma da puntatore generico a puntatore che mi serve ( in questo caso di dati, se volessi un int metterei (int *)
///Sleep(2) -- viene fatta in parallelo da tutti i thread ma sì può eliminare ------edo cuore<3
///--------
///attende terminazione del thread
///e =pthread_join (t[i] , NULL) --> aspetto la terminazione del thread passato come primo paramentro. Essendoci un for quindi aspetto un thread per volta
///------
///Se metto 'dati singolo'al posto dell'array non funziona.
///Se dalla main chiamiamo una funzione e dalla funzione chiamiamo un thread --> terminata funzione termina anche il thread
///Quindi bisogna allocare con malloc! In modo tale da non perdere il risultato
///Bisogna tener conto di ciò che è condiviso e ciò che è privato--> bisognerà aggiungere un meccanismo di sincronizzazione

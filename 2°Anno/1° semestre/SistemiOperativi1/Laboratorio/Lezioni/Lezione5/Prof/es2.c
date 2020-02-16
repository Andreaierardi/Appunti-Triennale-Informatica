#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <assert.h>
#include "xerrors.h"
#include "xerrors.c"

/*
 In segnali.c
 Vi è la funzione per l'handler

 Abbiamo due variabili globali
 Quando mando segnale viene eseguito il codice

 lanciando il programma segnali

 Se vuoi mandarmi dei segnali il mio pid è : 1948
 --> si blocca
 Con CTRL - C --> termina

 ___ Segnale 2 ricevuto dal processo 1948


 ---- devo creare nuovo terminale perchè il cristo me l'ha bloccato

 Se chiamo kill -10
 --> gli mando un segnale di 10

 Se chiamo kill -11
 --> gli mando un segnale di segmentation fault

Posso mandare segnali anche dal programma stesso.
E' PERICOLOSO!!!
in segnali.c

 printf(..)
 -->kill(getpid(), SIGUSR1);    //Mando segnale SIGUSR1 a se stesso
 if ...


Viene richiamato handler e a quel punto viene stampato --> segnale 10 ricevuto
Va in LOOP!


Se metto in if(s== SIGURSR2)
{
    kill(getpid(), SIGUSR1);
    ...
}

Non va in loop --> se premo CTRL C mi da segnale 2 poichè CTRL - C è segnale 2

Se metto kill -10 in terminale secondario mi da segnale 10

*/
///man kill
///kill -l --> useremo solo segnale 10 e 12
///kill -10 -->SIGSUR1
int main (int argc , char **argv)
{

   struct sigaction sa;
   //nella variabile sa viene indicato il numero del segnale
   ///funzione handler--> specifico funzione quando arriva il segnale
   sa.sa_handler= handler;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags= SA_RESTART;
   ///fai ciò che è definito in sa
   sigaction(SIGUSR1, &sa, NULL);
   sigaction(SIGUSR2, &sa, NULL);
   sigaction(SIGINT, &sa, NULL);

   ///visualizza pid
    printf("Se vuoi mandarmi dei segnali il mio pid è : %d\n",getpid());

    ///attende i segnali
    continua = true;
    while(continua)
    {
        pause();
    }
    printf("Ricevuti: %d segnali \n", tot_segnali);
   return 0;
}


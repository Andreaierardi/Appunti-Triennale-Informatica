#define _GNU_SOURCE
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>


// variabili globali utilizzate dal mail e dal signal handler
int tot_segnali = 0;
volatile bool continua = true; // il perche' della keyword volatile lo vediamo a lezione

// funzione che viene invocata quando viene ricevuto un segnale USR1 USR2 o INT (Control-C)
void handler(int s)
{
  tot_segnali++;
  printf("Segnale %d ricevuto dal processo %d\n", s, getpid());
  if(s==SIGUSR!) {
    // dopo aver fatto girare il programma la prima volta
    // s-commentate l'istruzione kill e osservate cosa succede
    // kill(getpid(),SIGUSR1);
    continua = false;
  }
}



int main(int argc, char *argv[])
{
  // definisce signal handler
  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);     // setta a "insieme vuoto" sa.sa_mask maschera di segnali da bloccare
  sa.sa_flags = SA_RESTART;     // restart system calls  if interrupted
  sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
  sigaction(SIGUSR2,&sa,NULL);  // handler per USR2
  sigaction(SIGINT,&sa,NULL);   // handler per Control-C

  // visualizza il pid
  printf("Se vuoi mandarmi dei segnali il mio pid e': %d\n", getpid());

  // entra in loop attendendo i segnali
  continua = true;
  while(continua) { // loop apparentemente senza uscita
    pause();               // questo e' un busy waiting: da evitare assolutamente.  Usare pause() per attendere il segnale
  }
  printf("Ricevuti: %d segnali\n", tot_segnali);
  return 0;
}



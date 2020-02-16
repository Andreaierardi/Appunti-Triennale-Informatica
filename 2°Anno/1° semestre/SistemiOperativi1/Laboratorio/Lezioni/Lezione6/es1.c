#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "xerrors.h"
#include "xerrors.c"
#include <signal.h>

///Usiamo SIGRTMIN --> un segnale real time che è gestito in modo atomico. Non vengono unificati in un unico segnale come SIGRUSR1
///La key word volatile a fianco all'int tot_segnali. Variabile può essere cambiata all'esterno del programma principale ( quindi dall'Handler)
///Ciclo while senza condizioni tiene in busy waiting. Quindi per realizzare attesa che non occupi troppa CPU utilizzo la sleep
///Potremmo mettere anche 20 ma funziona comunque perchè all'arrivo di un segnale la sleep si interrompe
// variabili globali utilizzate dal mail e dal signal handler
int volatile tot_segnali = 0;
volatile bool continua = true; // il perche' della keyword volatile lo vediamo a lezione

// funzione che viene invocata quando viene ricevuto un segnale USR1 USR2 o INT (Control-C)
void handler(int s)
{
  tot_segnali++;
  printf("Segnale %d ricevuto dal processo %d (tot=%d)\n", s, getpid(),tot_segnali);
    // dopo aver fatto girare il programma la prima volta
    // s-commentate l'istruzione kill e osservate cosa succede
    // kill(getpid(),SIGUSR1);
}
bool primo(int n);
int cerca_primi(int i ,int M, int N);

// main
int main(int argc, char **argv)
{
  if(argc!= 3)
  {
    fprintf(stderr,"Uso: nomefile n\n");
    exit(1);
  }
  int M= atoi(argv[1]);
  assert(M>0);
  int N= atoi(argv[2]);
  assert(N>0);

  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);     // setta a "insieme vuoto" sa.sa_mask maschera di segnali da bloccare
  sa.sa_flags = SA_RESTART;     // restart system calls  if interrupted
  sigaction(SIGRTMIN,&sa,NULL);  // handler per USR1


  int e, shmid;
  pid_t pid;

  // creazione array di memoria condivisa
  shmid = shmget(IPC_PRIVATE,N*sizeof(int),0600);
  if(shmid == -1) { perror("shared memory allocation"); exit(1);}
  int *a = shmat(shmid,NULL,0); // ora a punta all'array di memoria condivisa
  // visualizza pid per controllo memoria condivisa
  // creazione processo figlio
  pid_t pidpadre=getpid();
  // codice processo figlio
  for (int i= 0; i< N; i++)
  {
    pid= xfork(__LINE__, __FILE__);
    if(pid==0)
    {

        // detach memoria condivisa
        a[i]=cerca_primi(i,M,N);
        printf("PROCESSO %d--> %d\n",i,a[i]);
        e = shmdt(a);
        if(e<0) {perror("shmdt"); exit(1);}
        int ke = kill(pidpadre,SIGRTMIN);
        assert(ke==0);
        exit(0);
    }
  }

  // codice processo padre
  // aspetta che abbia finito il figlio
  while(tot_segnali<N)
  {
      sleep(1);
  }
  int somma = 0;
  for (int i = 0 ; i<N; i++)somma += a[i];


  // detach e rimozione memoria condivisa
  e = shmdt(a);
  if(e<0) {perror("shmdt"); exit(1);}
  e = shmctl(shmid, IPC_RMID,  NULL);
  if(e == -1) {perror("shmctl"); exit(1);}
  printf("La somma è : %d\n", somma);
  return 0;
}

int cerca_primi(int i ,int M, int N)
{
    int tot = 0;
    for( int j = 0; j<M; j++)
            if (j%(2*N) == (2*i)+1)
                    if (primo(j))
                        tot++;
    return tot;
}
bool primo(int n)
{
  int i;
  if(n<2) return false;
  if(n%2==0) {
    if(n==2)
      return true;
    else
      return false;
  }
  for (i=3; i*i<=n; i += 2) {
      if(n%i==0) {
          return false;
      }
  }
  return true;
}

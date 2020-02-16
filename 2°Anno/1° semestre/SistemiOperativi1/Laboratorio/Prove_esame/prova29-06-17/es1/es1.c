#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>
#include "xerrors.h"
#include "xerrors.c"
#define Buf_size 10
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
int tot_segnali=0;
bool ricevuto=true;
void handler(int s)
{
  tot_segnali++;
  printf("Segnale %d ricevuto dal processo %d (tot=%d)\n", s, getpid(),tot_segnali);
  if (s==SIGUSR1)
    ricevuto=false;

}

int main(int argc, char *argv[])
{
    // leggi input
    if(argc!=3)
    {
        printf("Uso\n\t%s file range n_processi\n", argv[0]);
        exit(1);
    }

    int p = atoi(argv[2]); ///Processi
    int m = atoi(argv[1]); ///Range di numeri
    assert(p>=0 && m>0);
    int i,status;
    int tot_primi =0 ;
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);     // setta a "insieme vuoto" sa.sa_mask maschera di segnali da bloccare
    sa.sa_flags = SA_RESTART;     // restart system calls  if interrupted
  //  sa.sa_flags |= SA_NODEFER;    // questa non aiuta (vedi Osservazioni)
    sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
    //  creo i processi consumatori
    for(i=0; i<p; i++)
    {
        if(xfork(__LINE__,__FILE__)==0)
        {
            int tot = 0;
            printf("PID %d : %d\n",i,getpid());
            for(int j = 2 * i + 1; (j < m)&& ricevuto; j += 2 * p)
                    if (primo(j))
                    {
                        sleep(5);
                        (tot)+=1;
                    }
            ricevuto = true;
            exit(tot);
        }
    }
    // aspetta terminazione figli
    for(int i=0; i<p; i++)
    {
        xwait(&status, __LINE__,__FILE__);
        if(WIFEXITED(status))
            tot_primi+=WEXITSTATUS(status);
    }
    printf("Numeri primi trovati compresi tra 0 e %d: %d\n",m,tot_primi);
    return 0;
}

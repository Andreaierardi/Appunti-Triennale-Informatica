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
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int divisori(int n)
{ int count = 0 ;
  for (int i = 1; i<=n ; i++)
  if (n %i == 0 )
     count++;
  return count ;
}

bool ricevuto=true;
void handler(int s)
{

  printf("Segnale %d ricevuto dal processo %d \n", s, getpid());
  if (s==SIGUSR1)
    ricevuto=false;

}


int main(int argc, char *argv[])
{
    // leggi input
    if(argc!=4)
    {
        printf("Uso\n\t%s infile outfile nprocessi\n", argv[0]);
        exit(1);
    }
    int p = atoi(argv[3]);
    assert(p>0);
    int e;
    pid_t pid;
    int up[2];
    xpipe(up,__LINE__,__FILE__);
    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , 0666);

    //Segnali
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);     // setta a "insieme vuoto" sa.sa_mask maschera di segnali da bloccare
    sa.sa_flags = SA_RESTART;     // restart system calls  if interrupted
    sigaction(SIGUSR1,&sa,NULL);

    // crea i processi assegnandogli intervalli distinti
    for (int i = 0 ; i<p; i++)
    {
        pid = xfork(__LINE__,__FILE__);
        if (pid==0)
        {
            // codice dei processi figli
            close(up[1]);
            ///Stampo il pid del processo per poter inviare il segnale da terminale
            printf("PID del processo %d: %d\n",i,getpid());

            while (ricevuto)
            {
                if (!ricevuto){printf("->CHIUDO PROCESSO\n");break;}
                ///utilizzo la funzione sleep per testare l'invio dei segnali
                // sleep(3);
                int x ;
                int e= read(up[0],&x,sizeof(int));
                if (e == 0 ) break;
                if(e!=sizeof(int)) {perror("Errore lettura pipe figlio "); exit(1);}
                int div = divisori(x);
                // qui ci voleva un mutex o una singola istruzione di scrittura
                e= write(fd,&x,sizeof(int));
                assert(e==sizeof(int));
                e= write(fd,&div,sizeof(int));
                assert(e==sizeof(int));
            }
            exit(0);
        }
    }
    // codice padre
    int num ,cf;
    FILE *f = xfopen(argv[1],"r",__LINE__,__FILE__);
    close(up[0]);
    while(true)
    {
        cf= fscanf(f,"%d",&num);
        if (cf==0) break ;  //\\ il test da fare era cf!=1
        else if(ferror(f)) ''\\ qualdo il file finisce cf==EOF e ferror==false
        {
            perror("Errore lettura da file");
            exit(1);
        }
        e= write(up[1],&num,sizeof(int));
        assert(e==sizeof(int));
    }
    puts("Lettura terminata");
    close(up[1]);
    e = fclose(f);
    if (e!=0){perror("Errore in chiusura file");exit(1);}
    return 0 ;
}

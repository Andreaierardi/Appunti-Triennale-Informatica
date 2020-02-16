#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>  
#include <assert.h>   
#include "xerrors.h"


// primo esempio di generazione di processi mediante fork
// la comunicazione tra processi figli e il padre
// avviene scrivendo su file di testo
// solo interesse didattico, NON UTILIZZARE in altri contesti

// notare l'uso delle funzioni x... che seguono chiamate di sistema
// o di libreria e verificano la presenza di eventuali errori
// Il sorgente di queste funzioni e' in xerrors.c i prototipi in xerrors.h 


// restituisce true/false a seconda che n sia primo o composto
bool primo(int n);

// conta il numero di primi in un intervallo
int cerca(int a, int b)
{
  int tot = 0;
  for(int i=a;i<b;i++)
    if(primo(i)) tot++;
  return tot;  
}


int main(int argc, char *argv[])
{
  // leggi input
  if(argc!=3) {
    printf("Uso\n\t%s limite numprocessi\n", argv[0]);
    exit(1);
  }
  int n = atoi(argv[1]);
  int p = atoi(argv[2]);
  assert(n>0 && p>0);

  // crea processi
  int i,a,b,e,tot,status;
  pid_t pid;

  // crea i processi assegnandogli intervalli distinti
  for(i=0;i<p;i++) {
    a=1+(n/p)*i;
    b= (i+1==p) ? n : (n/p)*(i+1);
    pid = xfork(__LINE__,__FILE__);
    if (pid==0) {
      // codice dei processi figli
      fprintf(stderr,"F Figlio %d con pid %d cerca fra %d e %d\n",i,getpid(), a,b);
      int tot = cerca(a,b);
      char *s;
      e = asprintf(&s,"conta%d.txt",getpid());
      assert(e>0);
      FILE *f=xfopen(s,"w",__LINE__,__FILE__);
      fprintf(f,"%d\n",tot);  
      fclose(f);
      free(s);
      exit(0);
    }
  }

  // codice del processo padre
  // attende terminazione dei figli e legge i risultati dai file 
  tot = 0;
  for(i=0;i<p;i++) { 
    pid=xwait(&status,__LINE__,__FILE__);
    char *s;
    e = asprintf(&s,"conta%d.txt",pid);
    assert(e>0);  
    FILE *f=xfopen(s,"r",__LINE__,__FILE__);
    free(s);
    int x;
    e = fscanf(f,"%d",&x);
    assert(e==1);
    tot +=x;
    fclose(f);
  }
  printf("Il numero di primi minori di %d e' %d\n",n,tot);
}

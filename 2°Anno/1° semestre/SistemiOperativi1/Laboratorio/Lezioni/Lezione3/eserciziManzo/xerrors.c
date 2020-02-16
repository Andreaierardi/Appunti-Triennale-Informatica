#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

// xerrors.c
// collezione di chiamate a funzioni di sistema con controllo output
// i prototipi sono in xerrors.h


// operazioni su FILE *
FILE *xfopen(const char *path, const char *mode, int linea, char *file) {
  FILE *f = fopen(path,mode);
  if(f==NULL) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  Errore apertura file");
    exit(1);
  }
  return f;
}


// operazioni su processi
pid_t xfork(int linea, char *file)
{
  pid_t p = fork();
  if(p<0) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  Errore fork");
    exit(1);
  }
  return p;
}

pid_t xwait(int *status, int linea, char *file)
{
  pid_t p = wait(status);
  if(p<0) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  Errore wait");
    exit(1);
  }
  return p;
}


int xpipe(int pipefd[2], int linea, char *file) {
  int e = pipe(pipefd);
  if(e!=0) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  Creazione pipe"); 
    exit(1);
  }
  return e;
}

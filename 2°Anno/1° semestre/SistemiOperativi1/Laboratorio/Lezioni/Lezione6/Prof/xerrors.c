#include "xerrors.h"

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


// memoria condivisa
int xshmget(key_t key, size_t size, int shmflg, int linea, char *file)
{
	int e = shmget(key, size, shmflg);
	if(e== -1) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  shmget"); 
    exit(1);
  }
  return e;
}

void *xshmat(int shmid, const void *shmaddr, int shmflg, int linea, char *file) {
	void *e = shmat(shmid, shmaddr, shmflg);
	if(e == (void *) -1) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  shm attach"); 
    exit(1);
  }
  return e;
}


int xshmdt(const void *shmaddr, int linea, char *file) {
	int e = shmdt(shmaddr);
	if(e== -1) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  shm detach"); 
    exit(1);
  }
  return e;
}

int xshmctl(int shmid, int cmd, struct shmid_ds *buf, int linea, char *file) {
	int e = shmctl(shmid, cmd, buf);
	if(e== -1) {
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    perror("  shmctl"); 
    exit(1);
  }
  return e;
}


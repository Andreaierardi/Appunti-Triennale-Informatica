#include "xerrors.h"

// xerrors.c
// collezione di chiamate a funzioni di sistema con controllo output
// i prototipi sono in xerrors.h

// ---- termina stampando il messaggio per l'ultimo errore
void die(const char *s) {
  perror(s);
  exit(1);
}

// ---------- operazioni su FILE *
FILE *xfopen(const char *path, const char *mode, int linea, char *file) {
  FILE *f = fopen(path,mode);
  if(f==NULL) {
    perror("Errore apertura file");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return f;
}


// -------------- operazioni su processi
pid_t xfork(int linea, char *file)
{
  pid_t p = fork();
  if(p<0) {
    perror("Errore fork");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return p;
}

pid_t xwait(int *status, int linea, char *file)
{
  pid_t p = wait(status);
  if(p<0) {
    perror("Errore wait");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return p;
}


int xpipe(int pipefd[2], int linea, char *file) {
  int e = pipe(pipefd);
  if(e!=0) {
    perror("Errore creazione pipe"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}

// ---------------- memoria condivisa POSIX
int xshm_open(const char *name, int oflag, mode_t mode, int linea, char *file)
{
  int e = shm_open(name, oflag, mode);
  if(e== -1) {
    perror("Errore shm_open"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;  
}

int xshm_unlink(const char *name, int linea, char *file)
{
  int e = shm_unlink(name);
  if(e== -1) {
    perror("Errore shm_unlink"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;  
}

int xftruncate(int fd, off_t length, int linea, char *file)
{
  int e = ftruncate(fd,length);
  if(e== -1) {
    perror("Errore ftruncate"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;  
}

void *simple_mmap(size_t length, int fd, int linea, char *file)
{
  void *a =  mmap(NULL, length ,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
  if(a == (void *) -1) {
    perror("Errore mmap"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return a;
}

int xmunmap(void *addr, size_t length, int linea, char *file)
{
  int e = munmap(addr, length);
  if(e== -1) {  
    perror("Errore munmap"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}


// ---------- memoria condivisa System V
int xshmget(key_t key, size_t size, int shmflg, int linea, char *file)
{
  int e = shmget(key, size, shmflg);
  if(e== -1) {
    perror("Errore shmget"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}

void *xshmat(int shmid, const void *shmaddr, int shmflg, int linea, char *file) {
  void *e = shmat(shmid, shmaddr, shmflg);
  if(e == (void *) -1) {
    perror("Errore shm attach"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    exit(1);
  }
  return e;
}


int xshmdt(const void *shmaddr, int linea, char *file) {
  int e = shmdt(shmaddr);
  if(e== -1) {
    perror("Errore shm detach"); 
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
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


// ----- thread (non scrivono il codice d'errore in errno)
#define Buflen 100
#define Attesa 5 

// stampa il messaggio d'errore associato al codice en in maniera simile a perror
void xperror(int en, char *msg) {
  char buf[Buflen];
  
  char *errmsg = strerror_r(en, buf, Buflen);
  if(msg!=NULL)
    fprintf(stderr,"%s: %s\n",msg, errmsg);
  else
    fprintf(stderr,"%s\n",errmsg);
}


int xpthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg, int linea, char *file) {
  int e = pthread_create(thread, attr, start_routine, arg);
  if (e!=0) {
    xperror(e, "Errore pthread_create");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;                       
}

                          
int xpthread_join(pthread_t thread, void **retval, int linea, char *file) {
  int e = pthread_join(thread, retval);
  if (e!=0) {
    xperror(e, "Errore pthread_join");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

// mutex 
int xpthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr, int linea, char *file) {
  int e = pthread_mutex_init(mutex, attr);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_init");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }  
  return e;
}

int xpthread_mutex_destroy(pthread_mutex_t *mutex, int linea, char *file) {
  int e = pthread_mutex_destroy(mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_destroy");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xpthread_mutex_lock(pthread_mutex_t *mutex, int linea, char *file) {
  int e = pthread_mutex_lock(mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_lock");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xpthread_mutex_unlock(pthread_mutex_t *mutex, int linea, char *file) {
  int e = pthread_mutex_unlock(mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_mutex_unlock");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}


// semafori
int xsem_init(sem_t *sem, int pshared, unsigned int value, int linea, char *file) {
  int e = sem_init(sem,pshared,value);
  if (e!=0) {
    xperror(e, "Errore sem_init");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xsem_post(sem_t *sem, int linea, char *file) {
  int e = sem_post(sem);
  if (e!=0) {
    xperror(e, "Errore sem_post");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xsem_wait(sem_t *sem, int linea, char *file) {
  int e = sem_wait(sem);
  if (e!=0) {
    xperror(e, "Errore sem_wait");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

// condition variables
int xpthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr, int linea, char *file) {
  int e = pthread_cond_init(cond,attr);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_init");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xpthread_cond_destroy(pthread_cond_t *cond, int linea, char *file) {
  int e = pthread_cond_destroy(cond);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_destroy");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xpthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, int linea, char *file) {
  int e = pthread_cond_wait(cond,mutex);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_wait");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xpthread_cond_signal(pthread_cond_t *cond, int linea, char *file) {
  int e = pthread_cond_signal(cond);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_signal");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}

int xpthread_cond_broadcast(pthread_cond_t *cond, int linea, char *file) {
  int e = pthread_cond_broadcast(cond);
  if (e!=0) {
    xperror(e, "Errore pthread_cond_broadcast");
    fprintf(stderr,"== %d == Linea: %d, File: %s\n",getpid(),linea,file);
    sleep(Attesa);  // si mette in attesa per non terminare subito gli altri thread 
    exit(1);
  }
  return e;
}


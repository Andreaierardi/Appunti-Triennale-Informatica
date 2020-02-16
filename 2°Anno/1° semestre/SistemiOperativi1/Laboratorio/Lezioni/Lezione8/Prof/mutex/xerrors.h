#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

// operazioni su FILE *
FILE *xfopen(const char *path, const char *mode, int linea, char *file);

// operazioni su processi
pid_t xfork(int linea, char *file);
pid_t xwait(int *status, int linea, char *file);
// pipes
int xpipe(int pipefd[2], int linea, char *file);

// memoria condivisa
int xshmget(key_t key, size_t size, int shmflg, int linea, char *file);
void *xshmat(int shmid, const void *shmaddr, int shmflg, int linea, char *file);
int xshmdt(const void *shmaddr, int linea, char *file);
int xshmctl(int shmid, int cmd, struct shmid_ds *buf, int linea, char *file);


// thread
void xperror(int en, char *msg);

int xpthread_create(pthread_t *thread, const pthread_attr_t *attr,
                          void *(*start_routine) (void *), void *arg, int linea, char *file);
int xpthread_join(pthread_t thread, void **retval, int linea, char *file);

// mutex 
int xpthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr, int linea, char *file);
int xpthread_mutex_destroy(pthread_mutex_t *mutex, int linea, char *file);
int xpthread_mutex_lock(pthread_mutex_t *mutex, int linea, char *file);
int xpthread_mutex_unlock(pthread_mutex_t *mutex, int linea, char *file);


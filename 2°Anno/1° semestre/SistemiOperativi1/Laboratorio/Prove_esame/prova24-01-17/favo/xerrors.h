#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

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




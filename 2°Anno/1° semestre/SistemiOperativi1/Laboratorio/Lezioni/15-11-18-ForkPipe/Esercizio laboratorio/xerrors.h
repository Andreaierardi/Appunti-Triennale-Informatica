#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

// operazioni su FILE *
FILE *xfopen(const char *path, const char *mode, int linea, char *file);

// operazioni su processi
pid_t xfork(int linea, char *file);
pid_t xwait(int *status, int linea, char *file);
// pipes
int xpipe(int pipefd[2], int linea, char *file);

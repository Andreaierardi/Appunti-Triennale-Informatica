#define _GNU_SOURCE
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "xerrors.h"

///20019993@studenti.uniupo.it ANDREA FERRARI

// es1: errori nella seconda parte  
// es2: alcuni errori logici nel codice, gestione segnali incompleta 
// voto: 19



typedef struct
{
    FILE *fp;
    int n ;
    pthread_mutex_t *file;
    int num;
    int *cv;
    pthread_mutex_t *m;
    pthread_cond_t *c;
} dati;


int divisori(int n)
{
    int count = 0 ;
    for (int i = 1; i<=n ; i++)
        if (n %i == 0 )
            count+= i;
    return count ;
}

void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    int div;
    if (*a->cv == a->num)
    {
        printf("OK C\n");//\\ prima della signal va fatta la lock sul mutex corrisopndente 
        pthread_cond_signal(a->c);//\\ questo andava fatto incondizionatamente dopo la scrittura su file 
        pthread_exit(NULL);
    }

    div = divisori(a->n);
    xpthread_mutex_lock(a->file,__LINE__,__FILE__);
    fprintf(a->fp,"%d %d\n",a->n,div);
    *a->cv = (*a->cv) +1;
    printf("%d - %d\n",*a->cv, a->num);
    xpthread_mutex_unlock(a->file,__LINE__,__FILE__);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    if(argc!=3)
    {
        printf("Uso\n\t%s infile \n", argv[0]);
        exit(1);
    }
    int i,e,n,count;
    count =0;
    int num = atoi(argv[2]);

    FILE *f = fopen(argv[1],"r");
    if(f==NULL)
    {
        perror("Errore apertura file");
        return 1;
    }
    while(!feof(f))
    {
        int n;
        e = fscanf(f,"%d", &n);
        if(e!=1) break;
        count++;

    }
    char nomeFile[80];
    sprintf(nomeFile,"%s.somme",argv[1]);
    FILE *fp = fopen(nomeFile,"w");
    rewind(f);
    pthread_t t[count];
    dati a[count];

    pthread_mutex_t mutex_file = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t c = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;;
    int cv ;
    cv = 0;
    if (count <= num)
        num = count-1;

    printf("%d\n",num);
    for(i=0; i<count ; i++)
    {
        e = fscanf(f,"%d", &n);
        if(e!=1) break;
        a[i].num = num;
        a[i].c = &c;
        a[i].m= &m;
        a[i].cv = &cv;
        a[i].fp = fp;
        a[i].n = n;
        a[i].file= &mutex_file;
        xpthread_create(&t[i], NULL, tbody, (void *) &a[i],__LINE__,__FILE__);
    }

    pthread_mutex_lock(&m);
    while (cv <  num)
        pthread_cond_wait(&c, &m);
    pthread_mutex_unlock(&m);

    for(i=0; i<count; i++)
    {
        xpthread_join(t[i], NULL,__LINE__,__FILE__);
        printf("Thread %d terminato \n",i);
    }
    e = fclose(f);
    if (e!=0 )
    {
        perror("Errore chisura file");
        exit(1);
    }
    e = fclose(fp);
    if (e!=0 )
    {
        perror("Errore chisura file");
        exit(1);
    }
    xpthread_mutex_destroy(&mutex_file,__LINE__,__FILE__);
    xpthread_cond_destroy(&c,__LINE__,__FILE__);
    xpthread_mutex_destroy(&m,__LINE__,__FILE__);

    return 0;
}

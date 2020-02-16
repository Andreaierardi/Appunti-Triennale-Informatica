#define _GNU_SOURCE
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include "xerrors.c"
#define Buf_size 10

// struct contenente i parametri di input e output di ogni thread
typedef struct
{
    int **buffer;
    int *somma ;
    int *cindex;
    int bsize;
    pthread_mutex_t *mutex_consumers;
    sem_t *sem_free_slots;
    sem_t *sem_data_items;
} dati;
// funzione eseguita dai thread consumer
void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    *a->somma = 0;
    while(1)
    {
        //aspetta che compaia una coppia (p,r) sul buffer
        int e = sem_wait(a->sem_data_items);
        assert(e==0);
        pthread_mutex_lock(a->mutex_consumers);
        int *n= a->buffer[*(a->cindex)];
        *(a->cindex) = (*(a->cindex) + 1) % Buf_size;
        pthread_mutex_unlock(a->mutex_consumers);
        e = sem_post(a->sem_free_slots);
        assert(e==0);
        if (n!=NULL)
            for (int i = 0 ; i<a->bsize ; i++) *a->somma +=n[i];

        if (n==NULL)
            break;


    }

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    int e;

    int numth, bsize;
    if(argc!=4)
    {
        fprintf(stderr,"USO:  %s numel numth limite [seed]\n\n",argv[0]);
        exit(1);
    }
    bsize = atoi(argv[2]);
    numth= atoi(argv[3]);
    assert(bsize >0 && numth >0 );
    ///----Creazione buffer------
    int *buffer[Buf_size];
    int cindex=0, pindex=0;
    ///----Definizione threads e struttura dati-----
    pthread_t t[numth];
    dati a[numth];
    ///-----Creazione semafori------
    sem_t sem_free_slots, sem_data_items;
    pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
    // inizializzazione semafori
    xsem_init(&sem_free_slots, 0, Buf_size,__LINE__,__FILE__);
    xsem_init(&sem_data_items, 0, 0,__LINE__,__FILE__);

    FILE *f = fopen(argv[1],"rb");
    if(f==NULL)    // se il file non è stato aperto visualizza messaggio d'errore e esci
    {
        perror("Errore apertura file");
        exit(1);
    }
    int somma = 0 ;
    // genera array random
    // copia array e ordina la copia usando la funzione di libreria
    for(int i=0; i<numth; i++)
    {
        a[i].bsize = bsize;
        a[i].somma= &somma;
        a[i].buffer = buffer;
        a[i].cindex = &cindex;
        a[i].mutex_consumers = &mutex_consumers;
        a[i].sem_data_items  = &sem_data_items;
        a[i].sem_free_slots  = &sem_free_slots;
        e = pthread_create(&t[i], NULL, tbody, (void *) &a[i]);
        assert(e==0);
    }
    // eseguo il mio algoritmo di ordinamento
    ///------Richiamo funzione-----
    // segnalo terminazione

    while(1)
    {

        int *n = (int *)malloc(sizeof(int)*bsize);
        assert(n!=NULL);
        int e = fread(n, sizeof(int), bsize, f); // legge un bsize int da f
        if(e!=bsize)
        {

            for (int i = 0 ; i< numth; i++)
            {
                xsem_wait(&sem_free_slots,__LINE__,__FILE__);
                buffer[pindex] = NULL;
                pindex = (pindex+1)%Buf_size;
                xsem_post(&sem_data_items,__LINE__,__FILE__);
            }
            free(n);
            break;

        }
        else
        {
            xsem_wait(&sem_free_slots,__LINE__,__FILE__);
            buffer[pindex] =n ;
            pindex = (pindex+1)%Buf_size;
            xsem_post(&sem_data_items,__LINE__,__FILE__);
        }

    }
    ///-----Aspetta risultato-----
   for(int i=0; i<numth; i++)
        xpthread_join(t[i], NULL,__LINE__,__FILE__);



    ///-------Controllo che array sia ordinato-------
    printf("SOMMA FINALE : %d\n", *(a[0].somma));
    sem_destroy(&sem_data_items);
    sem_destroy(&sem_free_slots);
    pthread_mutex_destroy(&mutex_consumers);

    return 0;
}

/*
 * Esempio semplice paradigma produttore consumatori
 *
 * Usare il numeri.py per generare lunghi elenchi di interi positivi su cui testare il programma
 *
 * Programma di esempio del paradigma 1 producer N consumer
 * i dati letti dal file vengono messi su un buffer in cui il producer scrive
 * e i consumer leggono. In principio il buffer va bene di qualsiasi dimensione:
 * piu' e' grande maggiore e' il lavoro pronto da svolgere nel caso
 * il produttore rimanga bloccato (ad esempio a leggere dal disco)
 *
 * */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "xerrors.h"
#define Buf_size 10
// struct contenente i parametri di input e output di ogni thread
typedef struct
{
    int *buffer;
    int *pindex;
    FILE *f;
    pthread_mutex_t *mutex_consumers;
    pthread_mutex_t *mutex_file;
    sem_t *sem_free_slots;
    sem_t *sem_data_items;
} dati;
// funzione eseguita dai thread consumer
void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    int n;
    while (true)
    {//AGGIUNTA MUTEX PER L'ACCESSO AL FILE
        xpthread_mutex_lock(a->mutex_file,__LINE__,__FILE__);
        int fd= fscanf(a->f,"%d", &n);
        xpthread_mutex_unlock(a->mutex_file,__LINE__,__FILE__);
        //unlock mutex file
        if (fd!=1)
            break;
    //Operazione
        xsem_wait(a->sem_free_slots,__LINE__,__FILE__);
        xpthread_mutex_lock(a->mutex_consumers,__LINE__,__FILE__);

        a->buffer[*(a->pindex)] = (n*n);
        *(a->pindex) = (*(a->pindex)+1)%(Buf_size);
        xpthread_mutex_unlock(a->mutex_consumers,__LINE__,__FILE__);
        xsem_post(a->sem_data_items,__LINE__,__FILE__);

    }
    xsem_wait(a->sem_free_slots,__LINE__,__FILE__);
    xpthread_mutex_lock(a->mutex_consumers,__LINE__,__FILE__);
    a->buffer[*(a->pindex)]= -1;
    *(a->pindex) = (*(a->pindex)+1)%(Buf_size);
    xpthread_mutex_unlock(a->mutex_consumers,__LINE__,__FILE__);
    xsem_post(a->sem_data_items,__LINE__,__FILE__);
    pthread_exit(NULL);

}


int main(int argc, char *argv[])
{
    // leggi input
    if(argc!=3)
    {
        printf("Uso\n\t%s file numthread\n", argv[0]);
        exit(1);
    }
    int p = atoi(argv[2]);
    assert(p>=0);
    int tot_somma = 0;
    int i,e;
    // threads related
    int buffer[Buf_size];
    int cindex=0, pindex=0;
    pthread_t t[p];
    dati a[p];
    sem_t sem_free_slots, sem_data_items;
    pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t mutex_file = PTHREAD_MUTEX_INITIALIZER;

    FILE *f = xfopen(argv[1],"r",__LINE__,__FILE__);
    // inizializzazione semafori
    e = sem_init(&sem_free_slots, 0, Buf_size);
    assert(e==0);
    e = sem_init(&sem_data_items, 0, 0);
    assert(e==0);
    //  creo i thread consumatori
    for(i=0; i<p; i++)
    {
        a[i].mutex_file= &mutex_file;
        a[i].buffer = buffer;
        a[i].f= f;
        a[i].pindex = &pindex;
        a[i].mutex_consumers = &mutex_consumers;
        a[i].sem_data_items  = &sem_data_items;
        a[i].sem_free_slots  = &sem_free_slots;
        e = pthread_create(&t[i], NULL, tbody, (void *) &a[i]);
        assert(e==0);
    }
    // segnalo terminazione
    int conta = 0;
    while(conta<p)
    {
            int e = sem_wait(&sem_data_items);
            assert(e==0);
            int n = buffer[cindex];
            cindex = (cindex + 1) % Buf_size;
            e = sem_post(&sem_free_slots);
            assert(e==0);
            if (n<0)conta++;
            if (n>0)tot_somma+= n;

    }
    xpthread_mutex_destroy(&mutex_consumers,__LINE__,__FILE__);
    xpthread_mutex_destroy(&mutex_file,__LINE__,__FILE__);

    fprintf(stderr,"\nSomma : %d\n",tot_somma);
    fclose(f);

    return 0;
}


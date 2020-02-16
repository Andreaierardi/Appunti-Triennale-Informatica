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
#include <string.h>
#define Buf_size 10

///thread padre produttore
///thread figli consumatori
///Il produttore deve fornire esponente 'i' che deve essere usato dal consumatore per generare i file
///File deve essere passato a tutti i thread che poi leggeranno dati in parallelo

// struct contenente i parametri di input e output di ogni thread
typedef struct
{
    int a;
    int n ;
    int m ;
    int trovati;
    int *pindex;
    int *buffer;
    pthread_mutex_t *mutex_consumers;
    sem_t *sem_free_slots;
    sem_t *sem_data_items;
} dati;

bool primo(int n)
{
    int i;
    if(n<2) return false;
    if(n%2==0)
    {
        if(n==2)
            return true;
        else
            return false;
    }
    for (i=3; i*i<=n; i += 2)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}
void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    for (int i = 0; i<a->m; i++)
    {
        if ((primo(i))&&(i % (2*a->n)== a->a*2 +1))
        {
            int e = sem_wait(a->sem_free_slots);
            assert(e==0);
            pthread_mutex_lock(a->mutex_consumers);
            a->trovati++;
            a->buffer[*(a->pindex)]= i;
            *(a->pindex) = (*(a->pindex) + 1) % Buf_size;
            pthread_mutex_unlock(a->mutex_consumers);
            e = sem_post(a->sem_data_items);
            assert(e==0);
        }
    }

    int e = sem_wait(a->sem_free_slots);
    assert(e==0);
    pthread_mutex_lock(a->mutex_consumers);
    a->buffer[*(a->pindex)]= -1;
    *(a->pindex) = (*(a->pindex) + 1) % Buf_size;
    pthread_mutex_unlock(a->mutex_consumers);
    e = sem_post(a->sem_data_items);
    assert(e==0);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

    int n, m;
    if(argc!=4)
    {
        fprintf(stderr,"USO:  %s nomefile M N \n\n",argv[0]);
        exit(1);
    }
    n = atoi(argv[3]);
    m = atoi(argv[2]);
    assert((n>=0)&&(m>=0));
    ///----Definizione threads e struttura dati-----
    int  buffer[Buf_size];
    int cindex=0, pindex=0;
    int trovati = 0;
    ///----Definizione threads e struttura dati-----
    pthread_t t[n];
    dati a[n];
    ///-----Creazione semafori------
    sem_t sem_free_slots, sem_data_items;
    pthread_mutex_t mutex_consumers = PTHREAD_MUTEX_INITIALIZER;
    int e = sem_init(&sem_free_slots, 0, Buf_size);
    assert(e==0);
    e = sem_init(&sem_data_items, 0, 0);
    assert(e==0);

    FILE *f = fopen(argv[1],"w");
    assert(f!=NULL);

    //a[i].a = i*(m/n);
    //a[i].b = (i==m-1) ? m : (i+1)*(m/n);
    for(int i=0; i<n; i++)
    {
        a[i].a = i;
        a[i].n = n;
        a[i].m = m;
        a[i].trovati = trovati;
        a[i].buffer = buffer;
        a[i].pindex = &pindex;
        a[i].mutex_consumers = &mutex_consumers;
        a[i].sem_data_items  = &sem_data_items;
        a[i].sem_free_slots  = &sem_free_slots;
        e = pthread_create(&t[i], NULL, tbody, (void *) &a[i]);
        assert(e==0);
    }

    int conta = 0 ;
    while(conta<n)
    {

        int e = sem_wait(&sem_data_items);
        assert(e==0);
        int l = buffer[cindex];
        cindex = (cindex+1) %Buf_size;
        if (l>0)fprintf(f,"%d\n",l);
        e = sem_post(&sem_free_slots);
        assert(e==0);
        if (l<0) conta ++;
        printf("CONTA MOD %d\n",conta);

    }
    // segnalo terminazione
    ///-----Aspetta risultato-----
    int tot_trovati = 0 ;
    for(int i=0; i<n; i++)
    {
        e = pthread_join(t[i], NULL);
        if(e==0)
        {
            tot_trovati += a[i].trovati;
            fprintf(stderr,"Thread %d terminato\n",i);
        }
        else
            fprintf(stderr,"Errore join %d\n",e);
    }
    printf("Trovati primi da 0 a %d : %d\n",m,tot_trovati);
    e = fclose(f);
    if (e!= 0)
    {
        perror("Errore chiusura file");
        exit(1);
    }
    return 0;

}

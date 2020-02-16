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
    int b;
    char *nomeFile;
    int *cindex;
    int *buffer;
    pthread_mutex_t *mutex_consumers;
    sem_t *sem_free_slots;
    sem_t *sem_data_items;



} dati;
long power(int a, int y)
{
    int b = a;
    for (int i  = 1 ; i <y; i++)
        b*=a;
    return b;
}
// funzione eseguita dai thread consumer
void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    while (1)
    {
        int n;
        int e = sem_wait(a->sem_data_items);
        assert(e==0);
        pthread_mutex_lock(a->mutex_consumers);
        int esp =a->buffer[*(a->cindex)];
        *(a->cindex) = (*(a->cindex) + 1) % Buf_size;
        if (esp<0) { pthread_mutex_unlock(a->mutex_consumers);
        e = sem_post(a->sem_free_slots);
        assert(e==0);break;}
	pthread_mutex_unlock(a->mutex_consumers);
        e = sem_post(a->sem_free_slots);
        assert(e==0);
	///char *s = sprintf(&s,"%s%d",nomefile,intero)
        char *str = a->nomeFile;
        char c = esp+0x30;
        size_t len = strlen(str);
        char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
        strcpy(str2, str);
        str2[len] = c;
        str2[len + 1] = '\0';
        printf("Creo file: %s\n", str2 ); /* prints "blablablaH" */
        FILE *g = fopen(str2,"w");
        assert(g!=NULL);
        free(str2);
	FILE *f = fopen(a->nomeFile,"r");
	assert(f!=NULL);
        while(!feof(f))
        {
            int fd= fscanf(f,"%d", &n);
            if (fd!=1)break;
            fprintf(g,"%ld\n",power(n,esp));
         
        }

        e = fclose(f);
        if (e!=0){perror("Errore chiusura file letto\n");exit(1);}
        e = fclose(g);
        if (e!=0){perror("Errore chiusura file scritto\n");exit(1);}

    }

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
    

    if (m<n) n = m;
    for(int i=0; i<n; i++)
    {
        a[i].nomeFile= argv[1];
        a[i].buffer = buffer;
        
        a[i].a = i*(m/n);
        a[i].b = (i==m-1) ? m : (i+1)*(m/n);
       
        a[i].cindex = &cindex;
        a[i].mutex_consumers = &mutex_consumers;
        a[i].sem_data_items  = &sem_data_items;
        a[i].sem_free_slots  = &sem_free_slots;
        e = pthread_create(&t[i], NULL, tbody, (void *) &a[i]);
        assert(e==0);
    }

    for (int i = 1 ; i<=m ; i++)
    {

        int e = sem_wait(&sem_free_slots);
        assert(e==0);
        buffer[pindex] = i;
        pindex = (pindex+1)%Buf_size;
        e = sem_post(&sem_data_items);
        assert(e==0);

    }
    // segnalo terminazione
    ///-----Aspetta risultato-----
    for (int i = 0 ; i<n ; i++)
    {

        int e = sem_wait(&sem_free_slots);
        assert(e==0);
        buffer[pindex] =-1;
        pindex = (pindex+1)%Buf_size;
        e = sem_post(&sem_data_items);
        assert(e==0);

    }

    for(int i=0; i<n; i++)
    {
        e = pthread_join(t[i], NULL);
        if(e==0)
        {
            fprintf(stderr,"Thread %d terminato\n",i);
        }
        else
            fprintf(stderr,"Errore join %d\n",e);
    }

  
    return 0;

}

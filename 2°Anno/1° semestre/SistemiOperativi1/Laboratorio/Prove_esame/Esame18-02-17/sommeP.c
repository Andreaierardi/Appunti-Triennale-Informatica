#define _GNU_SOURCE
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "xerrors.h"


#define Buf_size 10

//\\ queste non sono usate nel resto del programma  
int tot_segnali=0;
bool ricevuto=true;
void handler(int s)
{
    tot_segnali++;
    printf("Segnale %d ricevuto dal processo %d (tot=%d)\n", s, getpid(),tot_segnali);
    if (s==SIGUSR1)
        ricevuto=false;

}

int divisori(int n)
{
    int count = 0 ;
    for (int i = 1; i<=n ; i++)
        if (n %i == 0 )
            count+= i;
    return count ;
}

int main(int argc, char *argv[])
{

    if(argc!=2)
    {
        printf("Uso\n\t%s file \n", argv[0]);
        exit(1);
    }

    int tot_divisori = 0;
    int e,n;

    /// alloca i semafori nella shared memory
    int shmid = xshmget(IPC_PRIVATE,3*sizeof(sem_t),0600,__LINE__,__FILE__);
    sem_t *a = (sem_t *) xshmat(shmid,NULL,0,__LINE__,__FILE__);
    sem_t *free_slots = &a[0];
    sem_t *data_items = &a[1];
    sem_t *mutex_consumers = &a[2];

    /// inizializza i semafori, il secondo argomento !=0 permette di condividerli tra processi
    xsem_init(free_slots,1,2+Buf_size,__LINE__,__FILE__);
    xsem_init(data_items,1,0,__LINE__,__FILE__);
    xsem_init(mutex_consumers,1,1,__LINE__,__FILE__);

    /// inizializza shared memory per contenere buffer, somma, quanti e cindex
    int shmid2 = xshmget(IPC_PRIVATE,(Buf_size+1)*sizeof(int),0600,__LINE__,__FILE__);
    int *buffer = (int *) xshmat(shmid2,NULL,0,__LINE__,__FILE__);
    int *cindex = buffer+Buf_size;
    *cindex=0;
    int pindex=0;

    ///segnale
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGUSR1,&sa,NULL);

    char nomeFile[80];
    sprintf(nomeFile,"%s.somme",argv[1]);
    FILE *fout = xfopen(nomeFile,"w",__LINE__,__FILE__);

    if(xfork(__LINE__,__FILE__)==0)
    {
        while(true)
        {//\\ essendoci un solo consumatore non c'era bisogno di mutex_consumers

            xsem_wait(data_items,__LINE__,__FILE__);
            xsem_wait(mutex_consumers,__LINE__,__FILE__);

            int n = buffer[*cindex];
            *cindex = (*cindex+1)%Buf_size;

            xsem_post(mutex_consumers,__LINE__,__FILE__);
            xsem_post(free_slots,__LINE__,__FILE__);

            if(n<0) break;
            else
            {
                int div = divisori(n);
                xsem_wait(mutex_consumers,__LINE__,__FILE__);
                int e=fprintf(fout,"%d : %d\n",n,tot_divisori);//\\ tot_divisori? doveva usare div
                xsem_post(mutex_consumers,__LINE__,__FILE__);
                if(e<0) perror("Errore scrittura file");
            }
        }

        /// detach memoria condivisa
        xshmdt(a,__LINE__,__FILE__);
        xshmdt(buffer,__LINE__,__FILE__);
        exit(0);
    }

    /// codice processo produttore
    FILE *f = xfopen(argv[1],"wb",__LINE__,__FILE__);//\\ andava aperto in lettura 
    printf("Il mio pid è %d \n",getpid());
    while(true)
    {
        //\\ sleep(3);
        e = fscanf(f,"%d", &n);
        if(e!=1) break; /// se il valore e' letto correttamente e==1
        assert(n>0);    /// i valori del file devono essere positivi

        /// metto n nel buffer
        xsem_wait(free_slots,__LINE__,__FILE__);
        buffer[pindex] = n;
        pindex = (pindex+1)%Buf_size;
        xsem_post(data_items,__LINE__,__FILE__);
    }

    /// segnalo terminazione
    for(int i=0; i<Buf_size; i++)
    {
        xsem_wait(free_slots,__LINE__,__FILE__);
        buffer[pindex] = -1;
        pindex = (pindex+1)%Buf_size;
        xsem_post(data_items,__LINE__,__FILE__);
    }


    xwait(NULL,__LINE__,__FILE__);

    /// detach shared memory
    xshmdt(a,__LINE__,__FILE__);
    xshmdt(buffer,__LINE__,__FILE__);

    /// rimozione shared memory
    xshmctl(shmid, IPC_RMID,  NULL,__LINE__,__FILE__);
    xshmctl(shmid2, IPC_RMID,  NULL,__LINE__,__FILE__);
    return 0;
}

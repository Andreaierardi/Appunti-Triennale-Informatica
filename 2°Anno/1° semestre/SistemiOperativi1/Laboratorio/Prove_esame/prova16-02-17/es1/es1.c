#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "xerrors.h"
#include "xerrors.c"
#define Buf_size 10
#define BUFF 100000000

long power(int a, int y)
{
    int b = a;
    for (int i  = 1 ; i <y; i++)
        b*=a;
    return b;
}
int main(int argc, char *argv[])
{
    // leggi input
    if(argc!=4)
    {
        printf("Uso\n\t%s file numproc\n", argv[0]);
        exit(1);
    }
    int p = atoi(argv[3]); ///Processi
    int m = atoi(argv[2]); ///File da creare
    assert(p>=0 && m>0);
    int i,e,n,count, status;
    int max = count =   0;




    FILE *f = fopen(argv[1],"r");
    if(f==NULL){perror("Errore apertura file");exit(1);}
    int *tmp = (int *) malloc(sizeof(int)*BUFF);
    while(true)
    {
        e = fscanf(f,"%d", &n);
        if (e!=1) break;
        tmp[count++] = n;
        //count ++;
    }
    tmp = realloc(tmp,sizeof(int)*count);

    // alloca i semafori nella shared memory
    int shmid = xshmget(IPC_PRIVATE,3*sizeof(sem_t),0600,__LINE__,__FILE__);
    sem_t *a = (sem_t *) xshmat(shmid,NULL,0,__LINE__,__FILE__);
    sem_t *free_slots = &a[0];
    sem_t *data_items = &a[1];
    sem_t *mutex_consumers = &a[2];
    // inizializza i semafori, il secondo argomento !=0 permette di condividerli tra processi
    xsem_init(free_slots,1,Buf_size,__LINE__,__FILE__);
    xsem_init(data_items,1,0,__LINE__,__FILE__);
    xsem_init(mutex_consumers,1,1,__LINE__,__FILE__);
    // inizializza shared memory per contenere buffer, somma, quanti e cindex
    int shmid2 = xshmget(IPC_PRIVATE,(Buf_size+1+count)*sizeof(int),0600,__LINE__,__FILE__);
    int *buffer = (int *) xshmat(shmid2,NULL,0,__LINE__,__FILE__);

    int *array = buffer + Buf_size;
    int *cindex = array + count;
    *cindex=0;
    int pindex=0;
    for (int i = 0 ; i<count; i++) array[i]=tmp[i];
    free(tmp);
    //Copio elemento per elemento
    //  creo i processi consumatori
    for(i=0; i<p; i++)
    {
        if(xfork(__LINE__,__FILE__)==0)
        {
            int conta = 0;
            while(true)   // codice processi consumatori
            {


                xsem_wait(data_items,__LINE__,__FILE__);
                xsem_wait(mutex_consumers,__LINE__,__FILE__);
                long n = buffer[*cindex];
                *cindex = (*cindex+1)%Buf_size;
                xsem_post(mutex_consumers,__LINE__,__FILE__);
                xsem_post(free_slots,__LINE__,__FILE__);
                if(n<0) break;
                conta++;
                char *str = argv[1];
                char c = n+0x30;
                size_t len = strlen(str);
                char *str2 = malloc(len + 1 + 1 ); /* one for extra char, one for trailing zero */
                strcpy(str2, str);
                str2[len] = c;
                str2[len + 1] = '\0';

                printf("Creo file: %s\n", str2 ); /* prints "blablablaH" */
                FILE *g = fopen(str2,"w");
                assert(g!=NULL);
                for (int i = 0 ; i< count ; i++) fprintf(g,"%ld\n",power(array[i],n));
                e = fclose(g);
                if (e!= 0) {perror("Errore chiusura");exit(1);}
                free(str2);
            }

            // detach memoria condivisa
            xshmdt(a,__LINE__,__FILE__);
            xshmdt(buffer,__LINE__,__FILE__);
            exit(conta);

        }

    }
    // codice processo produttore

    for (int i = 1 ; i<=m ; i++)
    {
        // metto n nel buffer
        xsem_wait(free_slots,__LINE__,__FILE__);
        buffer[pindex] = i;
        pindex = (pindex+1)%Buf_size;
        xsem_post(data_items,__LINE__,__FILE__);
    }
    // segnalo terminazione ai consumatori
    for(int i=0; i<p; i++)
    {
        xsem_wait(free_slots,__LINE__,__FILE__);
        buffer[pindex] = -1;
        pindex = (pindex+1)%Buf_size;
        xsem_post(data_items,__LINE__,__FILE__);
    }
    // aspetta terminazione figli
    for(int i=0; i<p; i++)
    {
        xwait(&status, __LINE__,__FILE__);
        if (WIFEXITED(status))
            if (WEXITSTATUS(status)>max)
                max = WEXITSTATUS(status);
    }

    fprintf(stderr,"Massimo dei file creati da un singolo processo: %d\n",max);
    // detach shared memory
    xshmdt(a,__LINE__,__FILE__);
    xshmdt(buffer,__LINE__,__FILE__);
    // rimozione shared memory
    xshmctl(shmid, IPC_RMID,  NULL,__LINE__,__FILE__);
    xshmctl(shmid2, IPC_RMID,  NULL,__LINE__,__FILE__);
    return 0;
}

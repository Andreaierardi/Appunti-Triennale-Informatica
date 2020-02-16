#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "xerrors.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "xerrors.h"
#include "xerrors.c"

int main(int argc, char *argv[])
{
    // leggi input
    if(argc!=3)
    {

        printf("Uso\n\t%s limite numprocessi\n", argv[0]);
        exit(1);
    }
    int p = atoi(argv[1]);
    assert(p>0);
    // crea processi
    int e;
    pid_t pid;
    // crea pipe per la comnicazione dai figli al padre.
    int up[2];
    int down[2];
    xpipe(up,__LINE__,__FILE__);
    xpipe(down,__LINE__,__FILE__);

    // crea i processi assegnandogli intervalli distinti
    for (int i = 0 ; i<p; i++)
    {
        pid = xfork(__LINE__,__FILE__);

        if (pid==0)
        {
            // codice dei processi figli
            close(up[0]);
            close(down[1]);

            int somma = 0;
            while ( true )
            {
                int x ;
                int e= read(down[0],&x,sizeof(int));
                if (e == 0 ) break;
                if(e!=sizeof(int)) {perror("Errore lettura pipe figlio "); exit(1);}
                somma+=x*x;
            }
            close(down[0]);
            e= write(up[1],&somma,sizeof(int));
            assert(e==sizeof(int));
            close(up[1]);
            exit(0);
        }

    }

    int num ;
    close(down[0]);
    FILE *f = xfopen(argv[2],"r",__LINE__,__FILE__);
    while(!feof(f))
    {
        e = fscanf(f,"%d",&num); // legge un int da f
        if (e==0) break ;
        if(ferror(f))
        {
            perror("Errore lettura da file");
            exit(1);
        }

        e= write(down[1],&num,sizeof(int));
        assert(e==sizeof(int));
    }
    close(down[1]);
    e = fclose(f);
    if (e!=0){perror("Errore in chiusura file");exit(1);}
    close(up[1]);

    int fine = 0;
    while(true)
    {
        int x;
        e = read(up[0],&x,sizeof(int));
        if (e == 0 ) break;
        if(e!=sizeof(int)){perror("Errore lettura pipe");exit(1);}
        fine+= x;

    }
    close(up[0]);
    printf("Somma quadrati ricevuti da %d PROCESSI e' %d\n",p,fine);

}

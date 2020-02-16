#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
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

    FILE *fp = xfopen(argv[2],"r",__LINE__,__FILE__);
    int up[2];
    int down[2];
    int val,e,tot,status;
    pid_t pid;
    xpipe(up,__LINE__,__FILE__);
    xpipe(down,__LINE__,__FILE__);

    int cnt = 0;
    int fl=1;
     while (fl!=EOF)
    {
         fl= fscanf (fp,"%d",&val);
        if (e== 0)break;
        printf("%d\n",val );
        e = write(down[1],&val,sizeof(int));
        assert(e==sizeof(int));
        cnt ++;

    }
    close(down[1]);
   close(up[1]);

    // crea i processi assegnandogli intervalli distinti
    for(int i=0; i<p; i++)
    {

        pid = xfork(__LINE__,__FILE__);
        if (pid==0)
        {
            int let;
            // codice dei processi figli
            close(down[1]);
            close(up[0]);
            e  = read(down[0],&let,sizeof(int));
            if(e == 0 || e!= sizeof(int) ) break;
                        printf("LET %d\n ",let);

            let *= let;
            write(up[1],&(let) ,sizeof(int));
            assert(e==sizeof(int));
            close(up[1]);
            exit(0);
        }

    }

    // codice del processo padre
    // legge i risultati dalla pipe
    //close(up[1]);
    tot = 0;
    while(true)
        {

        int x;
        e = read(up[0],&x,sizeof(int));
        printf("X: %d\n",x);
        if(e==0) break;
        if(e!=sizeof(int))
        {
            break;
            perror("Errore lettura pipe");
            exit(1);
        }
        tot+= x;
       }

    close(up[0]);



    printf("SOMMA QUADRATI : %d\n",tot);
    e = fclose(fp);
    if (e!=0) xperror(1,"Errore chisura file");

}

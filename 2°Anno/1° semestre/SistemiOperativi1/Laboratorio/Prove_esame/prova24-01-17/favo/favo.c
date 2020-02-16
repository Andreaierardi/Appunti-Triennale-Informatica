#include "xerrors.h"
#include "xerrors.c"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <signal.h>

#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*Scrivere un programma sommeP che invocato dalla linea di comando scrivendo

  sommeP N nomefile

calcola la somma dei quadrati degli interi memorizzati nel file di testo di nome nomeFile utilizzando N processi figli. Il processo padre deve comunicare con i processi figli solo attraverso delle
pipe: si utilizzi una pipe pipedown per le comunicazioni dal padre ai figli, e una pipe pipeup per le comunicazioni tra figli e padre.

L'idea di base è che il processo padre legge i valori dal file e li comunica ai figli attraverso pipedown. Ogni figlio riceve un certo numero di valori e calcola la somma dei quadrati dei valori ricevuti
 e comunica la somma al padre attraverso pipeup. Il padre raccoglie tutte le somme e visualzza il risultato finale.

Piu' in dettaglio, il processo padre deve:

    generare N processi figli
    aprire il file nomefile
    leggere un intero alla volta dal file e appena letto deve scriverlo nella pipe pipedown
    terminata la lettura da nomefile deve chiudere nomefile e pipedown e leggere da pipeup le somme parziali restituite dai processi figli (1 per per figlio); deve poi calcolare la somma dei valori ricevuti
     e visualizzarla

I processi figli devono:

    inizializzare una variabile somma a 0
    leggere gli interi da pipedown; ogni intero ricevuto deve essere elevato al quadrato e aggiunto a somma
    dopo aver terminato la lettura, il valore di somma deve essere inviato al padre attraverso pipeup


*/


int main(int argc,char *argv[])
{
  if(argc!=3) {
		fprintf(stderr,"Uso\n\t%s  num_proc e nomefile\n", argv[0]);
		exit(1);
	}
  // conversione input
  int n= atoi(argv[1]);
  assert(n>0);
// apre file in scrittura
    FILE *fd=xfopen(argv[2], "rb",__LINE__,__FILE__);
    int pipedown[2];
    int pipeup[2];
    xpipe(pipedown,__LINE__,__FILE__);
    xpipe(pipeup,__LINE__,__FILE__);
    // legge valori dal file
    pid_t pid;
    int e;
    int conta=0;
    int i=0;
	while(!feof(fd)) {
        conta++;
        e = fread(&i,sizeof(int),1,fd);
        if(ferror(fd)){perror("errore lettura");exit(1);}
        if(e==0) {
                break;
		}
        //e = fread(fd, &pipedown[1], sizeof(int)); // legge un int da f
        int c=write(pipedown[1],&i,sizeof(int));
        assert(c==sizeof(int));

    }
    close(pipedown[1]);
	// chiude file
    e = fclose(fd);
	if(e!=0) {
	  perror("Errore chiusura file");
	  exit(1);
	}
int range=conta/n;
int c=0;
  // creazione processi figlio
  for(int i=0;i<n;i++) {

        pid= xfork(__LINE__, __FILE__);
		if(pid==0) { //processo figlio
			int somma=0;

            int e;
            for(int i=0;i<range;i++){
                e = read(pipedown[0],&c,sizeof(int));
                assert(e!=0);
                if(e!=sizeof(int))
                    {perror("Errore lettura pipe");}

                somma+=c*c;
            }
            e  = write(pipeup[1],&somma,sizeof(int));
                    assert(e==sizeof(int));
                    close(pipeup[1]);
                    exit(0);
		}
           // close(pipeup[1]);
			//exit(0);
}

          close(pipeup[1]);
         int sommafinale=0;
         int j=0;
         int h=0;
         while(j<n){

         e = read(pipeup[0],&h,sizeof(int));

        assert(e!=0);
        if(e!=sizeof(int)){
            perror("Errore lettura pipe");
            }
        else{
        sommafinale+=h;
         j++;
        }

        }
        close(pipeup[0]);
        printf("la somma dei quadrati è : %d\n",sommafinale);

        return 0;
}




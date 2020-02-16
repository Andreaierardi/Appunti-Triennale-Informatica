#include <stdio.h>    // permette di usare scanf printf ..
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


void scrivi1n(int n, char *nome)
{
    //n = 100;
	// apre file in scrittura
	int *array = (int *) malloc(n* sizeof(int));
	if (array==NULL){perror("Errore allocazione"); exit(1);}

	int index = 0 ;
	for (int i = 1; i<=n; i++)
    {
        array[index]=i;
        index++;
    }

	int fd = open("scrivibin2", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if(fd<0) {perror("Errore apertura file"); exit(1);}
	// scrive valori sul file
    int e = write(fd,array, n*sizeof(int));   // scrive su f il contenuto di i
    if(e!=sizeof(int)*n)
    {
		perror("Errore scrittura file");
		exit(1);

    }
	// chiude file
	free(array);
	int z = close(fd);
	if(z!=0) {
	  perror("Errore chiusura file");
	  exit(1);
	}
}


int main(int argc, char *argv[])
{

/*  if(argc!=3) {
	  fprintf(stderr, "Uso:\n\t%s n nomefile\n",argv[0]);
	  exit(1);
  }*/
  int n = atoi(argv[1]);
  //assert(n>0);
  scrivi1n(n,argv[2]);
}





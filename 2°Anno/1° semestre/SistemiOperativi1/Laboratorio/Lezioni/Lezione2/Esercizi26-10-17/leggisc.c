#include <stdio.h>    // permette di usare scanf printf ..
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


// leggi numero da file e restituisci la somma
int leggi(char *nome, int b)
{
    // apre file in scrittura
    int fd = open("scrivibin",O_RDONLY);
    if(fd<0)
    {
        perror("Errore apertura file");
        exit(1);
    }
    // legge valori dal file
    int somma = 0;

    int *array = (int *)malloc(sizeof(int)*b);

    while(true)
    {

        int e = read(fd, array, sizeof(int)*b); // legge un int da f
        if(e==0) break; // fine del file

        else
        {
            for(int j = 0 ; j<b; j++) somma += array[j];
        }

    }
    free(array);
    // chiude file
    int e = close(fd);
    if(e<0)
    {
        perror("Errore chiusura file");
        exit(1);
    }
    return somma;
}


int main(int argc, char *argv[])
{
    /*
    if(argc!=3) {
      fprintf(stderr, "Uso:\n\t%s nomefile\n",argv[0]);
      exit(1);
    }*/
    int b = 2; // atoi(argv[2]);
    assert(b>0);
    int l = leggi(argv[1],b);
    printf("Somma valori trovati: %d\n",l);
    return 0;
}

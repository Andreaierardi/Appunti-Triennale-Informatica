//ESERCIZIO 1
#include <stdio.h>
#include <stdlib.h>
int somma_bin(char *nomefile);

int main (int argc, char **argv)
{

    if (argc!= 2)
    {
        perror("DEVI INSERIRE NOME DEL FILE");
        exit(1);
    }
    else
    {
        char *nomefile= argv[1];
        printf("%d\n",somma_bin(nomefile));
    }


    return 0;


}

int somma_bin(char *nomefile)
{
     int somma = 0;
     int l=0;
     FILE *f= fopen(nomefile, "rb");
     if (f == NULL)
     {
         perror("Errore in apertura\n");
         exit(1);
     }

     while(!feof(f))
     {
        int e = fread(&l,sizeof(int), 1, f);
        //printf("%d\n",l);
        if (ferror(f))
        {
            perror("Errore lettura");
            exit(1);
        }

        if (e==0)
            continue;
        somma+=l;
     }
     int e = fclose(f);
     if (e!=0)
     {
         perror("Errore in chiusura file");
         exit(1);
     }

     return somma;

}

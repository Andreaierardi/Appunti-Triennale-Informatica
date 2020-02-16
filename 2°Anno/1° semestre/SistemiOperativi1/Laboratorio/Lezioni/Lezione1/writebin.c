//ESERCIZIO 1
#include <stdio.h>
#include <stdlib.h>
void scrivi(int inserimento, char *nomefile);

int main (int argc, char **argv)
{
 if (argc != 3)
     {
            printf("\nINSERISCI NUMERO - NOME DEL FILE");
            return -1;
     }
     else
     {
         int inserimento= atoi(argv[1]);
         char *nomefile = argv[2];
         scrivi(inserimento, nomefile);
     }

     return 0;
}

void scrivi(int inserimento, char *nomefile)
{
        FILE *f= fopen(nomefile, "wb");
        if (f == NULL)
        {
            perror("FILE NOT FOUND");
            exit(1);
        }
        for (int i = 1; i<=inserimento ; i++)
        {
            //fwrite(&x, sizeof(int), 1, fd);
            int e = fwrite(&i,sizeof(int),1,f);

            if(e!=1)
            {
                perror("Errore lettura file");
                exit(1);
            }
        }
        int e = fclose(f);
        if (e!=0)
        {
            perror("Errore chiusura file");
            exit(1);
        }
}

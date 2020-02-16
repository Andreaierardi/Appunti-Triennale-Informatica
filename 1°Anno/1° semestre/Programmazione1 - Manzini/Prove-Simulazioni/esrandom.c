#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *f=fopen(argv[1],"r");
    if (f==NULL); // verifica che non ci siano errori
        {
        printf("Impossibile aprire il file %s\n",argv[1]);
        return 0;
        }
    char s[100];
    // legge una riga per volta fino alla fine del file
    if(fgets(s,100,f)==NULL){
        puts("Errore");
        return 0;
    }
    printf("%s\n",s);
    return 0;
}

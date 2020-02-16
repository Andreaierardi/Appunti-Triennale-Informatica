#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>
void ora(char *orario)
{
    int ora, min;
    sscanf(orario,"%d:%d",&ora,&min);
    printf("%d:%d\n",ora,min);
    return;
}
void file(char *nome)
{
    FILE *f= fopen(nome,"r");
    if (f==NULL){
        puts("Impossibile aprire il file");
        return;
    }
    int contatore=0;
    char s[100], *r;
    char *a[100];
    int i=0;


    for(;;) {
      r = fgets(s,100,f);


      if(r==NULL)
         break;
      a[i] =(char *)malloc((strlen(s)+1)*sizeof(char));
      if(a[i]==NULL) {puts("Memoria esaurita"); return 2;}
      strcpy(a[i],s);
      i++;
      if(i>=100) {
      puts("Dimensione massima array raggiunta. Interrompo lettura file");
      break;
    }

      contatore+=1;

    }
    printf("[TOTALE AGGANCI]:\n%d\n",contatore);
    char stringhe[100];
    for(int j=i-1;j>=0;j--){
     strcpy(stringhe,a[j]);
     for (int l=i;l>=0;l--)
            printf("%s\n",stringhe[l]);

     }
    return;

}

int main(int argc, char *argv[])
{
    file(argv[1]);
    ora(argv[2]);
    return 0;
}

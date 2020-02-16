#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
#include <string.h>
char *str_concatena(char *a, char *b);

int main(){
    char a[10]={'C','i','a','o'};
    char b[7]={'m','a','m','m','a'};
    char l=0;
    l=*str_concatena(a,b);
    printf("%s",l);
    return 0;
}

char *str_concatena(char *a, char *b) //lunghezza nuova stringa deve essere lung a + lung b
 {
     int lungh = strlen(a) + strlen(b);
     char *copia = (char *) malloc((1+strlen(a))*sizeof(char));
     char *copia2 = (char *) malloc((1+strlen(b))*sizeof(char));
     char *c;
     int i;
     c =(char *) malloc(lungh+1*sizeof(char));
     // copia a e b nel posto giusto in c con 2 cicli for
     // versione alternativa col for
    for ( i=0; i<=lungh; i++){
        c[i]=a[i];
    }
    return c[i];}

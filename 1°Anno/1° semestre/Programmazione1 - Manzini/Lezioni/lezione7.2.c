#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
#include <string.h>
// funzione per stampare la lunghezza di una stringa
int str_lungh(char s[]);

int main(){
char parola[10];
    int array[5]={1,2,3};
    parola[0] = 'C';
    parola[1] = 'i';
    parola[2] = 'a';
    parola[3] = 'o';
    parola[4] = 0;   // in C con lo zero si definisce una fine della stringa
    parola[5] = 'X';   // gli elementi dopo le 0 non li considera
    parola[6] = '\n'; /// anche il caratteri di a capo ha il suo codice ASCII
    parola[7] = '0';
    parola[8] = '1';
    parola[9] =  0;  /// indichiamo con 0 la fine della stringa

    //'\0' è lo 0 in codice ASCII

    int lung = strlen(argv[0]);
    return lung;
    }


char *str_copia(char *s)
{
    char *copia;
    copia = (char *) malloc((1+strlen(s))*sizeof(char)); // non conta lo zero quindi devo aggiungere +1
    if (copia==NULL)
        return NULL;
    int i=0;
    do{
        copia[i] = s[i];
    } while(s[i++]!=0);

    return copia;
    // versione alternativa col for
    for(int i=0; i<=strlen(s);i++)  ///strlen non conta lo 0 quindi devo mettere <=
        copia[i] = s[i];
    return copia;
}
 /// FUNZIONE DI COPIA
 ///char *strcpy(char *dest, const char *src)  //destinazione e funzione a cui punta src
 ///char *strncpy(char *dest, const char *src, size_t n);
 // restituisce un puntatore alla stringa di destinazione
 // MEMORIA DEVE ESSERE GIA' ALLOCATA ALLA POSIZIONE GIUSTA
 /// && --> AND   ||--> OR

/* EX
 n= strlen(a);
 b= """" malloc(n+1);
 strncpy(b,a,n+1)
 */

/// FUNZIONA CONCATENA STRINGA

/// char *strcat(char *dest,const char *src);

/*
            [ciao0]  [mamma0]   elimina lo zero e le unisce
                    |
                    |
                    v
              [ciaomamma0]
*/

/// char *strncat(char *dest, const char *src, size_t n);
/*
            [ciao0] , [mamma0] , 3 | elimina lo zero e le unisce  e
                                   | da un limite a quanti caratteri vengono copiati dopo la prima
                    |
                    |
                    v
              [ciaomam]


*/


// restituisce la stringa formata dalla concatenazione di a e b
// DA COMPLETARE
char *str_concatena(char *a, char *b)
{
  int lungh = strlen(a) + strlen(b);
  char *c = (char *) malloc((lungh+1)*sizeof(char));
  if(c==NULL)
    return NULL;
  // TODO: copia a e b nel posto giusto in c con 2 cicli for
  return c;
}

int str_lungh(char s[])  // si può scrivere anche char *s
                         /// CONST puntatore ad una stringa costante
{
    int i;
    for(i=0;s[i]!=0;i++ ) ///fino a quando s[i] diverso da 0 vado avanti
        ;
    return i;          /// lunghezza della stringa

    //2° versione possibile
    for (int i=0; ;i++)
        if(s[i]==0)
           return i;
}



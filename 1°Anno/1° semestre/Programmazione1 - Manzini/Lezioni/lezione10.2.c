//ESERCIZIO SIMULAZIONE IN C 16-  -
/* memorizzo tutte le stringhe in un array
ma la stringa è 1 puntatore ad un array dove inizia la prima stringa ,seconda e terza.
argv è un puntatore ad un stringa.

ho bisogno di un array di puntatori a carattere. char *str
a[0] punta alla prima stringa
a[1] punta alla seconda stringa ecc..
dentro la variabile a c'è un puntatore ad un array


*/
#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
#include <string.h>
#define SIZE 100
int main(int argc, char *argv[])
{
    if (argc!=2)
    {
        printf("Uso: %s nome file\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1],"r");
    if(f==NULL) {printf("File non trovato\n"); return 2;}
    char s[SIZE];
    char *r;
    char *a[100]; // creo un array a di 100 elementi , ed ogni elemento di a sono puntatori a carattere
    int i=0;
    while(true)
    {
        r=fgets(s,SIZE,f);
        if(r==NULL)
            break;
        //a[i] = s; // sbagliato perchè s punta per ex a 100 e salva sempre la stessa riga "s"
                 //in tutte le posizioni dell'array a[i]
        /// quindi utilizzo una malloc
        a[i] = (char *) malloc((strlen(s)+1)*sizeof(char));
        if(a[i]==NULL){puts("Memoria esaurita");return 0;}
        // ora devo copiare ogni elemento nell'array con strcpy
        strcpy(a[i],s);
        i++;
    }
    fclose(f);
    for(int j=i-1;j>=0;j--)
        printf("%s",a[j]);

    return 0;
}

#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>

int main(int argc, char *argv[])
{
    int n = argc -1; // numero di interi da sommare
    int a[n]; // ho creato a[0], a[1], ... a[n-1]
    // conversione da stringa a interi
    char l;
    for(int i=0;i<n;i++) {
        a[i] = argv[i+1];
        if (strcmp(a[i],a[1])>0)
            printf("%s\n",l);
    }
    // somma degli interi
    return 0;
}

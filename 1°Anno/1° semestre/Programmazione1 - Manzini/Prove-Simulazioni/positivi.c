#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare la funzione assert
void visualizza_array(int a[], int n);

int main(int argc, char *argv[])
{   int conta=0;
    int *b=0;
    int l[conta];
    int n = argc -1; // numero di interi
    b=(int *)malloc(n*sizeof(int));
    int a[n]; // ho creato a[0], a[1], ... a[n-1]
    // conversione da stringa a interi
    for(int i=0;i<n;i++) {
        a[i] = atoi(argv[i+1]);
        if (a[i]>0){
            conta+=1;
            l[i] = a[i];
        }
    }
    b = (int *) realloc(l,conta*sizeof(int));
    visualizza_array(l,n);
    free(b);
    return 0;
}

void visualizza_array(int a[], int n)
{
    printf("--- array di %d elementi ----\n",n);
    for(int i=0;i<n;i++)
        printf("%d\n",a[i]);
    printf("--------- fine -----------------\n");
    // return;
}

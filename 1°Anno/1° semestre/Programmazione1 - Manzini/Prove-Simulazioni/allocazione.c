#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>

int main (int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int *a;
    int capacita=100;
     a =(int *) malloc(capacita*sizeof(int));
     if (a==NULL){puts("memoria insufficiente");}

    int messi=0;
    for (int i=2;i<=n;i++){
        if(primo(i)){
            if (messi==capacita){
                puts("Ingrandisco");
                capacita+=100;
                a=(int *);
                realloc(a,capacita*sizeof(int));
                if (a==NULL){
                    puts("Memoria insufficiente");
                    return 2;
                }
            }
            assert(messi<capacita);
            a[messi]=i;
            messi +=1;
        }
    }
}

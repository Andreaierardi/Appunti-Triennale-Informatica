#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int *quadrati(int a[], int n);
int *elimina_doppioni(int a[],int n);

int main(int argc, char*argv[]){
    if(argc==1){
            printf("Uso: %s");
            return 1;
    }
    int n = argc -1;
    int a[n];

    for(int i=0; i<n ;i++)
        a[i] = atoi(argv[i+1]);

    // calcolo i quadrati
    int *b;
    b = quadrati(a,n); /// restituisco in memoria la posizione dei quadrati
    puts("I quadrati sono");

    for(int i=0; i<n; i++)
        printf("%d",b[i]);
    printf("\n");

    // ora calcolo array senza doppioni
    // ???
    int *y= elimina_doppioni(a,n);
    puts("I non doppini sono");
    for (int i=0; i<n; i++)
        printf("%d",y[i]);
    printf("\n");

    return 0;
}

int quanti(int a[], int n, int k)
{
    int q = 0;
    for (int i=0; i<n ; i++)
        if(a[i]==k) q++;
    return q;
}


// con questa funzione elimino i doppioni dell'array passandogli i valori interi dell'array

int *elimina_doppioni(int a[],int n)  /// il problema è che non sappiamo quale sarà la dimensione dell'array finale
                                       /// prima di chiudere la funzione dovrò fare una realloc
{
    int *x =(int *) malloc(n*sizeof(int));
    assert(x!=NULL);
    int numel = 0; //quanti sono attualmente gli elementi di x

    // riempio x eliminando i doppioni
    for(int i=0; i<n; i++){ ///faccio una scansione dell'array a[]
        int candidato = a[i];
        if (quanti(x,numel,candidato)==0){ //se l'elemento non esiste nell'array lo aggiunge
            x[numel] = candidato;
            numel += 1;
        }

    }
    printf("Numel: %d\n", numel); // MAIN non lo conosce ma noi lo vediamo sullo schermo. Lo facciamo ora perchè ci mancano nozioni che vedremo domani
    x = (int *) realloc(x,numel*sizeof(int));
    return x; //x è una variabile locale però con malloc punta ad una parte della memoria
}

/// un array del c determinato con posizione array ma anche DIMENSIONE dell'array quindi dobbiamo comunicare la dimensione al main





int *quadrati (int a[], int n)  // passiamo un puntatore all'indirizzo dell'array a con n elementi// questa funzione deve restituire un puntatore all'array a[]
                                 // questa funzione deve restituire un puntatore all'array a[]
{
    int c[10]; // creo un array di 10 elementi solo per questa funzione sennò nel main dovrei utilizzare free(c) per sciogliere l'array
    ///int quad[n];   invece che così scrivo
    int *quad = (int *) malloc(n*sizeof(int));
    assert(quad!=0);

    for (int i=0; i<n ; i++)
        quad[i]=a[i]*a[i];
    return quad; // questo valore è la posizione d'inizio di quest'array di elementi
}


/* mi mette in quadrati a ,n, i ma anche la quad[n]
   finita la funzione non ci sono più!

   Quindi possiamo definire puntatori globali invece che locali, alloco quad[n] con una malloc così può essere passato al main

*/





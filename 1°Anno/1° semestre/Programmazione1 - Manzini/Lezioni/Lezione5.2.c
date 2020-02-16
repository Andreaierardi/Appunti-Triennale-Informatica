#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert


// Esempi di chiamate a funzioni che restituiscono un array


int *quadrati(int a[], int n);
int *elimina_doppioni(int a[], int n, int *);  /// col primo asterisco passo l'array, il secondo puntatore è una posizione in memoria

// copia gli elementi passati sulla linea di comando in un array
// di interi; successivamente invoca quadrati() e elmina_doppioni()
int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("Uso: %s n1 n2 n3 n4 .... \n",argv[0]);
        return 1;
    }
    int n = argc -1; // numero di interi da sommare
    int a[n]; // ho creato a[0], a[1], ... a[n-1]
    // conversione da stringa a interi
    for(int i=0;i<n;i++) {
        a[i] = atoi(argv[i+1]);
    }
    // calcolo i quadrati
    int *b;
    b = quadrati(a,n);
    puts("I quadrati sono");
    for(int i=0;i<n;i++)
      printf("%d ", b[i]);
    printf("\n");

    // calcolo array senza doppioni
    int *y = elimina_doppioni(a,n);
    int lunghy;
    int *y = elimina_doppioni(a,n,&lunghy)


    puts("I non doppioni sono (in fondo all'array puo' esserci spazzatura)");
    for(int i=0;i<n;i++)
      printf("%d ", y[i]);
    printf("\n");
    return 0;
}

// conta quante volte il valore k appare nell'array a[] di n elementi
int quanti(int a[], int n, int k)
{
  int q=0;
  for(int i=0;i<n;i++)
    if(a[i]==k) q++;
  return q;
}


// crea un nuovo array con elementi di a[] ma senza doppioni
int *elimina_doppioni(int a[], int n,int *lungh)
{
  int *x = (int *) malloc(n*sizeof(int));
  assert(x!=NULL);
  int numel=0; // quanti sono attualmente gli elementi di x

  // riempio x eliminando i doppioni
  for(int i=0;i<n;i++) {
    int candidato = a[i];
    if(quanti(x,numel,candidato)==0) {
      x[numel] = candidato;
      numel +=1;
    }
  }
  // eseguiamo questa stampa perche' non sappiamo come passare
  // il valore numel a main(). Appena lo sapremo fare la toglieremo
  // printf("I non doppioni sono: %d ma non so come dirlo a main()\n", numel);
  // non eseguo la realloc perche' main() accede a tutti n gli elementi
  // x = (int *) realloc(x,numel*sizeof(int));

  *lungh = numel;
  return x;
}

// creo un nuovo array contenente i qudrati degli elementi di a[]
int *quadrati(int a[], int n)
{
  int *quad = (int *) malloc(n*sizeof(int));
  assert(quad!=0);
  for(int i=0;i<n;i++)
    quad[i] = a[i]*a[i];
  return quad;
}

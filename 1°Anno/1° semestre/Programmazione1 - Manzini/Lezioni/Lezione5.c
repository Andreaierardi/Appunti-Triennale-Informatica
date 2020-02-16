#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert

int calcola_somma_prodotto(int a,int b,int *posizionediprod);


// copia gli elementi passati sulla linea di comando in un array
// di interi
int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("Uso: %s n1 n2 n3 n4 .... \n",argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);  /// vogli restituiti due valori
    int b = atoi(argv[2]);
    int somma,prod;

    /// gli interi vengono rappresentati in 8 bit attraverso la variabile long
    //printf("Posizioni di a,b,somma,prod: %ld %ld %ld %ld\n", (long)&a , (long)&b , (long)&somma , (long)&prod) ;


    prod = -55;
    //la variabile prod viene magicamente cambiata durante la chiamata

    somma = calcola_somma_prodotto(a,b,&prod);
    printf("Risultato, somma: &d, prodotto: %d\n", somma, prod);


    return 0;
}

int calcola_somma_prodotto(int a,int b,int *posizionediprod)
{
    int s = a+b;
    int p = a*b; // come lo passo al main()????  con la return ho soltando la somma
                 // e non posso ritornare due elementi

    //printf("Valori di a,b,posizionediprod , *posizioneprod: %d %d %ld %d\n", a , b , (long) posizionediprod, *posizionediprod);
    /// stampo i valori di a, b e posizionediprod
    //contenuto nella posizione di memoria (long) posizionediprod


    *posizionediprod = p; // il valore di p viene scritto nella RAM nella posizione della variabile prod


    printf("Risultato, somma: %d %d %ld\n", a , b , (long) posizionediprod);

    return s;

}

void calcola_somma_prod(int a,int b,int *posprod, int *possomma)
{
    int s = a+b;
    int p = a*b;
    *posprod = p;
    *possomma = s;
    return;  // non devo mettere return s

}
/// La funzione Main ha varie variabili che sono allocate in memoria

///  _______
/// |  a   | --> 1000
/// |------|
/// |  b   | --> 1004
/// |------|
/// | somma| --> 1008
/// |------|
/// | prod | --> 1012
/// |______|
/// se variabile a del main inizia nella funzione 1000 , b inizia in 1004, somma in 1008, prod in 1012;


/* la funzione prodotto viene allocata nella posizione 1012 che posso restituire attraverso la & che
indirizza alla posizione di memoria 1012

se stampo ora ottengo posizione delle variabili  con distanza di in memoria 4byte ognu

*/

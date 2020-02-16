#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>

int main()
{

/// ISTRUZIONI ++ E --
    int i=5;
    int messi;
    a[i++] = 3; // prima uso e poi incrementa
    messi = 0;

    ++j;
    a[++messi] = b[j]; // prima incrementa messi di 1 e poi utilizzo



    a[messi++] = b[j]; /// quindi utilizzo una istruzione invece che due

    a[messi]= b [j];
    messi++;

/// CICLO WHILE
    int i = 5;
    while(i>0){

        a[i] = 3*i;  //se i>0 allora eseguo le istruzioni nelle graffe, diminuisco per renderla minore di 0
        i--;
    }

    for( ;i>0;i-- ){   // è possibile un ciclo while col for ma è più macchinoso
        a[i] = 3*i;
        /// i--;

        }

     while(i>0){
        a[i] = 3*i;
        i--;

        if(i%2==0)
            continue;  ///quando trovo continue riparte da zero il ciclo senza eseguire le funzione seccessive(ovvero a[i]+= 1
        a[i] += 1;
    }

    do{             /// DO da solo non esiste in C
        a[i] = 3*i;
        i--;
    } while(i>0);  /// prima eseguo e poi verifico se eseguire ancora
                    // utile nel caso di verifica di password minore
                    // di 8 caratteri(se più corta di 8 caratteri continua a chidere)

    return;

}

/*
commenti
*/

*//direttive del compilatore

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

*//funzione per il fattoriale

int fatt(int n) {   *//devo specificare il tipo di variale e deve restituire un oggetto di tipo intero
    int f=1;
    for (int i=2; i<=n; i+=1) {
        f = f*i;
    }
    return f;
}

*/* FUNZIONE FATTORIALE IN PYTHON
def fatt(n):
    f=1
    for i in range(2,n+1):
        f *= i
    return f;
*/

"_______________________________________________________________________________________________"
*/ CICLO FOR IN C
inizializzazione del ciclo  ---> (int i=2)
deve esserci un confronto con un vero o falso --->(; i<=n )
eseguo la terza parte del ciclo for che determina l"aumento ---> (i+=1) "
*/
int fatt(int n){
    int f=1;
    for(int i=2; i<=n; i+= 1){
        f = f*i  //oppure f*= i
        //i += 1;
    }
    return f;
}
"_______________________________________________________________________________________________"

*//FUNZIONE MAIN E' LA PRINCIPALE

int main(int argc, char *argv[]){} *//trovo lunghezza dell'array mentre in C devo determinare
                                   *//una seconda variabile che ci dice quanto è lungo quell'array



"_______________________________________________________________________________________________"


if (argc==2){
    int f = fatt(atoi(argv[1]))   *//converto argv[1] in intero // atoi ---> ASCII TO INTEGER ==> Int(stringa) PYTHON
    printf("%d\n",f)
}
else {
    printf("Uso: %s intero\n", argv[0]);
}
return 0,
}

*/* IN PYTHON
if len(sys.argv)==2:
    print(fatt(int(sys.argv[0])))
else:

*/


*/ IN PYTHON
    a = 7
    print("risultato:",a,"secondo",nome,nome2 )
*/

*/ in C
    printf("risultato: %d secondo me %s e %s \n",a, nome ,nome2); //in C deve seguire l'ordine delle variabili

*/ COMANDO DI COMPILAZIONE
*/ gcc -std=c99 -o nomefinale -O2 -Wall nome.c
//uso lo standard del c99
//-O2 ottimizza il codide
// -Wall segnala non solo errori ma anche warning

//funzione per il calcolo del fattoriale
long fatt(){
long f;
for (int i=2, i<=n; i+=1){
    f*= i;

    }
return f;
}

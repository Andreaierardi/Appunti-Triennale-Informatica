/// TIPI DI VARIABILE
/*
Loung double  %Lf
double        %f
float         %f



char          %c
short         %hd
int           %d
long int      %ld
long long int %lld
*/


///Integer types e unsigned
/*
per esempio unsigne short sono 16 bit 2^16 valori diversi.

con short memorizza numeri da -32000 a +32000
con unsigned short memorizza solo i numeri positivi quindi con un range di +64000

*/
/// SE SCRIVO MAN SCANF MI TROVA GLI UTIZZI DELLA FUNZIONE SUL TERMINALE ( NON TUTTE)


#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <inttypes.h>
int main()
{
    /// LE STRINGHE IN C

    int b1 = 'C';
    int b2 = 'a';
    char  c = 'x';
    printf("b1=%d b2=%d c=%d\n",b1,b2,(int)c); //troverò b1=67 e b2=97 che corrispondono ai codici ASCII di quei due caratteri

    printf("c come carattere: %c  (b1 e b2: %c %c)\n",c,b1,b2); /// ci restituisce il carattere ma è comunque lo stesso valore
                                                              /// cambia solo il metodo di visualizzazione
    char parola[10];
    int a[] = {1,2,3};
    char v[] = 'Mare'; //5 elementi perchè c'è 0 in fondo
    char v[] = 'Mare\nMonti'; ///12 caratteri
    char v[] = 'Mare\\Monti'; /// con uno solo indica un carattere speciale con due determino "\"

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
    printf("\nparola: %s\n", parola);

    parola[3] = 0;
    printf("\nparola: %s\n", parola); // al primo 0 finisce la stringa

    printf("\nparola: %s\n", &parola[7]); /// con un puntatore parto dal valore 7 per stampare la stringa e
                                          /// continuo con parola[8]... ecc fino trovare il valore 0

/* pippo 3 sei

   array |pippo\0|  --> 6 caratteri
   argv|3|10| \0    --> 3 caratteri
   argv2 |s|e|i|10| \n    --> 4 caratteri
*/
    return 0;
}













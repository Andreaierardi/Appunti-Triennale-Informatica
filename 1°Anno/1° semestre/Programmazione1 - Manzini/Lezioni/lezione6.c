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
    printf("char : %d\n",sizeof(char));
    printf("short: %d\n",sizeof(short));
    printf("int: %d\n",sizeof(int));
    printf("long : %d\n",sizeof(long));
    printf("long long: %d\n",sizeof(long long));
    printf("pointer a int: %d\n",sizeof(int *));
    printf("pointer a char: %d\n",sizeof(char *));  //sizeof restituisce un long unsigned type perch� i byte non sono negativi
    printf("pointer a float: %d\n",sizeof(float ));
    printf("pointer a double: %d\n",sizeof(double ));
    printf("pointer a long double : %d\n",sizeof(long double ));
    puts("---------------------");
    /// POSSO DEFINIRE IO I BIT DELLE VARIABILI IN MODO TALE CHE SIA UGUALE IN TUTTE LE MACCHINE
    int64_t i;
    int32_t j;
    int8_t k;

    int a;
    long b;

    a = b; //mi da warning , stai mettendo variabile pi� piccola in una pi� grande e potrei perdere dei dati

    a = (int) b; // PER EVITARE IL WARNING E MI PERMETTE IL TRASFERIMENTO
    b = a;

    double c;

    c= 7/2; // non trovo elementi con la virgola perch� double non supporta la virgola(da risultato 3.0000)
    printf("7/2 con un double == >  %f\n",c);

    c= 7/2.0; // per avere 3.500000
    printf("7/2.0 con un double == >  %f\n",c);

    c = ((double)7/2 );
    printf("7/2.0 con un c=((double) 7/2) == >  %f\n",c);

    c = a; // non ho problemi perch� byte di c > byte di a

    a = c; // warning perch� a<c

    a = (int) c;

    printf("puntatore a double: %lu\n",sizeof(double *));

    puts("----------------------------------");
    //_____________________________________
 // esempi di conversione
  int a;
  char c;
  // tipo piccolo in tipo grande: tutto ok
  c=7;
  a=c;
  printf("a=%d c=%d\n",a,(int) c);
  // tipo grande in tipo piccolo: la conversione puo' dare valori senza senso
  a = 2500;
  c = a;  
  printf("a=%d c=%d\n",a,(int) c);
  // intero in double: tutto ok 
  double d=a;
  printf("a=%d d=%f\n",a,d);
  // double in intero: si perdono le cifre dopo la virgola
  d = -44.55;
  a = d;
  printf("a=%d d=%f\n",a,d);
  // una trappola del C: la divisione fra interi ha risultato intero
  // che successivamente viene convertito in double
  d = 7/2;
  printf("d=%f\n",d);
  // devo convertire uno dei due operandi in double
  d = (double) 7/2; // oppure d = 7.0/2
  printf("d=%f\n",d);
  return 0;
}












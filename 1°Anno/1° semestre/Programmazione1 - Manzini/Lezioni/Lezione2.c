#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/**funzione numero primo in python
def Primo(n):
    if n==1:
        return False
    if n%2==0:
        if n==2:
            return True
        else:
            return False
    for i in range(3,1+n//2,2):
        if n%i==0:
            return False
    return True
*/

bool primo(int n){
    if (n<2){
        return false;
    }
    else if(n%2==0){///n pari
        if(n==2)
            return true;  ///singola istruzione si può omettere la graffa
        else
            return false;
    }
    else {///n dispari >= 3
        assert(n%2!=0);
        for(int i=3; i<n; i+=2){
            if (n%i==0)
                return false;
            else if (i*i>n)
                break;
        }
        return true;

    }
}

/** problema 10 Eulero
def prob10(n):
    somma=0
    for i in range(1,n+1)
        if primo(i):
            somma +=i
    return somma
*/

long prob10(int n){
    long somma=0;
    for(int i=1; i<=n; i+=1){
        if(primo(i))
            somma +=i;
            }
    return somma;
}

/** IN PYTHON
se gli argomenti sono 2 calcola la somma dei primi fino a n altrimenti un messaggio d'errore
if len(sys.argv)==2:
    print(prob10(int(sys.argv[1])))
else:
    print("uso ", sys.argv[0], "numero")  */


 //__________________________________________________________________________________________
 ///  PROBLEMA 10 EULERO IN C
int main(int argc, char *argv[])
{
    if(argc==2){
        printf("%ld\n",prob10(atoi(argv[1])));
        return 0;
    }
    printf("Uso: %s numero \n",argv[0]);
    return 1;

}


//___________________________________________________________________________________________

///PROGRAMMA CHE FA LA SOMMA DI TUTTI I VALORI PASSATI SULLA LINEA DI COMANDO
/// primo esempio di creazione di array
int main2(int argc,char *argv[]){
    if(argc==1){
        printf("Uso: %s n1 n2 n3 n4 .... \n",argv[0]);
        return 1;

        }
    int n = argc -1; ///numeri di interi da somma
    int a[n];  /// n variabili diverse a[0],a[1],....a[n-1]
    ///conversione da stringa a interi
    for (int i=0;i<n;i++){ ///i++ è come scrivere i+=1
        a[i]= atoi(argv[i+1]);
    }
    /// somma degli interi
    int somma= 0;
    for(int i=0;i<n;i++)
        somma+=a[i];
    printf("Somma: %d\n", somma);
    return 0;
}

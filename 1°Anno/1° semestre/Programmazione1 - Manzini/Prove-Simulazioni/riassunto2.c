#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>
void somma_primi(int a[],int n);
bool primo(int n);

int main(int argc,char *argv[])
{
    if (argc!=0)
    {   int somma=0;
        int n=argc-1;
        char a[n];
        int i=0;
        for (i=0; i<n; i++)
            {
                a[i]=atoi(argv[i+1]);
                somma=a[i];
                printf("%d\n",somma);}
        }
        return 0;
    }


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
void somma_primi(int a[],int n)
{

}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


#define dim_array 200 //definisco dim_array=200

bool primo(int n);


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


// legge n da riga di comando e invoca prob10

int main(int argc, char *argv[])
{

    if (argc!=2){
        printf("Uso: %s numero\n",argv[0]);
        return 1;}

    int n = atoi(argv[1]);
    int a[100]; //array di capacità massima di 100
    int messi= 0;
    int i=99;   //se esco dal ciclo i vale 99

    for(int i=2; i<=n; i++){  // se dichiaro variabile i nel ciclo posso usarla solo dentro il ciclo
        if(primo(i)){
            if(messi==100){
                printf("Array troppo piccolo, ingrandisci la costante dim_array e ricompila\n");
                return 2;
            }
            a[messi]=i;
            messi += 1;
        }

    }
    printf("Inseriti %d primi, l'ultimo è' %d\n",messi,a[messi-1]);
    visualizza_array(a,messi);
    printf("Il valore 19 compare %d volte\n",conta(a,messi,19));

    return 0;
}

/* le funzioni o le dichiaro prima del main oppure utilizzo il prototipo della funzione all'inizio del programma  con bool primo(int n)*/


//visualizza il contenuto dell'array a[]

void visualizza_array(int a[], int n)  //è una funzione speciale che non restituisce nulla
{
    printf("--- array di %d elementi ----\n",n);
    for(int i=0;i<n;i++)
        print("%d\n",a[i]);
    printf("----------------- fine -----------------\n");
    return 1;
}


// conta quante volte un valore compare dentro a[] di dimensione n

int conta(int a[],int n, int val)
{
    int volte= 0; //tiene conto di quante volte ho visto val
    for(int i=0; i<n;i++)
        if(a[i]==val)
            volte +=1;
   /// else
   ///     volte += 0;

    return volte;
}






































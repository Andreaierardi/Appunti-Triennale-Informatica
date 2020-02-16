#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100

typedef struct PERSON
{
    char nome[20];
    char cognome[25];
    int eta;
} PERSON;

//function calls
PERSON *makearray(int n);
void printarray(PERSON *array, int n);
void dividi(PERSON *A, int n , PERSON *B, int *nB, PERSON *C, int *nC);

//main
int main()
{
    int n;
    printf("Quante persone vuoi aggiungere?\n");
    scanf("%d",&n);
    PERSON *p=makearray(n);
    printarray(p,n);

    PERSON *BB=malloc(sizeof(PERSON)*n);
    PERSON *CC=malloc(sizeof(PERSON)*n);
    int nB=0;
    int nC=0;

    dividi(p,n,BB,&nB,CC,&nC);
    printf("\n---------------ARRAY MAGGIORENNI-----------------\n");
    printarray(BB,nB);
    printf("\n---------------ARRAY MINORENNI---------------------\n");
    printarray(CC,nC);
}


PERSON *makearray(int n)
{
    PERSON *array=malloc(sizeof(PERSON)*n);
    int i =0;
    printf("\n");
    while(i<n)
    {
        printf("Person name: ");
        scanf("%s",array[i].nome);
        printf("Person surname: ");
        scanf("%s",array[i].cognome);
        printf("Person age: ");
        scanf("%d",&array[i].eta);

        i++;

    }

    return (array);

}

void printarray(PERSON *array, int n)
{
    int i =0;
    while (i<n)
    {
        printf("%d° - Name: %s\n",i+1,array[i].nome);
        printf("%d° - Surname: %s\n",i+1,array[i].cognome);
        printf("%d° - Age: %d\n",i+1,array[i].eta);

        i++;
    }
}

void dividi(PERSON *A, int n , PERSON *B, int *nB, PERSON *C, int *nC)
{
    int i =0;
    int countB=0;
    int countC=0;

    while(i<n)
    {
        if(A[i].eta>=18)
        {
            B[countB]=A[i];
            countB++;
        }
        else
            {
                C[countC]=A[i];
                countC++;
        }
        i++;
    }
    B=realloc(B,sizeof(PERSON)*countB);
    C=realloc(C,sizeof(PERSON)*countC);
    *nB=countB;
    *nC=countC;

}

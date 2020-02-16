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
}PERSON;


PERSON *allocanomi(int n);
void stampa(PERSON *array, int n);
void dividi(PERSON A[], int n, int *nB, int *nC, PERSON B[], PERSON C[]);

int main(int argc,char *argv[])
{

    int n=atoi(argv[1]);
    int dimA=0;
    int dimB=0;

    PERSON *y=allocanomi(n);
    PERSON *BB=(PERSON *)malloc(n*sizeof(PERSON));
    PERSON *CC=(PERSON *)malloc(n*sizeof(PERSON));

    stampa(y,n);
    dividi(y,n,&dimB,&dimA,BB,CC);
}

PERSON *allocanomi(int n)
{
    PERSON *array=malloc(n*sizeof(PERSON));
    for(int i=0; i<n; i++)
    {

        printf("Inserisci il %d nome:  ", i+1);
        scanf("%s",array[i].nome);

        printf("Inserisci il %d cognome:  ", i+1);
        scanf("%s",array[i].cognome);

        printf("Inserisci il %d eta:  ", i+1);
        scanf("%d", &array[i].eta);
    }
    array=(PERSON *)realloc(array,(n)*sizeof(PERSON));
    return array;
}

void stampa(PERSON *array, int n)
{
    printf("\n");
    for(int i=0; i<n; i++)
    {
        printf("%s\n",array[i].nome);
        printf("%s\n",array[i].cognome);
        printf("%d\n",array[i].eta);
    }
}

void dividi(PERSON A[], int n, int *nB, int *nC, PERSON B[], PERSON C[])
{

    for (int i=0; i<n; i++)
    {

        if (A[i].eta>=18)
        {
            strcpy(B[*nB].nome,A[i].nome);

            strcpy(B[*nB].cognome,A[i].cognome);

            B[*nB].eta=A[i].eta;
            (*nB)++;
        }

        else
        {
            strcpy(C[*nC].nome,A[i].nome);


            strcpy(C[*nC].cognome,A[i].cognome);

            C[*nC].eta=A[i].eta;
            (*nC)++;
        }
    }
    printf("--------------\nI MAGGIORENNI SONO\n\n");
    stampa(B,*nB);
    printf("--------------\nI MINORENNI SONO\n\n");
    stampa(C,*nC);
}

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


typedef struct linked_list
{
    PERSON d;
    struct linked_list  *next;
} ELEMENT;
typedef  ELEMENT *LINK;

LINK newnode(){return(malloc(sizeof(ELEMENT)));}

//function calls
LINK makelist();
void printlist(LINK lis);
void printn(LINK lis, int n);
LINK makefromfile(char *rubrica);

//main
int main()
{
    /*
    LINK lista=makelist();
    printlist(lista);

    int n;
    printf("Quanti numi vuoi stampare?\n");
    scanf("%d",&n);
    printn(lista,n);
    */
    LINK lista2=makefromfile("rubrica.txt");
    printlist(lista2);
}



//function
LINK makelist()
{
    LINK p, head, tail;
    head=NULL;
    tail=NULL;

    int n;

    printf("Quante persone vuoi aggiungere?\n");
    scanf("%d",&n);
    for(int i =0; i<n;i++)
    {
        p=newnode();
        printf("Person name: ");
        scanf("%s",p->d.nome);
        printf("Person surname: ");
        scanf("%s",p->d.cognome);
        printf("Person age: ");
        scanf("%d",&p->d.eta);
        p->next=NULL;
        if(head==NULL){head=p;tail=p;}
        else{tail->next=p;tail=p;}


    }
    return (head);
   }

void printlist(LINK lis)
{
    printf("\n");
    int num=1;
    while(lis!=NULL)
    {
        printf("%d° - Person name: %s\n",num, lis->d.nome);
        printf("%d° - Person surname: %s\n",num,lis->d.cognome);
        printf("%d° - Person age: %d\n",num,lis->d.eta);
        num++;
        printf("\n");
        lis=lis->next;
    }

}

void printn(LINK lis, int n)
{
    printf("\n");
    int num=1;
    while(lis!=NULL)
    {
        if (num<=n)
        {
        printf("%d° - Person name: %s\n",num, lis->d.nome);
        printf("%d° - Person surname: %s\n",num,lis->d.cognome);
        printf("%d° - Person age: %d\n",num,lis->d.eta);
        num++;
        printf("\n");
        }
        lis=lis->next;

    }
}

LINK makefromfile(char *rubrica)
{
    LINK p, head, tail;
    head=NULL;
    tail=NULL;

    FILE *f=fopen(rubrica,"r");
    if(f==NULL)
    {
        printf("\nERROR - FILE NOT FOUND\n");
        return NULL;

    }

    char *r; char s[BUFFER];

    while(true)
    {
        r=fgets(s,BUFFER,f);

        if(r==NULL)
        {
            break;
        }
        p=newnode();
        sscanf(r,"%s %s %d",p->d.nome,p->d.cognome,&p->d.eta);
        p->next=NULL;

        if(head==NULL){head=p;tail=p;}
        else{tail->next=p,tail=p;}
    }
    return(head);
}

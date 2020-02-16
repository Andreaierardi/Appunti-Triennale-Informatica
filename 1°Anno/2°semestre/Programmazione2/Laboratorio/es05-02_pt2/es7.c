#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100
typedef struct PERSON
{
    char nome[20];
    char cognome[20];
    int eta;
} PERSON;

typedef struct linked_list
{
    PERSON d;
    struct  linked_list *next;
} ELEMENT;

typedef ELEMENT *LINK;

LINK newnode(void)
{
    return (malloc(sizeof(ELEMENT)));
}

LINK listgenerate();
void printlis(LINK lis);
void searchlis(LINK lis);
void insertparents(LINK lis, PERSON per, int *contatore );

int main()
{
    LINK lista;
    lista=listgenerate();
    printlis(lista);

    searchlis(lista);

    PERSON persona;
    printf("AGGIUNTA PERSONA\nNome: ");
    scanf("%s",persona.nome);
    printf("Cognome: ");
    scanf("%s",persona.cognome);
    printf("Eta': ");
    scanf("%d",&persona.eta);
    int count=0;
    insertparents(lista, persona,&count);

    printlis(lista);

    if (count==0)
    {
        printf("\nNon ha parenti\n");
    }
}


LINK listgenerate()
{
    LINK p;
    PERSON valori;

    printf("Inserisci nome persona: ");
    scanf("%s",valori.nome);

    if(strcmp(valori.nome,"END")!=0)
    {
        p=newnode();
        strcpy(p->d.nome,valori.nome);

        printf("Inserisci cognome persona: ");
        scanf("%s",p->d.cognome);

        printf("Inserisci eta' persona: ");
        scanf("%d",&p->d.eta);

        p->next=listgenerate();
        return (p);
    }
    else{return (NULL);}
}

void printlis(LINK lis)
{
    printf("\n------------------\n");

    if (lis!=NULL)
    {
        printf("%s\n",lis->d.nome);
        printf("%s\n",lis->d.cognome);
        printf("%d\n",lis->d.eta);

        printlis(lis->next);
    }

}

void searchlis(LINK lis)
{
    char ricerca;
    printf("Come vuoi cercare la persona? /posizione o cognome/: \n");
    scanf(" %c",&ricerca);

    char cognome[20];
    int posizione;
    int count=0;
    while (lis!=NULL)
    {
    if(ricerca=='P')
    {
        printf("In quale posizione vuoi trovare la persona?");
        scanf("%d",&posizione);
        while(lis!=NULL)
        {
            count++;
            if (count==posizione)
            {
                printf("%s\n",lis->d.nome);
                printf("%s\n",lis->d.cognome);
                printf("%d\n",lis->d.eta);

            }
             lis=lis->next;


        }



    }

    if (ricerca=='C')
    {
        printf("Quale persona vuoi cercare?");
        scanf("%s",cognome);

        if(strcmp(lis->d.cognome,cognome)==0)
        {
            printf("%s\n",lis->d.nome);
            printf("%s\n",lis->d.cognome);
            printf("%d\n",lis->d.eta);


        }
        else {printf("\nPersona non trovata\n");}
        lis=lis->next;

    }

}
}

void insertparents(LINK lis, PERSON per, int *contatore)
{
    if(lis!=NULL)
    {

         if(strcmp(lis->d.cognome,per.cognome)==0)
        {
            LINK p;
            p=newnode();
            strcpy(p->d.cognome,per.cognome);
            strcpy(p->d.nome,per.nome);
            p->d.eta=per.eta;
            p->next=lis->next;
            lis->next=p;
            (*contatore)++;
        }
        else insertparents(lis->next,per,contatore);
    }
}

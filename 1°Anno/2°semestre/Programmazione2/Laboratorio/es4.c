#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <assert.h>
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
    struct linked_list *next;
} ELEMENT;


typedef ELEMENT *LINK;

LINK newnode()
{
     return (malloc(sizeof(ELEMENT)));
}

void stampapersonlista(LINK lis);
LINK crealistaperson();


void addpersontail(LINK *lis, PERSON per);
void addpersonhead(LINK *lis, PERSON per);
int controllmin(LINK lis);
int controllamag(LINK lis);
LINK findbefore(LINK lis);
LINK parenti(LINK lis, PERSON persona);

int main(int argc, char *argv[])
{
    LINK lista, lista2;
    PERSON persona;
    lista=crealistaperson();

    printf("Nome persona da aggiungere ");
    scanf("%s",persona.nome);
    printf("Cognome persona da aggiungere ");
    scanf("%s",persona.cognome);
    printf("Eta persona da aggiungere ");
    scanf("%d",&persona.eta);

    //addpersontail(&lista,persona);
    //addpersonhead(&lista,persona);
    stampapersonlista(lista);
    lista2=parenti(lista,persona);
    stampapersonlista(lista2);

}

void stampapersonlista(LINK lis)
{
    printf("\n");
    while(lis!= NULL)
    {
        printf("%s\n",lis->d.nome);
        printf("%s\n",lis->d.cognome);
        printf("%d\n",lis->d.eta);
        lis=lis->next;
    }
}

LINK crealistaperson()
{
    int numelem;

    LINK p,head, tail;
    head=NULL;
    tail=NULL;

    printf("Quanti nomi vuoi inserire? \n");
    scanf("%d",&numelem);
    if (numelem==0)
    {
        return(NULL);
    }

    else
    {
        for (int i=0; i<numelem; i++)
        {
            p=newnode();

            printf("Inserisci il nome:  ");
            scanf("%s",p->d.nome);
            printf("Inserisci il cognome:  ");
            scanf("%s",p->d.cognome);
            printf("Inserisci l'eta:  ");
            scanf("%d",&p->d.eta);

            p->next=NULL;

            if (head==NULL){head=p; tail=p;}
            else{tail->next=p; tail=p;}

        }
        return (head);
    }

}


LINK crealistamag(LINK lis)
{
    int numelem;

    LINK p,head, tail;
    head=NULL;
    tail=NULL;
    LINK elbef;

    printf("Quanti nomi vuoi inserire? \n");
    scanf("%d",&numelem);
    if (numelem==0)
    {
        return(NULL);
    }

    else
    {
        for (int i=0; i<numelem; i++)
        {
            p=newnode();

            printf("Inserisci il nome:  ");
            scanf("%s",p->d.nome);
            printf("Inserisci il cognome:  ");
            scanf("%s",p->d.cognome);
            printf("Inserisci l'eta:  ");
            scanf("%d",&p->d.eta);

            if(p->d.eta>=18)
            {
                if(controllamag(lis)>0)
                {
                    elbef=findbefore(lis);
                    addpersonhead(&lis,p->d);
                }
                else{addpersonhead(&lis,p->d);}
            }
            if (p->d.eta<18)
            {
                if((controllamin(lis)>0))
                {
                    elbef=findbefore(lis);
                    addpersonhead(&lis,p->d);
                }
                else{addpersonhead(lis,p->d);}
            }
        }

    }
       return (lis);

}

//inserimento in testa
void addpersonhead(LINK *lis, PERSON per)
{
    LINK p;

    if(lis!=NULL)
        {
            p=newnode();
            strcpy(p->d.nome,per.nome);
            strcpy(p->d.cognome,per.cognome);
            p->d.eta=per.eta;
            p->next=*lis;
            (*lis)=p;
        }

}


// inserimento in coda
void addpersontail(LINK *lis, PERSON per)
{
    LINK p, head, tail;
    head=*lis;

    if((*lis)!=NULL)
    {
        p=newnode();
        strcpy(p->d.nome,per.nome);
        strcpy(p->d.cognome,per.cognome);
        p->d.eta=per.eta;

        p->next=NULL;

        while(head->next!=NULL)
        {
            head=head->next;
        }
        *lis=p;
    }
    else
    {
           addpersonhead(&head,per);
    }

    return;

}

int controllamag(LINK lis)
{
    int verifica=0;

    while(lis!= NULL)
    {
        if(lis->d.eta>=18)
        {
            verifica++;
        }
        lis=lis->next;
    }

    return verifica;

}

int controllamin(LINK lis)
{
     int verifica=0;

    while(lis!= NULL)
    {
        if(lis->d.eta<18)
        {
            verifica++;
        }
        lis=lis->next;
    }

    return verifica;

}

LINK findbefore(LINK lis)
{
    int trovato=0;
    if (lis==NULL)
    {
        return (NULL);
    }
    else
    {
        if ((lis->d.eta)>=18)
        {
            return (NULL);
        }
        else
        {
            while((lis->next!=NULL)&&(!trovato))
                if ((lis->next->d.eta)>=18)
                    trovato=1;
                else
                    lis=lis->next;
        }
        if (trovato)
            return (lis);

        else
            return(NULL);
    }
}

LINK parenti(LINK lis, PERSON persona)
{
    LINK p,head, tail;
    head=NULL;
    tail=NULL;

    while(lis!=NULL)
    {
        if(strcmp(lis->d.cognome,persona.cognome)==0)
        {
            p=newnode();
            p->d=lis->d;
            p->next=NULL;
            if(head==NULL){head=p;tail=p;}
            else{tail->next=p; tail=p;}
        }

        lis=lis->next;

    }

    return (head);
}

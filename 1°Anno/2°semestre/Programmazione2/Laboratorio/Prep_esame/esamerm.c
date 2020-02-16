#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct STUDENT
{
    char cognome[20];
    char nome[20];
    int matricola;
    char esame[20];
    int crediti;
    int voto;
}STUDENTE;


typedef struct linked_list
{
    STUDENTE d;
    struct linked_list *next;
} ELEMENT;

typedef ELEMENT *LINK;


LINK newnode()
{
    return(malloc(sizeof(ELEMENT)));
}

//FUNCTION CALLS
LINK createfromfile(char *nomefile);
void printlis_rt(LINK p);
int sum_crediti_rn(LINK lis, int matricola);
LINK surnamedata(LINK *list, char *cognome);
void delallxV2(char *cognome, LINK *lis);
//MAIN
int main()
{
    LINK lista=createfromfile("input-esame.txt");
    printlis_rt(lista);

    int matricola=100123;
    //printf("Scrivi matricola di cui vuoi sapere i crediti totali: ");
    //scanf("%d",&matricola);
    int crediti=sum_crediti_rn(lista,matricola);
    printf("I crediti di %d:  %d\n",matricola,crediti);

    char *cognome="Rossi";
    //printf("Scrivi cognome di cui vuoi sapere i dati: ");
    //scanf("%s",&cognome);
    printf("\n-----------------NEWLIST-------------------\n\n");
   // LINK copy_lis=lista;
    LINK lista2=surnamedata(&lista, cognome);

    printlis_rt(lista2);

    printf("\n-----------------RELOAD OLD LIST-------------------\n\n");
    printlis_rt(lista);

}


//FUNTIONS
LINK createfromfile(char *nomefile)
{
    LINK p, head , tail;
    head=NULL;
    tail=NULL;
    FILE *f=fopen(nomefile, "r");

    if (f==NULL)
    {
        printf("ERROR \n");
        return (NULL);
    }


    else
    {

    STUDENTE tmp;
    while(( fscanf(f,"%s %s %d %s %d %d", tmp.cognome, tmp.nome, &tmp.matricola, tmp.esame, &tmp.crediti, &tmp.voto))!=EOF)
    {

        p=newnode();
        p->d=tmp;
        p->next=NULL;

        if (head==NULL){head=p; tail=p;}
        else {tail->next=p; tail=p;}

    }
}
    return (head);
}


void printlis_rt(LINK p)
{
    if (p!=NULL)
    {
        printf("Cognome: %s\nNome: %s\nMatricola: %d\nEsame: %s\nCrediti: %d\nVoto: %d\n\n",p->d.cognome, p->d.nome, p->d.matricola, p->d.esame, p->d.crediti, p->d.voto);
        printlis_rt(p->next);
    }
}

int sum_crediti_rn(LINK lis, int matricola)
{
    if (lis==NULL) return (0);

    else
    {
        if (lis->d.matricola==matricola)
        {
            return(lis->d.crediti+sum_crediti_rn(lis->next,matricola));

        }

        else
        {
            return (sum_crediti_rn(lis->next,matricola));
        }
    }
}

LINK surnamedata(LINK *list, char *cognome)
{
    LINK p, head, tail;
    head=NULL;
    tail=NULL;

    LINK p2;

    LINK lis=*list;

    while(lis!=NULL)
    {



        if (strcmp(cognome,lis->d.cognome)==0)
        {
            p=newnode();
            p->d=lis->d;
            p->next=NULL;

            if(head==NULL){head=p; tail=p;}
            else {tail->next=p; tail=p;}



        }

        lis=lis->next;
    }

 delallxV2(cognome,list);

    return (head);
}

void delallxV2(char *cognome, LINK *lis)
{

    LINK p, head;
    if (lis != NULL)
    {
        head=*lis;
        while (head->next != NULL)
        {
            if (strcmp(head->next->d.cognome,cognome)==0)
            {
            p=head->next;
            head->next=head->next->next;
            free(p);
            }
            else head=head->next;
        }
    if (strcmp((*lis)->d.cognome,cognome)==0) {p=*lis; *lis=(*lis)->next; free(p);}
    }
}

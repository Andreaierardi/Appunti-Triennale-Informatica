#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100

typedef struct BOOK
{
    char titolo[40];
    char autore[40];
    int prezzo;
    int disponibilita;

} BOOK;

typedef struct linked_list
{
    BOOK d;
    struct linked_list  *next;
} ELEMENT;
typedef  ELEMENT *LINK;

LINK newnode(){return(malloc(sizeof(ELEMENT)));}

//function calls
LINK buildfromfile(char *nomefile);
void printlis_r(LINK lis);
void searchautor(LINK lis, char *autore);
void shop(LINK *lis, char *titolo);
LINK unions(LINK lis, LINK lis2, LINK *head,LINK *tail);
int trovato(LINK lis, LINK trovato);
int max(int a, int b);
//main
int main()
{
    LINK lista=buildfromfile("libri.txt");

  //  printlis_r(lista);

    /*
    char autor[40];
    printf("\n-------------------------------------------------\n");
    printf("\nQuale autore vuoi cercare?");
    scanf("%s",autor);
    searchautor(lista,autor);
    printf("\n--------------------------------------------------\n");

    char title[40];
    printf("\n");
    printf("Di quale libro vuoi modificare la vendita?  ");
    scanf("%s",title);
    shop(&lista,title);

    printf("\n-------------------------------------------------\nLISTA MODIFICATA\n");
    printlis_r(lista);
    */


    LINK lista2=buildfromfile("libri2.txt");
    //printlis_r(lista2);
    LINK head=NULL;
    LINK tail=NULL;
    unions(lista,lista2, &head, &tail);

   printlis_r(head);
    return (0);
}


//functions
LINK buildfromfile(char *nomefile)
{
    LINK p, head , tail;
    head=NULL;
    tail=NULL;

    FILE *f=fopen(nomefile,"r");
    if (f==NULL)
    {
        printf("ERROR");
        return NULL;
    }

    char *r, s[BUFFER];

    while(true)
    {
        r = fgets(s,BUFFER,f);
        if (r==NULL)
        {
            break;
        }
        p=newnode();
        sscanf(r, "%s %s %d %d",p->d.titolo,p->d.autore,&p->d.prezzo,&p->d.disponibilita);
        p->next=NULL;
        if (head==NULL){head=p; tail=p;}
        else{tail->next=p;tail=p;}
     }


    return (head);
}

void printlis_r(LINK lis)
{
    while(lis!=NULL)
    {

    printf("\nTitolo: %s\n",lis->d.titolo);
    printf("Autore: %s\n",lis->d.autore);
    printf("Prezzo:  %d\n",lis->d.prezzo);
    printf("Disponibilita:  %d\n",lis->d.disponibilita);
    lis=lis->next;
    }
}

void searchautor(LINK lis,char *autore)
{
    if (lis==NULL) return;
    if(lis!=NULL)
    {


        if(strcmp(lis->d.autore,autore)==0)
        {
                printf("\nTitolo del Libro:   %s",lis->d.titolo);

        }
        searchautor(lis->next,autore);

    }

}


void shop(LINK *lis, char *titolo)
{

    int sell;
    LINK p;


    if ((*lis)==NULL) {*lis=NULL;}
    if ((*lis)!=NULL)
    {
        if (strcmp((*lis)->d.titolo,titolo)==0)
        {

            printf("\nQuante copie sono state vendute?");
            scanf("%d",&sell);

            (*lis)->d.disponibilita-=sell;


            if((*lis)->d.disponibilita<=0)
            {
                printf("Servono altre %d copie del libro\n",(*lis)->d.disponibilita-2*((*lis)->d.disponibilita));
                p=*lis;
                *lis=(*lis)->next;
                free(p);
            }
        }

        else{shop(&(*lis)->next, titolo);}
    }


}

LINK unions(LINK lis, LINK lis2, LINK *head,LINK *tail)
{
    LINK p;
   // LINK testa2=lis2;

    if((lis!=NULL)&&(lis2!=NULL))
    {
       // lis2=testa2;
      //  if (lis2!=NULL)
        //{


            if((strcmp(lis->d.autore,lis2->d.autore)==0)&&(strcmp(lis->d.titolo,lis2->d.titolo)==0)&&(trovato(head,lis)==0))
            {
                p=newnode();
                strcpy(p->d.autore,lis->d.autore);
                strcpy(p->d.titolo,lis->d.titolo);
                p->d.prezzo=max(lis->d.prezzo,lis2->d.prezzo);
                p->d.disponibilita=lis->d.disponibilita+lis2->d.disponibilita;
                p->next=unions(lis->next,lis2->next,head,tail);

                if(*head==NULL) {*head=p; *tail=p;}
                else {(*tail)->next=p; *tail=p;}
            }

            else {(unions(lis->next,lis2->next,head, tail));}

      //  }
       (unions(lis->next,lis2, head, tail));
    }

    return (0);

}

int trovato(LINK lis, LINK p)
{
    if(strcmp(lis->d.titolo,p->d.titolo)==0)
    {

        return (1);
    }
    else return (0);
}

int max(int a, int b)
{
    if(a>b)
    {
        return (a);
    }
    else
        return (b);
}

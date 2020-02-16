#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100

typedef struct BOOK
{
    char titolo[20];
    char autore[20];
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
LINK buildlis_r();
LINK buildfromfile(char *nomefile);

void printlis_r(LINK lis, int x);
void rewindprintlis(LINK lis, int x);
LINK samebook(LINK l1,LINK l2);
void samebook_rt(LINK l1, LINK l2,LINK *head, LINK *tail, LINK copy_l2);

LINK samebook_rn(LINK l1, LINK l2, LINK copy_l2);
//main
int main()
{
    LINK lista=buildfromfile("libri.txt");

    /*
    int val;
    printf("\n------------------------------\nDisponibilita dei libri che vuoi stampare: ");
    scanf("%d",&val);
    printlis_r(lista, val);

    printf("\n\n-------------------CONTRARIO------------------------\n\n");


    int val2;
    printf("\n------------------------------\nDisponibilita dei libri che vuoi stampare al contrario: ");
    scanf("%d",&val2);
    rewindprintlis(lista,  val2);
    */
    LINK lista2=buildfromfile("libri2.txt");

    printf("\n\n--------------------ITERATIVE--------------------------\n");
    LINK lista3=samebook(lista,lista2);

    printlis_r(lista3,0);

    printf("\n\n--------------------RICURSIVE--------------------------\n");

    LINK lista6=samebook_rn(lista,lista2,lista2);
    printlis_r(lista6,0);

    return 0;
}



//functions
LINK buildlis_r()
{
    LINK p=NULL;

    char risposta;

    printf("Vuoi aggiungere un libro?");
    scanf(" %c",&risposta);
    if (risposta=='y')
    {
    p=newnode();
    printf("Titolo: ");
    scanf("%s",p->d.titolo);
    printf("Autore: ");
    scanf("%s",p->d.autore);
    printf("Prezzo: ");
    scanf("%d",&p->d.prezzo);
    printf("Disponibilita:  ");
    scanf("%d",&p->d.disponibilita);

    p->next=buildlis_r();

    }
    return(p);

    }
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


void printlis_r(LINK lis, int x)
{
    if(lis==NULL) return ;

    else if((lis!=NULL)&&(lis->d.disponibilita >= x))
    {

    printf("\nTitolo: %s\n",lis->d.titolo);
    printf("Autore: %s\n",lis->d.autore);
    printf("Prezzo:  %d\n",lis->d.prezzo);
    printf("Disponibilita:  %d\n",lis->d.disponibilita);
    printlis_r(lis->next,x);
    }


    else
        printlis_r(lis->next,x);
}


void rewindprintlis(LINK lis, int x)
{
    if(lis==NULL) return ;

    else if((lis!=NULL)&&(lis->d.disponibilita >= x))
    {
    printlis_r(lis->next,x);
    printf("\nTitolo: %s\n",lis->d.titolo);
    printf("Autore: %s\n",lis->d.autore);
    printf("Prezzo:  %d\n",lis->d.prezzo);
    printf("Disponibilita:  %d\n",lis->d.disponibilita);

    }


    else
        printlis_r(lis->next,x);
}

LINK samebook(LINK l1, LINK l2)
{
    LINK p, head, tail;

    head=NULL;
    tail=NULL;

    LINK tmp=l2;
    while(l1!=NULL)
    {

        l2=tmp;
        while(l2!=NULL)
            {
            if (strcmp(l1->d.titolo,l2->d.titolo)==0)
            {
                p=newnode();
                strcpy(p->d.titolo,l1->d.titolo);
                strcpy(p->d.autore,l1->d.autore);
                p->d.prezzo=l1->d.prezzo;
                p->d.disponibilita=l1->d.disponibilita;
                p->next=NULL;

                if(head==NULL){head=p; tail=p;}
                else {tail->next=p;tail=p;}

            }

            l2=l2->next;
            }
         l1=l1->next;
    }

    return (head);
}


void samebook_rt(LINK l1, LINK l2, LINK *head, LINK *tail, LINK copy_l2)
{

    LINK p=NULL;

    if(l1!=NULL)
    {
        if(l2!=NULL)
            {
            if (strcmp(l1->d.titolo,l2->d.titolo)==0)
            {
                p=newnode();

                p->d = l1->d;


                if ((*head)==NULL)
                {
                    (*head)=p;
                    (*tail)=p;
                }
                else
                {
                    (*tail)->next=p;
                    (*tail)=p;
                }
                p->next=NULL;

                samebook_rt(l1,l2->next, head, tail, copy_l2);

            }

            else {(samebook_rt(l1,l2->next,head, tail, copy_l2));}

            }
       else {samebook_rt(l1->next,copy_l2,head,tail, copy_l2);
    }
}

}


LINK samebook_rn(LINK l1, LINK l2, LINK copy_l2)
{

    LINK p=NULL;

    if ((l1==NULL)&&(l2==NULL))return (p);

    if (l1!=NULL)
        {
        if(l2!=NULL)
            {
            if (strcmp(l1->d.titolo,l2->d.titolo)==0)
            {
                p=newnode();

                p->d = l1->d;



                p->next=samebook_rn(l1,l2->next, copy_l2);
                return (p);

            }

            else {return(samebook_rn(l1,l2->next, copy_l2));}

            }
       else {
                return(samebook_rn(l1->next,copy_l2, copy_l2));
            }
    }
    return p;
}


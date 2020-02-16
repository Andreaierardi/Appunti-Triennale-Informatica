#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <assert.h>
#define BUFFER 100

typedef struct COORDINATE
{
    int x;
    int y;
} COORDINATE;

typedef struct linked_list
{
    COORDINATE d;
    struct linked_list *next;
} ELEMENT;


typedef ELEMENT *LINK;

LINK newnode(void)
{
    return (malloc(sizeof(ELEMENT)));
}

void crealista(LINK *lis);
void stampalista(LINK lis);
int contacoordinate(LINK lis, int x, int y);
LINK primoquadrante(LINK lis);
void scrivicoordinate(LINK lis,char *nomefile);

int main(int argc, char *argv[])
{
    LINK lista;
    lista=NULL;
    crealista(&lista);

    stampalista(lista);

    int conta;
    int x, y;
    printf("Quale coordinata vuoi sapere quante volte appare?(nel formato 'X Y') ");
    scanf("%d",&x);
    scanf("%d",&y);
    conta=contacoordinate(lista,x,y);
    printf("\nLa coodinata appare: %d VOLTE\n",conta);

    LINK quadrantepos=NULL;
    quadrantepos=primoquadrante(lista);
    printf("\nLE COORDINATE DEL PRIMO QUADRANTE SONO:\n");
    stampalista(quadrantepos);

    char *file = malloc(sizeof(char));


    printf("\nCome vuoi chiamare il file?: ");
    scanf("%s",file);
    scrivicoordinate(lista,file);

    return 0;
}


void crealista(LINK *lis)
{

    int n;
    LINK p;

    printf("Quante coordinate vuoi aggiungere? (n>=0)  ");
    scanf("%d",&n);
    if (n>=0)
    {
        for (int i=0; i<n; i++)
        {
            p=newnode();
            printf("Valore di x: ");
            scanf("%d",&p->d.x);
            printf("Valore di y: ");
            scanf("%d",&p->d.y);
            p->next=*lis;
            *lis=p;
        }
    }

    else {crealista(lis);}
}

void stampalista(LINK lis)
{
    printf("\n");
    while(lis!= NULL)
    {
        printf("%d\n",lis->d.x);
        printf("%d\n",lis->d.y);
        lis=lis->next;
    }
    printf("\n");
}

int contacoordinate(LINK lis, int x, int y)
{
    int count=0;
    while(lis!=NULL)
    {
        if((lis->d.x==x)&&(lis->d.y==y))
        {
            count++;
            lis=lis->next;
        }
        else{lis=lis->next;}
    }
    return (count);
}

 LINK primoquadrante(LINK lis)
 {
     LINK p, head, tail;
     head=NULL;
     tail=NULL;

     while(lis!=NULL)
     {
       if((lis->d.x>=0)&&(lis->d.y>=0))
       {
           p=newnode();
           p->d.x=lis->d.x;
           p->d.y=lis->d.y;

           p->next=NULL;

           if (head==NULL){head=p;tail=p;}
           else{tail->next=p;tail=p;}
       }
       lis=lis->next;
     }
     return (head);
 }

 void scrivicoordinate(LINK lis,char *nomefile)
 {
    int count=1;
    FILE *f=fopen(nomefile,"w");
    assert(f!=NULL);

    while(lis!=NULL)
    {
        fprintf(f,"Coordinata %d è: (%d,%d)\n",count,lis->d.x,lis->d.y);
        count++;
        lis=lis->next;
    }


 }

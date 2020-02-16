#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <assert.h>

typedef struct point
{
    int x;
    int y;

} POINT;

typedef struct linked_list
{
    POINT d;

    struct linked_list *next;
} ELEMENT;

typedef ELEMENT *LINK;

LINK newnode(void)
{
    return (malloc(sizeof(ELEMENT)));
}

LINK crealista();
void stampalista(LINK lis);
void delprimoq(LINK *lis);
void supequ(LINK lis,LINK *l1, LINK *l2);
LINK fusionlist(LINK lis, LINK lis2);

LINK complista(LINK lis, LINK lis2, int n, int m);

int main()
{
    LINK lista,listainf, listasup;
    LINK lista2=NULL;
    listasup=NULL;
    listainf=NULL;
    lista=crealista();
    stampalista(lista);
    lista2=crealista();
    /*
    puts("_______________________\nLE COORDINATE ESCLUSO IL PRIMO QUADRANTE");

    delprimoq(&lista);
    stampalista(lista);
    */

    supequ(lista,&listasup,&listainf);
    puts("_______________________\nLE COORDINATE SOPRA EQUATORE");
    stampalista(listasup);
    puts("_______________________\nLE COORDINATE SOTTO EQUATORE");
    stampalista(listainf);

    /*
    puts("_______________________\nLE COORDINATE DEL TERZO QUADRANTE SONO");
    LINK lista3;
    lista3=fusionlist(lista,lista2);
    stampalista(lista3);
    */

    LINK lista4;
    lista4=complista(lista,lista2,2,5);
    puts("_______________________\nLE COORDINATE DA 'n' a 'm':");
    stampalista(lista4);



}


LINK crealista()
{

    int n;
    LINK p,head,tail;
    head=NULL;
    tail=NULL;

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
            p->next=NULL;
            if (head==NULL){head=p;tail=p;}
            else{tail->next=p;tail=p;}

        }
    }

    return(head);
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

void delprimoq(LINK *lis)
{
    LINK p, head;
    if(lis!=NULL)
    {
        head=*lis;
        while(head->next!=NULL)
        {
            if ((head->next->d.x>=0)&&(head->next->d.y>=0))
            {
                p=head->next;
                head->next=head->next->next;
                free(p);
            }
            else head=head->next;
        }
    if(((*lis)->d.x>=0)&&((*lis)->d.y>=0)){p=*lis;*lis=(*lis)->next;free(p);}
    }
}

void supequ(LINK lis,LINK *l1, LINK *l2)
{
     LINK p,sopra,sotto;
    sopra=NULL;
    sotto=NULL;
    while(lis!=NULL)
    {
        p=newnode();
        p->d.x=lis->d.x;
        p->d.y=lis->d.y;
        p->next=NULL;

        if(lis->d.y>0)
        {

            if((*l1)==NULL)
            {
                *l1=p;
                sopra=p;
            }
            else
            {
                sopra->next=p;
                sopra=p;
            }
        }
        else
        {
            if((*l2)==NULL)
            {
                *l2=p;
                sotto=p;
            }
            else
            {
                sotto->next=p;
                sotto=p;
            }
        }
        lis=lis->next;
    }
}

LINK fusionlist(LINK lis, LINK lis2)
{
    LINK p, head, tail;
    head=NULL;
    tail=NULL;

    while((lis!=NULL)&&(lis2!=NULL))
          {
              if(((lis->d.x)<0)&&(lis->d.y<0))
              {
                  p=newnode();
                  p->d.x=lis->d.x;
                  p->d.y=lis->d.y;
                  p->next=NULL;

                  if(head==NULL){head=p;tail=p;}
                  else{tail->next=p; tail=p;}
              }
              if(((lis2->d.x)<0)&&(lis2->d.y<0))
              {
                  p=newnode();
                  p->d.x=lis2->d.x;
                  p->d.y=lis2->d.y;
                  p->next=NULL;

                  if(head==NULL){head=p;tail=p;}
                  else{tail->next=p; tail=p;}
              }
              lis=lis->next;
              lis2=lis2->next;
          }
    while(lis!=NULL)
          {
              if(((lis->d.x)<0)&&(lis->d.y<0))
              {
                  p=newnode();
                  p->d.x=lis->d.x;
                  p->d.y=lis->d.y;
                  p->next=NULL;

                  if(head==NULL){head=p;tail=p;}
                  else{tail->next=p; tail=p;}
              }

              lis=lis->next;

          }
    while(lis2!=NULL)
          {
              if(((lis2->d.x)<0)&&(lis2->d.y<0))
              {
                  p=newnode();
                  p->d.x=lis2->d.x;
                  p->d.y=lis2->d.y;
                  p->next=NULL;

                  if(head==NULL){head=p;tail=p;}
                  else{tail->next=p; tail=p;}
              }
              lis2=lis2->next;
          }
          return(head);
}

LINK complista(LINK lis, LINK lis2, int n, int m)
{
    LINK p, head, tail;
    head=NULL;
    tail=NULL;
    int pos=1;

    while((lis!=NULL)&&(lis2!=NULL))
    {
        p=newnode();

        if (pos<=n){p->d=lis->d;}
        if ((pos>n)&&(pos<=m))
        {
            if(lis2->d.y>lis->d.y)
            {
                p->d=lis2->d;
            }
            else (p->d=lis->d);
        }
        else
        {
            p->d=lis2->d;
        }
        p->next=NULL;
        if (head==NULL){head=p;tail=p;}
        else{tail->next=p; tail=p;}
        lis=lis->next;
        lis2=lis2->next;
        pos++;
    }

    while((lis!=NULL)&&(pos<=m))
    {
        p=newnode();
        p->d=lis->d;
        p->next=NULL;
        if (head==NULL){head=p;tail=p;}
        else{tail->next=p; tail=p;}
        lis=lis->next;
        pos++;
    }
    while((lis2!=NULL))
    {   if (pos>n)
        {
            p=newnode();
            p->d=lis2->d;
            p->next=NULL;
            if (head==NULL){head=p;tail=p;}
            else{tail->next=p; tail=p;}
            lis2=lis2->next;
            pos++;
        }
        else{pos++;}

    }

    return (head);
}

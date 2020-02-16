#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100
#define INIZ 0
//--------------------------------
//STRUTTURE
typedef struct STUDENT
{
    char cognome[20];
    char nome[20];
    int matricola;
    char esame[20];
    int crediti;
    int voto;
} STUDENT;
typedef struct linked_list
{
    STUDENT d;
    struct linked_list *next;

} ELEMENT;
typedef ELEMENT *LINK;
typedef ELEMENT *LINK;
LINK newnode(void)
{
    return (malloc(sizeof(ELEMENT)));
}


//--------------------------------
//RICHIAMO FUNZIONI
LINK crealistfromfile(char *nomefile);
void printlist(LINK lis);
int sumcredit(int matricola, LINK lis, int sum);
LINK creasplitcogn(char *cognome, LINK lis, int pos);
//--------------------------------
// MAIN
int main()
{
    LINK lista;
    lista=crealistfromfile("input-esame.txt");
    printlist(lista);

    int matricola;
    printf("Di quale matricola i crediti totali?\n");
    scanf("%d",&matricola);

    int somma=sumcredit(matricola, lista,INIZ);
    printf("%d\n",somma);

    LINK lissplit;
    char *cognome=(char *)malloc(sizeof(char));
    printf("Di quale persona vuoi vedere gli esami ?\n");
    scanf("%s",cognome);
    lissplit=creasplitcogn(cognome,lista, INIZ);

    printlist(lissplit);
}


//--------------------------------
//FUNZIONI

LINK crealistfromfile(char *nomefile)
 {
     LINK p, head, tail;
     head=NULL;
     tail=NULL;

     FILE *f=fopen(nomefile,"r");
     if (f==NULL)
     {
         puts("file vuoto");
     }
     char *s=(char *)malloc(sizeof(char));
     char *r;

     while (true)
     {
         r=fgets(s,BUFFER,f);
         if (r==NULL)
         {
             break;
         }
         p=newnode();
         sscanf(r,"%s %s %d %s %d %d",p->d.cognome,p->d.nome,&p->d.matricola,p->d.esame,&p->d.crediti,&p->d.voto);
        p->next=NULL;
        if (head==NULL){head=p; tail=p;}
        else {tail->next=p; tail=p;}

     }
     return(head);
 }

 void printlist(LINK lis)
 {  puts("-----------------");
     if (lis!=NULL)
     {
         printf("Cognome: %s\n",lis->d.cognome);
         printf("Nome: %s\n",lis->d.nome);
         printf("Matricola: %d\n",lis->d.matricola);
         printf("%s\n",lis->d.esame);
         printf("%d\n",lis->d.crediti);
         printf("%d\n",lis->d.voto);
         printf("\n");
         printlist(lis->next);
     }
 }

int sumcredit(int matricola, LINK lis, int sum)
 {
     if(lis!=NULL)
        {
        if(lis->d.matricola==matricola)
        {
            return(sum+sumcredit(matricola, lis->next, lis->d.crediti));


        }
        else{return(sumcredit(matricola,lis->next,lis->d.crediti));}
        }

        return (0);
    }

LINK creasplitcogn(char *cognome,LINK lis, int pos)
{
    LINK p, head, tail;
    head=NULL;
    tail=NULL;

    while(lis!=NULL)
    {
        if(strcmp(cognome,lis->d.cognome)==0)
        {
            p=newnode();
            p->d=lis->d;
            p->next=NULL;

            if(head==NULL){head=p; tail=p;}
            else {tail->next=p;tail=p;}
        }
        lis=lis->next;
    }
    return (head);
}

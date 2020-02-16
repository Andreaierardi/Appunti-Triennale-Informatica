#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100

typedef struct PERSON
{
    char nome[12];
    char cognome[10];
    int eta;

} DATA;
//typedef int DATA;

typedef struct linked_list
{
    DATA d;

    struct linked_list *next;
} ELEMENT;


typedef ELEMENT *LINK;

LINK newnode(void)
{
    return (malloc(sizeof(ELEMENT)));
}

LINK crealista();
LINK crealistaperson();
void stampalista(LINK lis);
void stampapersonlista(LINK lis);

void stampanelem(LINK lis, int n);
void stampanperson(LINK lis, int n);

LINK rubrica(char *rubrica);

int main(int argc, char *argv[])
{
    int n=atoi(argv[1]);
    LINK lista;

   //lista=crealista();
   // stampalista(lista);
   // stampanelem(lista,n);
    //lista=crealistaperson();
    //stampapersonlista(lista);
    //stampanperson(lista,n);
    lista=rubrica("rubrica.txt");
    stampapersonlista(lista);
    stampanperson(lista,n);
    return 0;

}

LINK rubrica(char *rubrica)
{

    LINK p,head, tail;
    head=NULL;
    tail=NULL;

    FILE *f= fopen(rubrica,"r");
    if (f==NULL)
    {
        printf("Impossibile aprire il file");
        return (NULL);
    }


    char *r, s[BUFFER];

    while(true)
    {
         r = fgets(s,BUFFER,f);

         if (r==NULL)
         {
             break;
         }
        else{
        p=newnode();
        sscanf(r,"%s %s %d",p->d.nome,p->d.cognome,&p->d.eta);

        //p=newnode();
        //strcpy(p->d.nome,nome);
        //strcpy(p->d.cognome,cognome);
        //p->d.eta=eta;
        p->next=NULL;
        if (head==NULL){head=p; tail=p;}
        else{tail->next=p; tail=p;}

        }
    }
        return (head);
}

/*
void stampalista(LINK lis)
{
    printf("\n");
    while(lis!= NULL)
    {
        printf("%d\n",lis->d);
        lis=lis->next;
    }
}
*/
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

void stampanperson(LINK lis, int n)
{   int count=0;
    if (n==1){printf("\nSTAMPO SOLO PRIMA PERSONA\n");}
    else {printf("\nSTAMPO SOLO PRIME %d PERSONE:\n",n);}

    while((lis!= NULL)&&(count<n))
    {   printf("--------------------------------------\n");
        printf("%d)\n",count+1);
        printf("%s\n",lis->d.nome);
        printf("%s\n",lis->d.cognome);
        printf("%d\n",lis->d.eta);
        lis=lis->next;
        count++;
    }
    printf("--------------------------------------\n");
}
/*
void stampanelem(LINK lis, int n)
{   int count=0;
    printf("\nSTAMPO SOLO %d ELEMENTI:\n",n);
    while((lis!= NULL)&&(count<n))
    {
        printf("%d\n",lis->d);
        lis=lis->next;
        count++;
    }
}
*/
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


/*
LINK crealista()
{
    int numelem;
    int numero;
    LINK p,head, tail;
    head=NULL;
    tail=NULL;

    printf("Quanti numeri vuoi inserire? \n");
    scanf("%d",&numelem);
    if (numelem==0)
    {
        return(NULL);
    }

    else
    {
        for (int i=0; i<numelem; i++)
        {
            printf("Inserisci il numero:  ");
            scanf("%d", &numero);

            p=newnode();
            p->d=numero;
            p->next=NULL;

            if (head==NULL){head=p; tail=p;}
            else{tail->next=p; tail=p;}

        }
        return (head);
    }

}

*/

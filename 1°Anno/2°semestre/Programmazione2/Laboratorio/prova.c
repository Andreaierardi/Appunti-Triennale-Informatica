#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
//------------------------------------
//STRUCTURES(+ NEWNODE)

typedef struct STUDENTE
{
    char cognome[20];
    char nome[20];
    int matricola;
    char esame[20];
    int crediti;
    int voto;
} STUDENTE;


typedef struct linked_list
{
    STUDENTE d;
    struct linked_list  *next;
} ELEMENT;
typedef  ELEMENT *LINK;

LINK newnode()
{
    return(malloc(sizeof(ELEMENT)));
}
//------------------------------------
//FUNCTION CALLS
LINK createfromfile();
void printlis_r(LINK lis);
int contacrediti(LINK lis, int matricola);
LINK listfromsurname(LINK lis);
void cancella(LINK *lis);
//------------------------------------
//MAIN

int main()
{
//   1)
    LINK lista= createfromfile();

//   2)
    printlis_r(lista);

//   3)
/*
    int matricola;
    printf("\n------------------------------------\n\n");
    printf("Di quale studente vuoi sapere i crediti totali?: ");
    scanf("%d",&matricola);

    int creditiTot=contacrediti(lista, matricola);

    printf("\nCrediti totali dello studente:     %d\n",creditiTot);
    printf("\n------------------------------------\n\n");
*/
//   4)
    LINK  lista2=listfromsurname(lista);

    printf("\n--------------------------\nNUOVA LISTA \n");
    printlis_r(lista2);

    printf("\n--------------------------\nAGGIORNAMENTO VECCHIA \n");
    printlis_r(lista);
}

//------------------------------------
//FUNCTIONS

LINK createfromfile()
{
    LINK p, head, tail;
    head=NULL; tail=NULL;
    p=NULL;

    FILE *f = fopen("input-esame.txt","r");

    if (f==NULL)
    {
        printf("ERRORE NELL'APERTURA DEL FILE");
        return (NULL);
    }

    STUDENTE tmp; //Non sono sicuro che il file sia vuoto o meno quindi creo una struttura temporanea
    while(fscanf(f, "%s %s %d %s %d %d",tmp.cognome, tmp.nome, &tmp.matricola, tmp.esame, &tmp.crediti, &tmp.voto)!=EOF)
    {
    p=newnode();  // se esiste creo un nuovo nodo
    p->d= tmp;
    if (head==NULL)
        {
            head=p;
            tail=p;
        }

    else{tail->next=p; tail=p;}
    p->next=NULL;
    }


        return (head);
}

void printlis_r(LINK lis)
{
    if (lis!=NULL)
    {
        printf("\nCOGNOME:  %s\n",lis->d.cognome);
        printf("NOME:  %s\n", lis->d.nome);
        printf("MATRICOLA:  %d\n",lis->d.matricola);
        printf("ESAME:  %s\n", lis->d.esame);
        printf("CREDITI:  %d\n", lis->d.crediti);
        printf("VOTO:  %d\n",lis->d.voto);
        printlis_r(lis->next);
    }
}


int contacrediti(LINK lis, int matricola)
{
    if(lis==NULL)return (0);
    else
    {
        if(lis->d.matricola==matricola)
        {
            return(lis->d.crediti+contacrediti(lis->next,matricola));
        }

        else{contacrediti(lis->next, matricola);}
    }
    return (0);
}

LINK listfromsurname(LINK lis)
{
    LINK head, tail , p;

    head=NULL;
    tail= NULL;

    char *cognome= (char *)malloc(sizeof(char));
    printf("Di quale studente vuoi vedere gli esami? : ");
    scanf("%s",cognome);

    while (lis!=NULL)
    {
        if(strcmp(lis->d.cognome,cognome)==0)
        {
            p=newnode();
            p->d=lis->d;

            if (head==NULL){head=p; tail =p;}
            else {tail->next=p; tail=p;}
            p->next=NULL;
            cancella(&lis);


        }

        lis=lis->next;
    }

    return (head);
}

void cancella(LINK *lis)
{
   LINK p;
    if (*lis != NULL)
    {
        p=*lis;
        *lis=(*lis)->next;
        free(p);
    }
}

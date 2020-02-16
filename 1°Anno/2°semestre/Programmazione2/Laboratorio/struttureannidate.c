#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAX 3
#define N 50
#define MAX_AMICI 50
//---------------------------------------
//structures
typedef struct ind
{
    char via[N];
    int num;
    int CAP;
    char localita[N];
} INDIRIZZO;

typedef struct pers
{
    char nome[N];
    char cognome[N];
    int eta;
    INDIRIZZO i;
    int codice_pers;
    int num_amici;
    int amici[MAX_AMICI];
} PERSON;

typedef struct linked_list
{
    PERSON d;
    struct linked_list  *next;
} ELEMENT;

typedef  ELEMENT *LINK;

LINK newnode(){return(malloc(sizeof(ELEMENT)));}
//---------------------------------------
//function calls
void readnperson(LINK lista);
LINK aperturafile(char *nomefile);
void searchprint(LINK lista);
void printnage(LINK lista);
void printplaceage(LINK lista);
//---------------------------------------
//main
int main()
{
    printf("\nQuale operazione vuoi eseguire?\n");
    printf("\n1. Lettura di n persone da input\n");
    printf("2. Ricerca e stampa di una persona dati in input nome e cognome \n");
    printf("3. Dato in input un range [min, max], stampa della lista di persone la cui età è compresa nel range\n");
    printf("4. Data in input una località, stampa della lista di persone che abitano in quella località e la loro età media\n");
    printf("5. Data in input una località, stampa della lista di persone che abitano in quella località e la loro età media\n");

    int scelta  ;
    scanf("%d",&scelta);

    LINK lista=aperturafile("indirizzi.txt");

    switch (scelta)
    {
    case 1:
        readnperson(lista);

    break;

    case 2:
        searchprint(lista);

    break;

    case 3:
        printnage(lista);

    break;

    case 4:
        printplaceage(lista);

    break;

    case 5:
       // printpersonplace();
        printf("Scelta 5\n");
    break;

    default:
        printf("\n---------------Non hai compiuto una scelta adeguata------------------\n---------------------------------------------------------------------\n");
        main();
    break;

    }



}

LINK aperturafile(char *nomefile)
{
    LINK p, head, tail;
    head=NULL;
    tail=NULL;

    FILE *fp;
    fp=fopen(nomefile,"r");

    while(fp!=NULL)
    {
        int am1,am2;
        p=newnode();
        int g = fscanf(fp, "%s %s %d %s %d %d %s %d %d %d %d",p->d.nome,p->d.cognome,&p->d.eta,p->d.i.via,&p->d.i.num,&p->d.i.CAP,p->d.i.localita,&p->d.codice_pers,&p->d.num_amici,&am1,&am2);
        p->d.amici[0]=am1;
        p->d.amici[1]=am2;
        p->next=NULL;

        if(head==NULL){head=p;tail=p;}
        else {tail->next=p;tail=p;}

        if (g==EOF)
        {
             break;
        }
    }
    return(head);

}

void readnperson(LINK lista)
{


    printf("Quante persone vuoi leggere?: ");
    int quante;
    scanf("%d",&quante);
    int count=0;
    while ((lista!=NULL)&&(count!=quante))
    {
        puts("");

        printf("Nome: %s\n",lista->d.nome);
        printf("Cognome: %s\n",lista->d.cognome);
        printf("Eta: %d\n",lista->d.eta);
        printf("Via: %s\n",lista->d.i.via);
        printf("Numero Civico: %d\n",lista->d.i.num);
        printf("CAP: %d\n",lista->d.i.CAP);
        printf("Localita: %s\n",lista->d.i.localita);
        printf("Codice Personale: %d\n",lista->d.codice_pers);
        printf("Numero Amici: %d\n",lista->d.num_amici);
        printf("Codice 1^ Amico: %d\n",lista->d.amici[0]);
        printf("Codice 2^ Amico : %d\n",lista->d.amici[1]);

        lista=lista->next;
        count++;
    }
}

void searchprint(LINK lista)
{
    PERSON p;
    printf("Scrivi nome e cognome della persona che vuoi cercare: ");
    scanf("%s",p.nome);
    scanf("%s",p.cognome);

    while(lista!=NULL)
    {
        if((strcmp(lista->d.nome,p.nome)==0)&&(strcmp(lista->d.cognome,p.cognome)==0))
        {
        puts("");

        printf("Nome: %s\n",lista->d.nome);
        printf("Cognome: %s\n",lista->d.cognome);
        printf("Eta: %d\n",lista->d.eta);
        printf("Via: %s\n",lista->d.i.via);
        printf("Numero Civico: %d\n",lista->d.i.num);
        printf("CAP: %d\n",lista->d.i.CAP);
        printf("Localita: %s\n",lista->d.i.localita);
        printf("Codice Personale: %d\n",lista->d.codice_pers);
        printf("Numero Amici: %d\n",lista->d.num_amici);
        printf("Codice 1^ Amico: %d\n",lista->d.amici[0]);
        printf("Codice 2^ Amico : %d\n",lista->d.amici[1]);


        }

        lista=lista->next;
    }
}


void printnage(LINK lista)
{
    int min;
    int max;
    printf("Scrivi eta min e max delle persone che vuoi cercare: ");
    scanf("%d",&min);
    scanf("%d",&max);

    while(lista!=NULL)
    {
        if((lista->d.eta>=min)&&(lista->d.eta<=max))
        {
        puts("");

        printf("Nome: %s\n",lista->d.nome);
        printf("Cognome: %s\n",lista->d.cognome);
        printf("Eta: %d\n",lista->d.eta);
        printf("Via: %s\n",lista->d.i.via);
        printf("Numero Civico: %d\n",lista->d.i.num);
        printf("CAP: %d\n",lista->d.i.CAP);
        printf("Localita: %s\n",lista->d.i.localita);
        printf("Codice Personale: %d\n",lista->d.codice_pers);
        printf("Numero Amici: %d\n",lista->d.num_amici);
        printf("Codice 1^ Amico: %d\n",lista->d.amici[0]);
        printf("Codice 2^ Amico : %d\n",lista->d.amici[1]);
        }

        lista=lista->next;
    }
}

void printplaceage(LINK lista)
{
    PERSON p;
    printf("Scrivi localita della persona che vuoi cercare: ");
    scanf("%s",p.i.localita);

    while(lista!=NULL)
    {
        if((strcmp(lista->d.i.localita,p.i.localita)==0))
        {
        puts("");

        printf("Nome: %s\n",lista->d.nome);
        printf("Cognome: %s\n",lista->d.cognome);
        printf("Eta: %d\n",lista->d.eta);
        printf("Via: %s\n",lista->d.i.via);
        printf("Numero Civico: %d\n",lista->d.i.num);
        printf("CAP: %d\n",lista->d.i.CAP);
        printf("Localita: %s\n",lista->d.i.localita);
        printf("Codice Personale: %d\n",lista->d.codice_pers);
        printf("Numero Amici: %d\n",lista->d.num_amici);
        printf("Codice 1^ Amico: %d\n",lista->d.amici[0]);
        printf("Codice 2^ Amico : %d\n",lista->d.amici[1]);


        }

        lista=lista->next;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100

//structures
typedef struct ESAMI
{
    int codice;
    int voto;
    int matricola;
    int lode;
}   ESAME;


typedef struct linked_list
{
    ESAME d;
    struct linked_list  *next;
} ELEMENT;
typedef  ELEMENT *LINK;

LINK newnode(){return(malloc(sizeof(ELEMENT)));}


//function calls

LINK createlist( int n);
void printlis_r(LINK lis);
LINK  course_r(LINK lis, int codice);
void createfile_r(LINK lis, char *nomefile, int verifica, FILE *fp);
void stampa_votomassimo(LINK lis,LINK p);
//main

int main()
{
    int n;
    printf("Quanti esami vuoi inserire?: ");
    scanf("%d",&n);

    LINK lista=createlist(n);

    /*
    int codice;
    printf("Quale corso vuoi verificare?: ");
    scanf("%d",&codice);
    LINK listcodice=course_r(lista, codice);
    printlis_r(listcodice);
    */

    createfile_r(lista,"EXAMS.txt",0 , NULL);



    stampa_votomassimo(lista,NULL);

    return 0;

}



//functions
LINK    createlist( int n)
{
    LINK head,p;
    LINK head2=NULL;
    head=NULL;
    int pos=1;

    while(pos<=n){
    p=newnode();
    puts("inserisci codice esame\n");
    scanf("%d",&p->d.codice);
    puts("inserisci matricola esame\n");
    scanf("%d",&p->d.matricola);
    puts("inserisci voto esame\n");
    scanf("%d",&p->d.voto);

    while((p->d.voto<18)||(p->d.voto>30)){
         puts("inserisci voto esame\n");
         scanf("%d",&p->d.voto);
    }
    if(p->d.voto==30){
    puts("inserisci lode esame\n");
    scanf("%d",&p->d.lode);
    }
    p->next=NULL;
    if (head==NULL){head=p;}
    else //lista non vuota
    {
       if(head->d.codice>=p->d.codice){
          p->next=head;
          head=p;
        }
        else{
          head2=head;
          int inserito =0;
          while(head2->next!=NULL && inserito ==0){
            if (head2->next->d.codice>= p->d.codice){
                //inserimento in lista in testa
                p->next=head2->next;
                head2->next=p;

                inserito =1;

            }
            else
                head2= head2->next;

          }//inserimento in coda
          if (inserito==0)
          {
              head2->next=p;
          }
        }
    }

    pos++;

    }
    return head;

}

void printlis_r(LINK lis)
{
    while(lis!=NULL)
    {

    printf("\nCodice Esame: %d\n",lis->d.codice);
    printf("Voto: %d\n",lis->d.voto);
    printf("Matricola:  %d\n",lis->d.matricola);
    printf("Lode:  %d\n",lis->d.lode);
    lis=lis->next;
    }
}


LINK  course_r(LINK lis, int codice)
{
    LINK p, head, tail;

    head=NULL;
    tail=NULL;

    if(lis!=NULL)
    {

        if(lis->d.codice==codice)
        {
            p=newnode();
            p->d=lis->d;
            p->next=course_r(lis->next, codice);


            if(head==NULL)
            {
                head=p;
                tail=p;
            }

            else{tail->next=p; tail=p;}
        }
    }

    return (head);

}


void createfile_r(LINK lis, char *nomefile, int verifica, FILE *fp)
{

    if (lis!=NULL)
    {


        if ((verifica)==0)
        {
            FILE *fp=fopen(nomefile,"w");
            if (fp==NULL)
            {
                printf("ERROR");
            }
            else
                {
                (verifica)=1;
                fprintf(fp, "Codice Corso: %d\nVoto: %d\nMatricola: %d\nLode: %d\n\n", lis->d.codice,lis->d.voto,lis->d.matricola,lis->d.lode);
                createfile_r(lis->next,nomefile,verifica, fp);

                }
        }

        else
            {

            fprintf(fp, "Codice Corso: %d\nVoto: %d\nMatricola: %d\nLode: %d\n\n", lis->d.codice,lis->d.voto,lis->d.matricola,lis->d.lode);
            createfile_r(lis->next,nomefile,verifica, fp);
            }
    }

    else
        {
            if(fp==NULL)
                fclose(fp);
        }
}


void stampa_votomassimo(LINK lis,LINK p)
{
     if (lis!=NULL)
        {

        if(p==NULL)
        {
            p=newnode();
            p->d=lis->d;
            stampa_votomassimo(lis->next,p);
        }

        else
            {
                if(lis->d.codice==p->d.codice)
                {

                    if (lis->d.voto>p->d.voto)
                        {
                            p->d=lis->d;
                            stampa_votomassimo(lis->next,p);
                        }

                    else
                        {
                            stampa_votomassimo(lis->next,p);
                        }

                }
                else
                    {
                    printf("\nCodice esame: %d\nMatricola:%d\nVoto massimo: %d\n",p->d.codice,p->d.matricola,p->d.voto);
                    if(p->d.voto==30)
                    {
                        printf("%d",p->d.lode);
                    }
                    printf("\n");
                    stampa_votomassimo(lis->next,lis);


                        }
            }
        }

    else
        {
            printf("\nCodice esame: %d\nMatricola:%d\nVoto massimo: %d\n",p->d.codice,p->d.matricola,p->d.voto);
            if(p->d.voto==30)
                {
                    printf("%d",p->d.lode);
                }
                printf("\n");

        }
}


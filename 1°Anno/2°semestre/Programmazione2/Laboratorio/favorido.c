#include <stdio.h>    // permette di usare scanf printf
#include <stdlib.h>   // conversioni stringa/numero rand() abs() exit() etc ...
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <string.h>   // permette di usare funzioni strlen() strcmp() etc
/*Data la una lista di Esami (struttura Esame definita su CodiceCorso -intero-, voto - intero- Matricola - intero- lode - intero)

Voto è un intero compreso tra 18 e 30

Lode vale 1 se c'è la lode (voto deve essere uguale a 30) altrimenti 0

Scrivere:

*) una funzione iterativa crei una lista inserendo in modo ordinato  crescente un numero n (n è un parametro della funzione) di nuovo Esami
(l'ordimamento è fatto in base al codice del corso)

*) una funzione ricorsiva che data una lista restituisca in output una lista contenente tutti gli Esami di un dato corso (codice passato in input)

*) una funzione ricorsiva che dato in input una lista e il nome di un file salvi il contenuto della lista

*) una funzione ricorsiva che stampi a video per ogni Esame quello con il voto massimo
*/
typedef struct esami{
int codicecorso;
int voto;
int matricola;
int lode;
}
esami;


struct linked_list
{
    esami d;
    struct linked_list *next;
};
typedef struct linked_list ELEMENT;
typedef ELEMENT *LINK;

LINK newnode(void){
return (malloc(sizeof(ELEMENT)));
}
LINK listaesami(LINK lis,int codice);
LINK buildlist(int n);
void stampa(LINK lis);
void scrivifile(LINK lis,char nome[],int flag,FILE *f);
void stampa_votomassimo(LINK lis,LINK p);

int main(){
LINK lis;
int t;
char nome[50];
LINK lis2;
int n;
puts("quanti esami vuoi inserire?\n");
scanf("%d",&n);
lis=buildlist(n);
stampa (lis);
puts("inserisci codice che vuoi ricercare\n");
scanf("%d",&t);
lis2=listaesami(lis,t);
stampa(lis2);
puts("inserisci nome file\n");
scanf("%s",nome);
scrivifile(lis,nome,1,NULL);
stampa_votomassimo(lis,NULL);

}
LINK buildlist(int n){
LINK head,p;
LINK head2=NULL;
head=NULL;
int pos=1;
while(pos<=n){
    p=newnode();
    puts("inserisci codice esame\n");
    scanf("%d",&p->d.codicecorso);
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
       if(head->d.codicecorso>=p->d.codicecorso){
          p->next=head;
          head=p;
        }
        else{
          head2=head;
          int inserito =0;
          while(head2->next!=NULL && inserito ==0){
            if (head2->next->d.codicecorso>= p->d.codicecorso){
                //inserimento in lista
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

void stampa(LINK lis){
while (lis!=NULL){
    printf("codice corso %d ",lis->d.codicecorso);
    printf("matricola %d ",lis->d.matricola);
    printf("voto %d ",lis->d.voto);
    if (lis->d.voto==30){
    printf("lode %d",lis->d.lode);
    }
    puts("\n");
    lis=lis->next;
}
}
/*una funzione ricorsiva che data
una lista restituisca in output una lista contenente tutti gli Esami di un dato corso (codice passato in input)*/
LINK listaesami(LINK lis,int codice){
    LINK p;

    if(lis==NULL) return NULL;
    else{
        if (lis->d.codicecorso==codice){
            p=newnode();
            p->d=lis->d;
            p->next=listaesami(lis->next,codice);
            return p;

        }
        else{
            return listaesami(lis->next,codice);
        }
    }

}
//una funzione ricorsiva che dato in input una lista e il nome di un file salvi il contenuto della lista
void scrivifile(LINK lis,char nome[],int flag,FILE *f){
    if (flag==1){
       FILE *f= fopen(nome,"w");
        if (lis!=NULL){
        if (f==NULL){
            printf("impossibile aprire il file\n");
        }
        else{
                fprintf(f,"%d %d %d ",lis->d.codicecorso,lis->d.matricola,lis->d.voto);
                if (lis->d.voto==30){
                    fprintf(f,"%d",lis->d.lode);
                }
                fprintf(f,"\n");
                scrivifile(lis->next,nome,0,f);

        }
        }
        else{
            fclose(f);
        }
    }
    else{
        if (lis!=NULL){
        if (f==NULL){
            printf("impossibile aprire il file\n");
        }
        else{
                fprintf(f,"%d %d %d ",lis->d.codicecorso,lis->d.matricola,lis->d.voto);
                if (lis->d.voto==30){
                    fprintf(f,"%d",lis->d.lode);
                }
                fprintf(f,"\n");
            scrivifile(lis->next,nome,0,f);

        }

    }
    else{
        fclose(f);
    }
    }
}

//una funzione ricorsiva che stampi a video per ogni Esame quello con il voto massimo
void stampa_votomassimo(LINK lis,LINK p){
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
                if(lis->d.codicecorso==p->d.codicecorso)
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
                    printf("%d %d %d ",p->d.codicecorso,p->d.matricola,p->d.voto);
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
            printf("%d %d %d ",p->d.codicecorso,p->d.matricola,p->d.voto);
            if(p->d.voto==30)
                {
                    printf("%d",p->d.lode);
                }
                printf("\n");

        }
}

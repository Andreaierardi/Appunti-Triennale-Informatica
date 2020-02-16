#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define Num 8
#define RUN 100
///Andrea Ierardi Matricola: 20018785
///Edoardo Favorido Matricola: 20018971
///Marco Rizzi Matricola: 20019238


///Funzioni per la creazione di nodi
typedef struct studente
{
    long matricola;
    char cognome[30];
    char nome[30];
} *Studente;

typedef struct Nodo
{
    Studente  inf;
    struct Nodo *sinistro;
    struct Nodo *destro;
} Nodo;

long *MATRICOLE; /* array di chiavi */
int numElementi;

///Funzioni per la creazione di alberi

///Richiamo funzioni
Nodo *makeNodo (Studente inf);
Nodo *inserisci (Nodo *root, Studente inf);
Nodo *carica_albero(char*nome,int n);
Studente cercaAbr(Nodo *r, long matricola,int *f);
bool cercaFlat(Nodo *r,long matricola, int *f);
void benchmark();
void stampasufile(char *nome, int *array,int lung, FILE *fp);


///Funzione main
int main()
{
    benchmark();
    return 0;
}

void benchmark()
{
    FILE *fp = fopen("ris.csv","w");
    if (fp == NULL){perror("Errore apertura file");exit(1);}
    int dimensioni[Num] = { 10, 20, 30, 40, 50, 60, 70 , 80};
    srand(time(NULL));
    char nome[20] = "studenti.txt";
    int flat, abr, tmp, tmp2;
    tmp = tmp2= 0;
    flat = abr = 0 ;

    int flat_array[Num];
    int abr_array[Num];
    fprintf(fp,"DIMENSIONI,");
    for (int i = 0 ; i < Num; i++)
    {
        if (i+1 == Num) fprintf(fp,"%d\n",dimensioni[i]);
        else fprintf(fp,"%d,",dimensioni[i]);
    }
    printf("\n==========Risultati==========\n");
    for (int i = 0 ; i < Num; i++)
    {

        for(int r = 0 ; r < RUN ; r++)
        {
            tmp=0;
            tmp2=0;

            int N = dimensioni[i];
            int indice = rand()%N;
            numElementi= 0;
            Nodo *r  = carica_albero(nome,N);

            cercaAbr(r,MATRICOLE[indice],&tmp);
            abr+= tmp;

            cercaFlat(r,MATRICOLE[indice],&tmp2);
            flat += tmp2;
        }
        printf("Flat %d: %d\nAbr %d: %d\n",i,flat/RUN,i,abr/RUN);
        flat_array[i]= flat/RUN;
        abr_array[i]= abr/RUN;

    }
    puts("------------------------");
    stampasufile("Flat",flat_array,Num,fp);
    stampasufile("Abr",abr_array,Num, fp);

    fclose(fp);
}

void stampasufile(char *nome, int *array,int lung, FILE *fp)
{
    fprintf(fp,"%s,",nome);
    for (int i = 0 ; i<lung ; i++)
    {
        if(i+1 == lung)fprintf(fp,"%d\n",array[i]);
        else fprintf(fp,"%d,",array[i]);
    }
}
Nodo *makeNodo (Studente inf)
{
    Nodo *al = (Nodo *) malloc(sizeof(Nodo));
    if (al != NULL)
    {
        al -> destro = al -> sinistro = NULL;
        al -> inf = inf;
    }
    return al;

}

Nodo *inserisci (Nodo *root, Studente inf)
{
    if (root == NULL) root = makeNodo(inf);
    else if ((inf->matricola) < (root->inf->matricola ))
        root->sinistro = inserisci(root->sinistro,inf);
    else if (inf->matricola > root->inf->matricola )
        root->destro = inserisci(root->destro,inf);
    return root;
}

Nodo *carica_albero(char*nome,int n)
{
    Nodo *r = NULL;
    FILE* f=fopen(nome,"r");
    if (f==NULL)
    {
        perror("Errore apertura file");
        exit(1);
    }
    MATRICOLE=(long *)malloc(n*sizeof(long));
    for ( int i = 0 ; i< n ; i++)
    {
        Studente inf= malloc(sizeof(struct studente));
        int e=fscanf(f,"%ld %s %s",&inf->matricola,inf->nome,inf->cognome);//legge dal file
        if(e!=3)
        {
            perror("Errore letture");
            exit(1);
        }
        r = inserisci(r,inf);
        MATRICOLE[numElementi]=inf->matricola;
        numElementi++;
    }
    int e = fclose(f);
    if (e!= 0)
    {
        perror("Errore chisura file");
        exit(1);
    }
    return r;
}

Studente cercaAbr (Nodo *r, long matricola,int *f)
{
    *f = *f+1;
    if (r == NULL) return NULL;
    if ((r->inf->matricola) == matricola) return r->inf;
    if (r->inf->matricola > matricola) return cercaAbr (r->sinistro, matricola,f);
    else return cercaAbr (r->destro, matricola,f);
}

bool cercaFlat(Nodo *r,long matricola, int *f)
{

    *f= *f+1;
    if (r == NULL) return false;
    if (r->inf->matricola == matricola) return true;
    if (cercaFlat(r->sinistro,matricola, f))return true;
    if (cercaFlat(r->destro,matricola,f))return true;
    return false;

}

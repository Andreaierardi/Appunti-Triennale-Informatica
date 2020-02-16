# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <assert.h>
#include <time.h>
///Andrea Ierardi    20018785
///Marco Camillo Rizzi 20019238
///Edoardo Favorido    20018971

typedef struct studente//studente
{
    long matricola; //matricola
    char nome[40]; //nome
    char cognome[40]; //cognome
} studente;


void stampa(studente *e);
void inserisci_stud(char *nome,studente *HT[], int m,int n);
int hash_insert(studente *HT[],studente *e,int m);
int hash_search(studente *HT[],studente *e,int m);
int h(long k,int i,int m);
int h1 (long k, int m);
int h2 (long k, int m);
bool primo(int n);


int main(int argc, char *argv[])
{
    int e; //Controllo scanf
    int n;///numero studenti
    int m;///Dim tabella hash
    if(argc!=4)
    {
        fprintf(stderr,"\n\t Uso :%s+n+m numero primo+nomefile\n",argv[0]);
        return -1;

    }

    n=atoi(argv[1]);
    m=atoi(argv[2]);
    while(!primo(m))
    {
        puts("numero non primo, inserisci di nuovo\n");
        e = scanf("%d",&m);
        if (e!=1) {perror("Errore inserimento dati");exit(1);}
    }
    assert(n>0);
    assert (m>0);
    studente *HT[m]; //tabella hash creata staticamente va bene lo stesso
    for(int i=0; i<m; i++)
    {
        HT[i]=NULL; //inizializzo a NULL tutti i blocchi.
    }
    int risposta;
    inserisci_stud(argv[3],HT,m,n);
    puts("Vuoi cercare uno studente 1=si 0=no\n");
    e = scanf("%d",&risposta);
    if (e!=1) {perror("Errore inserimento dati");exit(1);}

    while(risposta==1)
    {
        studente *el=malloc(sizeof(studente));
        puts("Inserisci la matricola dello studente che vuoi cercare\n");
        e = scanf("%ld",&el->matricola);
        if (e!=1) {perror("Errore inserimento dati");exit(1);}

        hash_search(HT,el,m);
        puts("Vuoi cercare un altro studente 1=si 0=no\n");
        e = scanf("%d",&risposta);
        if (e!=1) {perror("Errore inserimento dati");exit(1);}

    }

    return 0;
}



///FUNZIONE INSERIMENTO:
void inserisci_stud(char *nome,studente *HT[], int m,int n)
{
    FILE*f=fopen(nome,"r");

    if (f==NULL)
    {
        perror("Errore apertura file");
        exit(1);
    }
    for ( int i=0 ; i< n ; i++)
    {
        studente *el=malloc(sizeof(studente));
        int e=fscanf(f,"%ld %s %s",&el->matricola,el->nome,el->cognome);//legge dal file
        if(e!=3)
        {
            perror("Errore letture");
            exit(1);
        }
        int r = hash_insert(HT,el,m);
        printf("tentativi fatti per inserire il dato: %d\n",r);
    }
    int e = fclose(f);
    if (e!= 0)
    {
        perror("Errore chisura file");
        exit(1);
    }

}

///INSERT

int hash_insert(studente *HT[],studente *e,int m)
{
    int i=0;
    do
    {
        int j=h((e->matricola),i,m);
        if(HT[j]==NULL)
        {
            HT[j]=e;
            return i+1;//ritorniamo numero tentativi??i??
        }
        else
        {
            i=i+1;
        }
    }
    while (i!=m);
    return -1;
}
///SEARCH
int hash_search(studente *HT[],studente *e,int m)
{
    int i=0;//1 o 0;  ///Numero hit per cui cerca
    int j=0;
    do
    {
        j=h(e->matricola,i,m);
        if(HT[j]->matricola==e->matricola)
        {
            stampa(HT[j]);
            return i+1;//ritorniamo numero tentativi +1 perche i parte da 0
        }
        else
        {
            i++;
        }
    }
    while((HT[j]!=NULL)&&(i!=m)); //Numero tentativi non è uguale alla lunghezza della tabella
    return -1;
}

///STAMPA STUDENTI
void stampa(studente *e)
{
    printf("Matricola: %ld nome: %s cognome: %s \n",e->matricola,e->nome,e->cognome);
}

///FUNZIONI PER HASHING DOPPIO
int h(long k,int i,int m)
{
    return((h1(k,m)+i*h2(k,m))%m);
}
int h1 (long k, int m)
{
    return (k%m);
}
int h2(long k, int m)
{
    return (1+(k%(m-1))); //Se m non è primo devo fare h2
}

///FUNZIONE PRIMO

// funzione per stabilire se n e' primo
bool primo(int n)
{
    if(n<2) return false;
    if(n%2==0) return (n==2);
    for (int i=3; i*i<=n; i += 2)
        if(n%i==0) return false;
    return true;
}

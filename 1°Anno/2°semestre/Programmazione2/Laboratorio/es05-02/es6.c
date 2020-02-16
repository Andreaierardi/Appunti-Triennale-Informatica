#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <assert.h>
#define BUFFER 100
#define INIZ 0
//-------------------------------------
//struttura person e list
typedef struct person
{
    char nome[20];
    char cognome[20];
    int eta;
} PERSON;

//-------------------------------------
//richiamo funzioni
void printarr_rt(PERSON a[], int n, int pos);
void buildarrayfile(PERSON array[],int n,char *rubrica, int *m);
int minage(PERSON array[],int n);
int maxage(PERSON array[],int n);
void personminage(PERSON array[],int n,int minage, char *nome , char *cognome);
void personmaxage(PERSON array[],int n,int maxage, char *nome , char *cognome);
int summag(PERSON array[],int n, int pos);
int palindromo(char *A);
int palindromo_r(char *A, int n);
void printpersonpalindrome(PERSON a[], int n, int pos);
void toUPPER(char *s);
//-------------------------------------
//main
int  main ()
{
    /*
    int n;
    printf("Quante persone vuoi aggiungere ? ");
    scanf("%d",&n);

    PERSON *array= malloc(sizeof(PERSON)*n);

    for (int i=0; i<n ; i++)
    {
        printf("Scrivi il nome che vuoi aggiungere: ");
        scanf("%s",array[i].nome);
        printf("Scrivi il cognome che vuoi aggiungere: ");
        scanf("%s",array[i].cognome);
        printf("Scrivi l'eta della persona: ");
        scanf("%d",&array[i].eta);

    }
    printf("\nLe persone aggiunte sono: \n___________________\n");
    printarr_rt(array, n, 0);
    */
    int n2=1;
    PERSON *array2= malloc(sizeof(PERSON)*n2);

    buildarrayfile(array2,n2,"rubrica.txt",&n2);
    printarr_rt(array2,n2,INIZ);

    int etamin;
    etamin=minage(array2,n2-1);
    printf("---------------------\nL'eta minima e: %d\n",etamin);

    int etamax;
    etamax=maxage(array2,n2-1);
    printf("\nL'eta massima e: %d\n---------------------",etamax);

    char nome[20];
    char cognome[20];
    personminage(array2,n2,etamin,nome,cognome);
    printf("\nLA PERSONA PIU PICCOLA E': %s %s\n",nome,cognome);

    personmaxage(array2,n2,etamax,nome,cognome);
    printf("\nLA PERSONA PIU GRANDE E': %s %s\n",nome, cognome);
    printf("---------------------");

    int sum;
    sum=summag(array2,n2-1,INIZ);
    printf("\nSOMMA ETA DEI MAGGIRENNI: %d\n",sum);

    /*
    char *stringa="anna";
    int ciao=palindromo_r(stringa,INIZ);

    printf("\n\n%d\n\n",ciao);
    */
    printf("\nI NOMI PALINDROMI SONO:\n");
    printpersonpalindrome(array2,n2,INIZ);
}


//-------------------------------------
//funzioni

void printarr_rt(PERSON a[], int n, int pos)
{

    if ((pos!=n)&&(a!=NULL))
    {
        printf("%s\n",a[pos].nome);
        printf("%s\n",a[pos].cognome);
        printf("%d\n",a[pos].eta);
        printarr_rt(a,n,pos+1);
    }


}

void buildarrayfile(PERSON array[],int n,char *rubrica,int *m)
{

    FILE *f= fopen(rubrica,"r");
    if (f==NULL)
    {
        printf("Impossibile aprire il file");

    }


    char *r, s[BUFFER];

    int i=0;
    while(true)
    {
         r = fgets(s,BUFFER,f);

         if (r==NULL)
         {
             break;
         }
        sscanf(r,"%s %s %d",array[i].nome,array[i].cognome,&array[i].eta);
        i++;

    }
    array=realloc(array,sizeof(char)*i);
    *m=i;
}

int minage(PERSON array[],int n)
{
    if (n>0)
    {
        if(array[n].eta<minage(array,n-1))
        {
            return array[n].eta;
        }
        else
        {
            return minage(array,n-1);
        }

    }
    else return array[n].eta;
}

int maxage(PERSON array[],int n)
{
   if (n>0)
    {
        if((array[n].eta>maxage(array,n-1)))
        {
            return array[n].eta;
        }
        else
        {
                return maxage(array,n-1);
        }

    }
    else return array[n].eta;
}

void personminage(PERSON array[],int n,int minage,char *nome, char *cognome)
{
    if ((minage>0)&&(n>0))
    {
       if(array[n].eta==minage)
        {
            strcpy(nome,array[n].nome);
            strcpy(cognome,array[n].cognome);
        }
        else{personminage(array,n-1,minage,nome,cognome);}
    }

}
void personmaxage(PERSON array[],int n,int maxage,char *nome, char *cognome)
{
    if ((maxage>0)&&(n>0))
    {
       if(array[n].eta==maxage)
        {
            strcpy(nome,array[n].nome);
            strcpy(cognome,array[n].cognome);
        }
        else{personmaxage(array,n-1,maxage,nome,cognome);}
    }

}

int summag(PERSON array[], int n,int pos)
{
    if (pos<n)
    {
        if (array[pos].eta>18)
        {

            return(summag(array,n,pos+1)+array[pos].eta);

        }
        else
        {
            return(summag(array,n,pos+1));
        }
    }

    return 0;
}
int palindromo(char A[])
{   toUPPER(A);
    int n=strlen(A)-1;
    int i =0;
    int pal = 1;
    while ((i<n) && (pal ==1))
    {

        if (A[i] !=A[n-i])
                pal =0;
        i++;
    }
    return pal;
}

int palindromo_r(char A[], int i)
{
   toUPPER(A);
   int n=strlen(A)-1;

   if(i>(n-i))
   {
       return(1);
   }
   if ((A[i]!=A[n-i]))
   {
       return(0);
   }
   else
   {
       return(palindromo_r(A,i+1));
   }

}
void printpersonpalindrome(PERSON a[], int n, int pos)
{

    if ((pos!=n)&&(a!=NULL))
        {
            if(palindromo_r(a[pos].nome,INIZ)==1)
            {
                printf("%s\n",a[pos].nome);
                printpersonpalindrome(a,n,pos+1);
            }
            else{printpersonpalindrome(a,n,pos+1);}
        }
}

void toUPPER(char *s)  {
int i;
     for (i=0; i<strlen(s); i++)
          // Se il carattere corrispondente della stringa è
          // un carattere maiuscolo, ovvero è compreso tra A e Z...

          if ( (s[i]>='a') && (s[i]<='z') )
s[i]-=32; // spazio che esiste in codice ASCII tra i caratteri maiuscoli e minuscoli
}
//-------------------------------------

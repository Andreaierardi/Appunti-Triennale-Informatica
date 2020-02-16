#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <assert.h>
#include "xerrors.h"
#include "xerrors.c"

// genera array di n elementi con interi random tra 0 e 1999 
int *random_array(int n)
{
  assert(n>0);
  int *a = malloc(n* sizeof(int));
  assert(a!=NULL);
  for(int i=0;i < n;i++)
    a[i] = (int) random() % 2000;
  return a;
}

// funzione di confronto tra interi passata da array_sort a qsort
int intcmp(const void *a, const void *b)
{
  return *((int *) a) - *((int *) b);
}
// esegue il sort dell'array a[0..n] utilizzando la funzione di libreria qsort
void array_sort(int *a, int n)
{
  qsort(a,n,sizeof(int), intcmp);
}
// verifica che array a[0..n] sia ordinato
bool check_sort(int *a, int n)
{
  for(int i=0; i < n-1; i++)
     if(a[i] > a[i+1]) return false;
  return true;
}

//Funzione per il calcolo dei numeri minori di 1000 e dei numeri maggiori di 1000 fino a 2000.
//Ci serve sapere i minori e i maggiori in modo che si sappia quanti sono i numeri da assegnare al processo figlio e quali affidare al processo padre
//Vengono utilizati una variabile puntatore lesser per ritornare i numeri minori al main e nella variabile intera big che verrà ritornata al main con la return
int cerca_lesbig(int *array, int n , int *lesser)
{
	//Inizializzo due vatiabili locali e quella dei maggiori riotrnerò al main
    int less = 0;
    int big=0;
    //big è dei maggiori e less è dei minori
    
    //Scorro l'array generato in modo casuale
    for (int i = 0 ; i<n ; i++)
    {
		
		//Se il numero trovato è minore di 1000 incremento les, altrrimenti incremento big
        if (array[i]<1000)
            less++;
        else
            big++;
    }
    //Assegno al puntatore il numero di minori in modo da poterlo ritornare al main
    *lesser= less;
    //Ritorno semplciemente i numeri maggiori trovati al main
    return big;
}


///MAIN
int main (int argc , char **argv)
{
	//Viene controllato il numero di parametri passati.
    if(argc!=2) 
    {
		printf("Uso\n\t%s lunghezza_array\n", argv[0]);
		exit(1);
	}
	//Assegnamo il valore passato come parametro alla variabile n
	//In questo caso il parametro passato con linea di comando è il numero di elementio dell'array
    int n = atoi(argv[1]);
    //Controllo che n sia maggiore di 0
    assert(n>0 );

///CREAZIONE ARRAY INIZIALE CON NUMERI RANDOM + controllo che l'array venga creato correttamente
//Successivamente questo array una volta assegnato al figlio potrà essere usato per registrare i valori finali ordinati dal padre e dal figlio senza aver bisogno di un nuovo array
//Questo lo si fa per ottimizzazione dato che l'esercizio richiede di allocare minore quantità di memoria possibile
    int *array = random_array(n);
    if(array == NULL){perror("Errore crezione array");exit(1);}
    
///STAMPA DELL'ARRAY
    printf("\n-----ARRAY INIZIALE-----\n");
    for (int i =0 ; i<n ; i++)
        printf("%d\n",array[i]);

//Intero e per i controlli delle write e delle read in pipe
   int e;
   
//Interi utili per avere il numero di interi minori di 1000 e maggiori di 1000 contenuti nell'array da divdere tra processo padre e figlio
   int lesser;
   int bigger = cerca_lesbig(array, n, &lesser);
   
//Stampo i numeri trovati 
   printf("\nMAGGIORI DI 1000 GESTITI DAL FIGLIO: %d\nMINORI DI 1000 GESTITI DAL PADRE: %d\n", bigger,lesser);

//Creo un array tmp in cui andremo ad ordinare gli interi con la funzione array_sort()
//Si utilizza un solo array tmp sia per il padre che per il figlio dato che alla creazione del processo figlio questo avrà le stesse strutture dati del padre.
//Quindi appena copiate le strutture dati il processo figlio andrà avanti con l'esecuzione per "conto suo" quindi qualsiasi modifica verrà fatta al tmp del figlio non 
//verrà fatta su tmp del padre.

   int *tmp= (int *)malloc(sizeof(int )*bigger);
   if(tmp == NULL){perror("Errore crezione array");exit(1);}


   pid_t pid;

  /// CREO PIPE
    int up[2];
    xpipe(up,__LINE__,__FILE__);

  ///CREO PROCESSO FIGLIO
    pid = xfork(__LINE__,__FILE__);
   
//=======INIZIO CODICE DEL FIGLIO
    if (pid==0) 
    {
	
    //La variabile index ci consente di tenere conto della posizione dell'array tmp
    int index = 0;
///CREO ARRAY PER IL FIGLIO IN CUI VADO A METTERE TUTTI I VALORI MAGGIORI DI 1000
      for (int i = 0 ; i<n; i++)
      {
          if(array[i]>=1000)
            tmp[index++]=array[i];

      }
///ORDINO ARRAY DEL FIGLIO
      array_sort(tmp,index);
///COTNROLLO CHE L'ARRAY SIA EFFETIVAMENTE ORDINATO
      if (check_sort(tmp,index)==false)
      {
          perror("Errore ordinamento tmp");
          exit(1);
      }

///STAMPO FIGLIO ORDINATO --- NON NECESSARIO PER L'ESERCIZIO MA AIUTA A CAPIRE SE EFFETTIVAMENTE LE FUNZIONI PRECEDENTI EFFETTIVAMENTE FUNZIONANO
      printf("\n-----FIGLIO----\n");
      for (int j =0 ; j<index ; j++)
        printf("%d\n",tmp[j]);

//Chiusura della pipe in lettura dato che non dobbiamo leggere alcun dato dal figlio
      close(up[0]);

///SCRIVO ARRAY FIGLIO ORDINATO IN PIPE + controllo che effettivamente siano stati scritti un numero "index" di interi su pipe
      e  = write(up[1],tmp,sizeof(int)*index);
      assert(e==sizeof(int)*index);
     //Deallochiamo la memoria
      free(tmp);
      //Chiudiamo pipe in scrittura --- molto importante! Se si lasciasse aperta la pipe in scrittura o lettura si programma si bloccherebbe perchè abbiamo lasciato delle strutture dati in sospeso
      close(up[1]);
      //Con exit(0) c'è la kill del processo figlio quindi chiusura del processo
      exit(0);
    }
//======== FINE CODICE DEL FIGLIO

  // si ritorna al codice del processo padre
  //Chiudo la modalità di scrittura per il padre perchè il padre non deve scrivere in pipe (NB. Abbiamo fatto lo stesso per il figlio ma per la pipe in lettura dato che il figlio non doveva leggere nulla in pipe ma doveva scrivere)
  close(up[1]);

///CREO ARRAY PER IL PADRE
//La variabile indice ci serve per lavorare sull'array tmp del padre
  int indice= 0;
  for (int z = 0; z<n ; z++)
  {
      if(array[z]<1000)
            tmp[indice++]=array[z];

  }
///ORDINO IL PADRE + controllo sulla corretta ordinazione degli elementi
  array_sort(tmp,indice);
  if (check_sort(tmp,indice)==false)
      {
          perror("Errore ordinamento padre");
          exit(1);
      }

///STAMPO PADRE ORDINATO
  printf("\n-----PADRE-----\n");
  for (int ind= 0 ; ind<indice ; ind++)
  {
      printf("%d\n",tmp[ind]);
  }

///METTO NELLE PRIME POSIZIONI DELL'ARRAY IL PADRE ORDINATO
//Così facendo avrò le prime posizioni di array ordinate poichè tmp ha gli elementi già ordinati
  array = tmp;
  
  //Leggo gli interi dell'array tmp scritti in pipe e li assegno ad array
//In poche parole con &array[indice] gli dico di prendere l'indirizzo di array alla posizione indice
//Dalla posizione 0 alla posizione indice, infatti avremo gli elementi del padre che abbiamo inserito con l'istruzione prima
//Quindi gli diciamo di partire dalla posizione array[indice] in poi ad inserire i valori ordinati dal figlio.
///ES. Il padre ha ordinato 3 elementi e tmp sarà lungo quindi 3. La lunghezza di tmp padre è definita dal indice quindi in array andrò a lavorare dalla quarta posizione in poi
    e = read(up[0],&array[indice],sizeof(int)*bigger); 
    if(e==0) {perror("Errore lettura");exit(1);};
    if(e!=sizeof(int)*bigger) {perror("Errore lettura pipe"); exit(1);}
    close(up[0]);
///STAMPA ARRAY FINALE
  printf("---------------FINALE------------\n");
  for (int i =0 ; i<n ; i++)
    {
        printf("%d\n",array[i]);
    }
/// Si può utilizzare fprintf(stderr,"%s\n",check_sort(array,n)? "OK ORDINATO\n" : "Errore\n");
  if(check_sort(array,n))
            printf("\nOK! - FINALE ORDINATO\n");
  else
        {perror("FINALE NON ORDINATO");exit(1);}
        
   free(tmp);
   free(array);

   return 0;
}


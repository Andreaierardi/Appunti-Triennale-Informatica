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
//Successivamente questo array una volta assegnato al figlio potrà essere usato per registrare i valori finali ordinati dai due figli senza aver bisogno di un nuovo array
//Questo lo si fa per ottimizzazione dato che l'esercizio richiede di allocare minore quantità di memoria possibile
    int *array = random_array(n);
    if(array == NULL){perror("Errore crezione array");exit(1);}
    
///STAMPA DELL'ARRAY INIZIALE NON ORDINATO
    printf("\n-----ARRAY INIZIALE-----\n");
    for (int i =0 ; i<n ; i++)
        printf("%d\n",array[i]);

//Intero e per i controlli delle write e delle read in pipe
   int e, e1;

//Questo array viene utilizzato dai due figli per poter gestire ciascuno n/2 numeri.
//Anche in questo caso come nell'esercizio precedente creando un tmp dal padre i figli lo erediteranno con la differenza che quando andranno a gestirlo ognuno avrà la propria copia locale dell'array tmp
//che sarà differente l'una dall'altra
  int *tmp= (int *)malloc(sizeof(int )*(n/2+1));
  if(tmp == NULL){perror("Errore crezione array");exit(1);}

//Creo i due pid per i processi figli
   pid_t pid,pid2;

  /// CREO LE DUE PIPE
    int up[2];
    xpipe(up,__LINE__,__FILE__);
    
     int up2[2];
    xpipe(up2,__LINE__,__FILE__);


//=======INIZIO CODICE DEI FIGLI

///CREO PROCESSO FIGLIO 1

    pid = xfork(__LINE__,__FILE__);
    

    if (pid==0) 
    {
		
//CHIUDO la pipe due per il processo figlio1 dato che lui ne dovrà utilizzare solo una. Questo viene fatto perchè comunque la eredita dal padre
	  close(up2[1]);
      close(up2[0]);

//Chiusura della pipe in lettura dato che non dobbiamo leggere alcun dato dal figlio
      close(up[0]);
      
    //La variabile index ci consente di tenere conto della posizione dell'array tmp
    int index = 0;
///CREO ARRAY PER IL FIGLIO IN CUI VADO A METTERE TUTTI I VALORI NELLE POSIZIONI DA 0 a N/2
      for (int i = 0 ; i<n/2; i++)
            tmp[index++]=array[i];
///ORDINO ARRAY DEL FIGLIO1
      array_sort(tmp,index);
///CONTROLLO CHE L'ARRAY SIA EFFETIVAMENTE ORDINATO
      if (check_sort(tmp,index)==false)
      {
          perror("Errore ordinamento tmp");
          exit(1);
      }

///STAMPO FIGLIO ORDINATO --- NON NECESSARIO PER L'ESERCIZIO MA AIUTA A CAPIRE SE EFFETTIVAMENTE LE FUNZIONI PRECEDENTI EFFETTIVAMENTE FUNZIONANO
      for (int j =0 ; j<index ; j++)
        printf("Figlio1 %d\n",tmp[j]);



///SCRIVO ARRAY FIGLIO ORDINATO IN PIPE + controllo che effettivamente siano stati scritti un numero "index" di interi su pipe
      e  = write(up[1],tmp,sizeof(int)*index);
      assert(e==sizeof(int)*index);
     //Deallochiamo la memoria
      free(tmp);
      //Chiudiamo pipe in scrittura --- molto importante! Se si lasciasse aperta la pipe in scrittura o lettura si programma si bloccherebbe perchè abbiamo lasciato delle strutture dati in sospeso
      close(up[1]);
      printf("CHIUSURA PROCESSO 1 \n");

      //Con exit(0) c'è la kill del processo figlio quindi chiusura del processo
      exit(0);
    }
   
   
///CREO PROCESSO FIGLIO 2

    pid2 = xfork(__LINE__,__FILE__);

	if (pid2==0) 
    {
		
//CHIUDO la pipe uno per il processo figlio2 dato che lui ne dovrà utilizzare solo una. Questo viene fatto perchè comunque la eredita dal padre

	 close(up[1]);
     close(up[0]);
     
//Chiusura della pipe in lettura dato che non dobbiamo leggere alcun dato dal figlio ma dobbiamo solo scrivere in pipe2
      close(up2[0]);
      
    //La variabile index ci consente di tenere conto della posizione dell'array tmp
    int index = 0;
///CREO ARRAY PER IL FIGLIO IN CUI VADO A METTERE TUTTI I VALORI NELLE POSIZIONI DA 0 a N/2
      for (int i = n/2 ; i<n; i++)
            tmp[index++]=array[i];
///ORDINO ARRAY DEL FIGLIO1
      array_sort(tmp,index);
///COTNROLLO CHE L'ARRAY SIA EFFETIVAMENTE ORDINATO
      if (check_sort(tmp,index)==false)
      {
          perror("Errore ordinamento tmp");
          exit(1);
      }

///STAMPO FIGLIO ORDINATO --- NON NECESSARIO PER L'ESERCIZIO MA AIUTA A CAPIRE SE EFFETTIVAMENTE LE FUNZIONI PRECEDENTI EFFETTIVAMENTE FUNZIONANO
      for (int j =0 ; j<index ; j++)
        printf("Figlio2 %d\n",tmp[j]);



///SCRIVO ARRAY FIGLIO ORDINATO IN PIPE + controllo che effettivamente siano stati scritti un numero "index" di interi su pipe2
      e  = write(up2[1],tmp,sizeof(int)*index);
      assert(e==sizeof(int)*index);
     //Deallochiamo la memoria
      free(tmp);
      //Chiudiamo pipe in scrittura --- molto importante! Se si lasciasse aperta la pipe in scrittura o lettura si programma si bloccherebbe perchè abbiamo lasciato delle strutture dati in sospeso
      close(up2[1]);
      //Con exit(0) c'è la kill del processo figlio quindi chiusura del processo
      	printf("CHIUSURA PROCESSO 2\n");

      exit(0);
    }
//======== FINE CODICE DEI FIGLI

  // si ritorna al codice del processo padre
  //Chiudo la modalità di scrittura per il padre perchè il padre non deve scrivere in pipe (NB. Abbiamo fatto lo stesso per il figlio ma per la pipe in lettura dato che il figlio non doveva leggere nulla in pipe ma doveva scrivere)
  close(up[1]);
  close(up2[1]);
  
  
  ///EFFFETTIVAMENTE ASPETTARE I FIGLI NON E' OBBLIGATORIO DATO CHE ANDRANNO A SCRIVERE IN UNA PASSATA TUTTO L'ARRAY GIA' ORDINATO E NON DOVREBBERO ESSERCI RISCHI
  ///DI ANDARE A PESCARE MAGARI UN NUMERO NON ORDINATO. PERÒ PER RENDERE CHIARO IL CODICE E' UTILE
//Intero status per poter eseguire la wait
  int status;
//Ciclio for di due iterazioni poichè effettivamente andremo ad aspettare che 2 figli appunto abbiamo finito il loro lavoro
  for(int i =0 ;i<2;i++)
	xwait(&status,__LINE__,__FILE__);
	
	
  printf("==================HO ASPETTATO CHE I FIGLI AVESSERO TERMINATO===============\n");
		

//Dichiaro delle variabili per poter assegnare i valori letti da pipe(x), pipe(y) e un indice che terrà conto dei valori correttamente inseriti nell'array in modo ordinato
  int x,y, indice = 0 ;
 
//Comincio a leggere fuori dal ciclo while per facilità. Se mettessi queste letture nel while si avrebbero due letture in pipe consecutive dato che nel while andiamo a trattare caso per caso
//Inoltre, non si potrebbe uscire nel momento giusto(per esempio se pipe1 fosse vuota andremmo a leggere comunque il valore che sarà 0 e quindi sicuramente minore di qualsiasi altro letto in pipe2 e il programma non funzionerebbe

//Lettura di un intero dalla pipe e salvo valore in x
  e = read(up[0],&x,sizeof(int)); 
//Questi controlli servono entrambi in questo caso poichè se la pipe è già inzialmente vuota significa che il lavoro di un figlio non è stato svolto nella maniera corretta
  if(e!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
  if(e==0) {perror("Errore lettura "); exit(1);} //Di solito se la pipe è vuota significa che abbiamo terminato la lettura da pipe però se è il caso iniziale significa che in pipe non abbiamo proprio inserito nulla e quindi non va bene
//La stampa è utile per capire come procede l'algoritmo  
  printf("VALORE INIZIALE DI X LETTO:   %d\n",x);
  

  e1 = read(up2[0],&y,sizeof(int));
  if(e1!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
  if(e1==0) {perror("Errore lettura "); exit(1);}
  printf("VALORE INIZIALE DI Y LETTO:   %d\n",y);


///La struttura del while è il cuore di questo programma
///In pratica è un po' come i programmi che si facevano in programmazione2 con le liste
//-if(e1== 0 && e==0 )
// il caso base in cui i valori letti in entrambe le pipe sono a 0 quindi ho terminato la lettura da entrambe le pipe e quindi ho finito di scrivere nell'array

//-else if(e==0)
//Il caso in cui la prima pipe abbia finito allora dobbiamo continuare ad inserire i restanti valori dalla pipe2 (come quando lis1 era minore di lis2 allora inserivamo tutti gli elementi di lis2 rimanenti)

//-else if(e1==0)
//Il caso in cui la seconda pipe abbia finito allora dobbiamo continuare ad inserire i restanti valori dalla pipe1(caso contrario quando lis1 era piu' grande di lis2

//- else
//E' il caso in cui entrambe hanno valori da leggere nelle pipe e quindi c'è bisogno di vedere quali dei due è minore

 while(true)
{
	
//Caso base in cui entrambe le pipe sono vuote e bisogna uscire dal while
//Si potrebbe inserire il controllo direttamente al posto di (true) nel while ma andrebbe avanti nel ciclo e nella lettura fino alla fine dell'ultimo ciclo e non darebbe fuori output corretti   
   if(e1== 0 && e==0 )
		break;
		
//Caso in cui la prima pipe sia vuota
   else if(e==0)
   {
	   //Inserisco il valore letto prima del ciclo while oppure all'ultima iterazione svolta
	    array[indice++] = y;
		printf("PIPE1 VUOTA INSERISCO y: %d \n",y);

		//Aggiorno il valore di y leggendo in pipe2
		e1 = read(up2[0],&y,sizeof(int));
		//Nel caso io abbia finito di leggere valori dalla pipe(quindi la pipe è vuota allora e1 sarà uguale a 0 e dovrò terminare questo if)
		if(e1==0)
			break;
			
		//Verifico che effettivamente venga letto un numero intero dalla pipe
		if(e1!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
   }

//Caso in cui pipe2 sia vuota
   else if(e1==0)
   {
	   //Inserisco il valore letto prima del ciclo while oppure all'ultima iterazione svolta
	   array[indice++] = x;
	   printf("PIPE2 VUOTA INSERISCO x: %d \n",x); //La printf è utile per capire quando vengono inseriti i valori nell'array e quali sono

		//Aggiorno il valore di x leggendo in pipe 
	   e = read(up[0],&x,sizeof(int));
	   
	   //Nel caso io abbia finito di leggere valori dalla pipe(quindi la pipe è vuota allora e1 sarà uguale a 0 e dovrò terminare questo if)
	   if(e==0)
			break;
	//Verifico che effettivamente venga letto un numero intero dalla pipe
	   if(e!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
   }
   
//Caso in cui entrambe le pipe siano piene e quindi ci siano valori da leggere e confrontare
   else
    {
		//In questo caso, fino a quando i valori di letti di x sono minori di y allora continuo ad inserire x nell'array e poi aggiorno il valore di x leggendo in pipe il prossimo valore
		while(x<y)
		{
			
			array[indice++] = x;
			printf("Ho trovato un valore di pipe minore di pipe2-- ");
			printf("x: %d \nquindi %d < %d \n\n",x,x,y);
			
			e = read(up[0],&x,sizeof(int));
			if(e==0)
				break;
			if(e!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
		}
		
		//Qui è il caso contrario in cui finchè il valore di y è minore di x allora inserisco il valore y e aggiorno il suo valore leggendo da pipe2
		while(y<=x )
		{
			array[indice++] = y;
			printf("Ho trovato un valore di pipe2 minore di pipe-- ");
			printf("y: %d \nquindi %d < %d \n\n",y,y,x);

			e1 = read(up2[0],&y,sizeof(int));
			if(e1==0)
				break;
			if(e1!=sizeof(int)) {perror("Errore lettura pipe"); exit(1);}
		}
    }
    	
   

}

//Chiusura delle pipe in lettura da parte del padre visto che abbiamo terminato
    close(up[0]);
    close(up2[0]);
	
//Stampa per verificare che effettivamente abbiano letto dalla pipe e inserito nell'array effettivamente n elementi
	printf("N: %d\nINDICE: %d\n",n,indice);
	
///STAMPA ARRAY FINALE
printf("---------------FINALE ORDINATO------------\n");

    for (int i =0 ; i<n ; i++)
        printf("ARRAY: %d\n",array[i]);
/// Si può utilizzare fprintf(stderr,"%s\n",check_sort(array,n)? "OK ORDINATO\n" : "Errore\n");
  if(check_sort(array,n))
            printf("\nOK! - FINALE ORDINATO\n");
  else
        {perror("FINALE NON ORDINATO");exit(1);}

//Dealloco la memoria dei due array allocati
   free(tmp);
   free(array);

   return 0;
}


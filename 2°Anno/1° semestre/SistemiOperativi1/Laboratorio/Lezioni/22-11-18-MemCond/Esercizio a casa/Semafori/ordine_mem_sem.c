#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>  // gestisce tipo bool (per variabili booleane)
#include <assert.h>   // permette di usare la funzione assert
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>   
#include "xerrors.h"
#include "xerrors.c"


#define Nome "/ordinearray_array"
#define Nome1 "/ordinetmp_array"
#define Nome2 "/ordina_sem"
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

  /// MEMORIA CONDIVISA
      // ---- creazione array memoria condivisa
  int shm_size = n*sizeof(int); // numero di byte necessari
  int fd = xshm_open(Nome,O_RDWR | O_CREAT, 0600 , __LINE__,__FILE__);
  xftruncate(fd, shm_size, __LINE__,__FILE__);
  int *array = simple_mmap(shm_size,fd, __LINE__,__FILE__);
  close(fd); // dopo mmap e' possibile chiudere il file descriptor
  array=  random_array(n);
  if(array == NULL){die("Errore crezione array");}
     
  // ---- creazione array temporaneo in memoria condivisa che ci servirà per gestire i numeri delle posizioni interessate senza dover toccare l'array originale
  int shm_size1 = n*sizeof(int); // numero di byte necessari
  int fd1 = xshm_open(Nome1,O_RDWR | O_CREAT, 0600,__LINE__,__FILE__);
  xftruncate(fd1, shm_size1, __LINE__,__FILE__);
  int *tmp = simple_mmap(shm_size1,fd1, __LINE__,__FILE__);
  close(fd1); // dopo mmap e' possibile chiudere il file descriptor
  
   // ---- memoria condivisa per i semafori
  int shm_size2 = 2*sizeof(sem_t); // numero di byte necessari
  int fd2 = xshm_open(Nome2,O_RDWR | O_CREAT, 0600,__LINE__,__FILE__);
  xftruncate(fd2, shm_size2, __LINE__,__FILE__);
  sem_t *sem = simple_mmap(shm_size2,fd2, __LINE__,__FILE__);
  close(fd1); // dopo mmap e' possibile chiudere il file descriptor
  sem_t *semconta = &sem[0];  // oppure  = sem 
  sem_t *semfinito = &sem[1]; // oppure = sem+1
  xsem_init(semconta,1,1,__LINE__, __FILE__);
  xsem_init(semfinito,1,0,__LINE__, __FILE__);


///STAMPA DELL'ARRAY
    printf("\n-----ARRAY INIZIALE-----\n");
    for (int i =0 ; i<n ; i++)
        printf("%d\n",array[i]);

//less e big quindi saranno i valori delle posizioni in cui andranno a lavorare il padre e il figlio
//Infatti less indica i valori minori di 1000 e big i numeri maggiori di 1000 fino a 2000
   int less;
   int big = cerca_lesbig(array,n,&less);

   printf("\nMINORI DI 1000 GESTITI DAL PADRE: %d\nMAGGIORI DI 1000 GESTITI DAL FIGLIO: %d\n", less,big);


   pid_t pid;
  ///CREO PROCESSO FIGLIO
  printf("\nPARTE IL CODICE DEL FIGLIO\n");
    pid = xfork(__LINE__,__FILE__);

//=======INIZIO CODICE DEL FIGLIO
    if (pid==0)
    {

    //La variabile index ci consente di tenere conto della posizione dell'array tmp che per il figlio dovrà essere 6 poichè il padre deve lavorare dalle posizioni 0 a 5 di tmp dato che i numeri minori di 1000 sono 6
    int index = less;
    printf("IL FIGLIO PARTE AD ORDINARE DALL'INDICE %d\n",index);
    
    //Assegnamo delle variabili diverse per non far confusione ma non dovrebbe essere necesssario
	int min=less;
    int mag = big;
    

///CREO ARRAY PER IL FIGLIO IN CUI VADO A METTERE TUTTI I VALORI MAGGIORI DI 1000
    for (int i = 0 ; i<n; i++)
      {
          if(array[i]>=1000)
            tmp[index++]=array[i]; //Ogni volta che trova un valore >=1000 index viene incrementato

      }
      
      
      //Semaforo posizionato qui per accedere alla mutua esclusione per l'ordinamento dell'array
      xsem_wait(semconta,__LINE__, __FILE__);

///ORDINO ARRAY DEL FIGLIO
//Il sorting parte dall'indirizzo tmp[min] dato che parte dalla posizione 6 essendo i valori minori di 1000. Dalla posizione 6 fino a n-1 ordinerà mag numeri quindi ordinerà tutte le posizioni dei numeri >=1000
//In questo esempio andrà ad ordine appunto dalla posizione 6 alla posizione 9 dato che i numeri >=1000 sono 4
      array_sort(&tmp[min],mag);
///COTNROLLO CHE L'ARRAY SIA EFFETIVAMENTE ORDINATO
      if (check_sort(&tmp[min],mag)==false)
          die("Errore ordinamento tmp");
      //Rilascio mutua esclusione dell'ordinamento di tmp
      xsem_post(semconta,__LINE__, __FILE__);

///STAMPO FIGLIO ORDINATO --- NON NECESSARIO PER L'ESERCIZIO MA AIUTA A CAPIRE SE EFFETTIVAMENTE LE FUNZIONI PRECEDENTI EFFETTIVAMENTE FUNZIONANO
      printf("\n-----FIGLIO----HA ORDINATO DALLA POSIZIONE %d AD %d DI TMP\n", min,n-1);
      for (int j =min ; j<n ; j++)
		printf("FIGLIO %d\n",tmp[j]);
		
	 // segnalo al padre che ho terminato 
      xsem_post(semfinito,__LINE__, __FILE__);
      // unmap memoria condivisa
      xmunmap(sem,shm_size2,__LINE__, __FILE__);
    //xmunmap(array,shm_size,__LINE__, __FILE__);
    xmunmap(tmp,shm_size1,__LINE__, __FILE__);
	printf("CHIUSURA FIGLIO\n");
    
    //Con exit(0) c'è la kill del processo figlio quindi chiusura del processo
      exit(0);
    }
//======== FINE CODICE DEL FIGLIO


///CREO ARRAY PER IL PADRE
//La variabile indice ci serve per lavorare sull'array tmp del padre
  int indice= 0;
  for (int z = 0; z<n ; z++)
  {
      if(array[z]<1000)
            tmp[indice++]=array[z];

  }
  
  printf("IL PADRE ORDINA DA tmp[0] a tmp[%d]\n",indice-1);
///ORDINO IL PADRE + controllo sulla corretta ordinazione degli elementi
  array_sort(tmp,indice);
  if (check_sort(tmp,indice)==false)
      die("Errore ordinamento padre");
      


///STAMPO PADRE ORDINATO
  printf("\n-----PADRE-----ORDINA DA POSIZIONE %d A %d DI TMP\n",0,indice-1);
  for (int i= 0 ; i<indice ; i++)
	printf("%d\n",tmp[i]);




//In questo caso aspetto che il figlio termini.
//Aspetta che il figlio ordini la sua parte in modo che non entri in conflitto con lui 
   xsem_wait(semfinito, __LINE__, __FILE__);

  
  //pongo array uguale a tmp perchè appunto l'esecuzio richiede che l'array inziale sia ordinato usando un secondo array di appoggio
  array = tmp;
 
///STAMPA ARRAY FINALE
  printf("---------------FINALE------------\n");
  for (int i =0 ; i<n ; i++)
    {
        printf("FINALE: %d\n",array[i]);
    }
/// Si può utilizzare fprintf(stderr,"%s\n",check_sort(array,n)? "OK ORDINATO\n" : "Errore\n");
  if(check_sort(array,n))
            printf("\nOK! - FINALE ORDINATO\n");
  else
        die("FINALE NON ORDINATO");

//Dealloco memoria condivisa
  xmunmap(array,shm_size,__LINE__, __FILE__);
  xmunmap(tmp,shm_size1,__LINE__, __FILE__);
  xmunmap(sem,shm_size2,__LINE__, __FILE__);
  xshm_unlink(Nome2,__LINE__, __FILE__);
  xshm_unlink(Nome,__LINE__, __FILE__);
  xshm_unlink(Nome1,__LINE__, __FILE__);
      return 0;
}


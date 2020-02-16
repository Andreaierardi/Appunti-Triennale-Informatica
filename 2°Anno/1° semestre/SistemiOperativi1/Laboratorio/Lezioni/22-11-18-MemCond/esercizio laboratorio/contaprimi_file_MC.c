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


#define Nome "/array"
#define Nome1 "/num"
#define Nome2 "/sem"


// restituisce true/false a seconda che n sia primo o composto
bool primo(int n)
{
  int i;
  if(n<2) return false;
  if(n%2==0) {
    if(n==2)
      return true;
    else
      return false;
  }
  for (i=3; i*i<=n; i += 2) {
      if(n%i==0) {
          return false;
      }
  }
  return true;
}



///MAIN
int main (int argc , char **argv)
{
	//Viene controllato il numero di parametri passati.
    if(argc!=3)
    {
		printf("Uso\n\t%s lunghezza_array\n", argv[0]);
		exit(1);
	}
	//Assegnamo il valore passato come parametro alla variabile n
	//In questo caso il parametro passato con linea di comando è il numero di elementio dell'array
    int n = atoi(argv[1]);
    int tot= 0;
    //Controllo che n sia maggiore di 0
    assert(n>0 );

  /// MEMORIA CONDIVISA
      // ---- creazione array memoria condivisa
  int shm_size = 10*sizeof(int); // numero di byte necessari
  int fd = xshm_open(Nome,O_RDWR | O_CREAT, 0600 , __LINE__,__FILE__);
  xftruncate(fd, shm_size, __LINE__,__FILE__);
  int *array = simple_mmap(shm_size,fd, __LINE__,__FILE__);
  close(fd); // dopo mmap e' possibile chiudere il file descriptor
 
  if(array == NULL){die("Errore crezione array");}
     
  // ---- creazione array temporaneo in memoria condivisa che ci servirà per gestire i numeri delle posizioni interessate senza dover toccare l'array originale
  int shm_size1 = 2*sizeof(int); // numero di byte necessari
  int fd1 = xshm_open(Nome1,O_RDWR | O_CREAT, 0600,__LINE__,__FILE__);
  xftruncate(fd1, shm_size1, __LINE__,__FILE__);
  int *num = simple_mmap(shm_size1,fd1, __LINE__,__FILE__);
    close(fd1); // dopo mmap e' possibile chiudere il file descriptor

  num[0] = 0;
  num[1]= 0;
  
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


  FILE *f= xfopen(argv[2], "r",__LINE__,__FILE__); 
  int val;
  pid_t pid;
  ///CREO PROCESSO FIGLIO
  printf("\nPARTE IL CODICE DEL FIGLIO\n");

//=======INIZIO CODICE DEL FIGLIO
   for(int i = 0; i<n;i++)
   {
	 pid = xfork(__LINE__,__FILE__);
	int x = 0;
	if (pid==0)
	{
		do
		{
			xsem_wait(semconta,__LINE__, __FILE__);
			printf("PROCESSO %d IN ZONA CRITICA\n",i);
			while(num[0]== 0)
				{
					printf("DORMO...\n");
					sleep(1);
				    printf("PROCESSO %d FUORI ZONA CRITICA DOPO SLEEP\n",i);

					xsem_post(semconta,__LINE__,__FILE__);
				}
				
				
			if(num[0]>0)
			{
				x = array[num[0]-1];
				num[0] -=1;
				   printf("--PRELEVO %d IN POSIZIONE %d DEL BUFFER\n[%d] FUORI ZONA CRITICA LAVORO OK\n",x,num[0],i);

				 xsem_post(semconta,__LINE__,__FILE__);
				/*if(x<0)
					{	xsem_post(semconta,__LINE__,__FILE__);
			 // unmap memoria condivisa
			xmunmap(sem,shm_size2,__LINE__, __FILE__);
			xmunmap(array,shm_size,__LINE__, __FILE__);
			xmunmap(num,shm_size1,__LINE__, __FILE__);
						exit(1);
					}*/
				if(primo(x))
					{
						printf("\n___TROVATO PRIMO : %d dal processo [%d]\n\n",x,i);
						num[1]+=1;
					}
			}
		 

		}while(x>=0);
	 // unmap memoria condivisa
    xmunmap(sem,shm_size2,__LINE__, __FILE__);
    xmunmap(array,shm_size,__LINE__, __FILE__);
    xmunmap(num,shm_size1,__LINE__, __FILE__);
	printf("===CHIUSURA FIGLIO -%d-\n",i);
    
    //Con exit(0) c'è la kill del processo figlio quindi chiusura del processo
     exit(1);

	}
}
//======== FINE CODICE DEL FIGLIO

   while(!feof(f))
	{	 
		int x =  fscanf(f,"%d",&val);
		if(x==0) 
		break;
		tot++;
		printf("		PADRE -LEGGO %d\n",val);
		xsem_wait(semconta,__LINE__, __FILE__);
		printf("		PADRE ACCEDO AL BUFFER\n");
		while(num[0] == 10)
			{	printf("PADRE: DORMO...\n");
				sleep(1);
				xsem_post(semconta,__LINE__,__FILE__);
			}
		if(num[0] <10)
			{
				array[num[0]] = val;
				printf("		PADRE - INSERISCO %d nel buffer in posizione %d\n",val,num[0]);

				num[0] += 1;
					xsem_post(semconta,__LINE__,__FILE__);
			}
	

	}
	printf("		PADRE - FINITO FILE\n");
	if(feof(f))
	   for(int i = 0; i<n;i++)
		{
			xsem_wait(semconta,__LINE__, __FILE__);
			array[num[0]++] = -1;
			xsem_post(semconta,__LINE__,__FILE__);

		}
   
 
	int status;
	for(int i = 0; i<n;i++)
		xwait(&status,__LINE__,__FILE__);
			 
	printf("\n\n========================\nNUMERI TOTALI NEL FILE: %d\nNUMERI PRIMI NEL FILE: %d\n",tot-1,num[1]);
	//Dealloco memoria condivisa
	  xmunmap(array,shm_size,__LINE__, __FILE__);
	  xmunmap(num,shm_size1,__LINE__, __FILE__);
	  xmunmap(sem,shm_size2,__LINE__, __FILE__);
	  xshm_unlink(Nome2,__LINE__, __FILE__);
	  xshm_unlink(Nome,__LINE__, __FILE__);
	  xshm_unlink(Nome1,__LINE__, __FILE__);
		  return 0;
}

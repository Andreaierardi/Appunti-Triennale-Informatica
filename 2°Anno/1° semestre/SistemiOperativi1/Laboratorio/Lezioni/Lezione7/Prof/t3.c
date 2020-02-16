#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

// struttura usata per comunicare con i thread
typedef struct {
  char *s;   // stringa (puntatore) passata in input
  int len;   // lunghezza passata in output
} dati; 



// esempio in cui si passa un valore attraverso la exit 
void *tbody(void *arg)
{
  dati *d = (dati *) arg;   
  printf("%s passata al pid: %d\n",d->s,getpid());// il pid e' lo stesso per tutti i thread
  sleep(2);
  d->len = strlen(d->s); // calcola il risultato e lo memorizza dove il thread principale lo puo' trovare
  pthread_exit(NULL);    // non restituisce nulla attraverso la exit
}


int main(int argc, char *argv[])
{
  int i,n,e;

  if (argc==1) { 
    fprintf(stderr,"Passare almeno un argomento\n"); exit(1);
  }

  n = argc-1;
  pthread_t t[n];    // usata internamente per gestire i thread
  dati d[n];         // usato per passare input e output
  for(i=0;i<n;i++) {
    d[i].s = argv[i+1];
    e = pthread_create(&t[i], NULL, tbody, (void *) &d[i]);
    if(e!=0) {
      fprintf(stderr,"Errore pthread_create (%d)\n",e);
      exit(1);
    }
  }

  // attende terminazione dei thread 
  for(i=0;i<n;i++) {
    e = pthread_join(t[i], NULL);  //\\ il valore passato dalla exit viene ignorato
    if(e!=0) {
      fprintf(stderr,"Errore pthread_join (%d)\n",e); 
      exit(1);
    }
    printf("Thread %d ha restituito %d\n",i,d[i].len);
  }
}

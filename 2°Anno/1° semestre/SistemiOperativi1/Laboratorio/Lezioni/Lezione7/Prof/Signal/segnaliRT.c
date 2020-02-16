#include "xerrors.h"


/* Osservazioni
 * 
 * In questo esempio si cera di effettuare la sincronizzazione tra padre e figli 
 * utilizzando i segnali invece della wait()
 * 
 * I processi figli mandano un segnale USR1 al padre per indicare che hanno 
 * terminato: il signal handler incrementa la varabile globale tot_segnali 
 * per ogni segnale ricevuto quindi in teoria il padre deve semplicemente 
 * aspettare che la variabile tot_segnali riceva raggiunga il valore pari
 * al numero dei processi figli. Purtroppo questo schema non funziona.
 * 
 * Di default nuove istanze di un segnale sono bloccate (diventano pending) 
 * quando e' in esecuzione l'handler per quel segnale. Se pero' due o piu' istanze dello 
 * stesso segnale sono pending, allora le istanze vengono unificate e il segnale 
 * viene inviato una volta sola: abbiamo allora che la variabile tot_segnali sara'
 * incrementata un numero minore di volte rispetto al numero dei processi.
 * Si noti che il problema e' piu' accentuato quando l'handler impega molto tempo
 * (infatti si suggerisce sempre di fare handler semplici), ma anche un handler 
 * che consiste in una sola istruzione puo' avere questo problema.  
 * 
 * Se tra i flag del segnale aggiungiamo SA_NODEFER allora nuove istanze del
 * segnale non sono piu' bloccate ma in questo caso puo' determinarsi una race
 * condition nell'operazione num_segnali++ (che anche se molto semplice non e' 
 * atomica).
 * 
 * La soluzione e' non usare SA_NODEFER e utilizzare al posto di SIGUSR1 il
 * real-time signal SIGRTMIN. I segnali real time hanno, tra le altre, 
 * la caratteristica che quando vengono bloccati e diventano pending diverse
 * istanze dello stesso segnale non sono mai unificate, quindi se vengono 
 * lanciate n istanze del segnale l'handler sara' eseguito n volte (che
 * e' quello che serve a noi)
 * 
 * Come aspettare i segnali 
 *  
 * Il semplice ciclo while(tot_segnali<n) ; e' un busy-waiting cioe'
 * il processo mentre attende consuma molta CPU. Inoltre, se eliminate 
 * la keyword *volatile* dalla definizione di tot_segnali il programma non
 * esce dal ciclo in quanto il compilatore "ottimizza" il ciclo e lo sostiuisce
 * direttamente con un ciclo infinito. La keyword volatile dice al compilatore:
 * guarda che "the value of the variable may change at any time--without 
 * any action being taken by the code the compiler finds nearby" quindi 
 * il compilatore non deve ottimizzare un loop basato su questa variabile.  
 * 
 * Se utilizziamo la pause() c'e' il rischio che l'ultimo segnale arrivi nel 
 * tempo tra il controllo tot_segnali<n e la pause(); in questo caso la pause
 * si metterebbe in atesa di un segnale che non arrivera' mai. Per questo motivo
 * e' opportuno non entrare in un'attesa infinta ma sospendere l'esecuzione
 * per piccolo un intervallo di tempo con la funzione sleep(). L'argomento
 * di sleep e' un intero che indica il numero minimo di secondi da aspettare
 * quindi la sleep si mette in attesa per almeno un secondo; per attendere intervalli
 * più brevi usare usleep(3) o nanosleep(2). Dalla pagina man di sleep si vede che
 * l'attesa di una chiamata a sleep termina se arriva un segnale che non e'
 * ignorato.   
 * 
 * 
 *  
 * */
#define SEGNALE SIGRTMIN
//Prototipi
bool primo(int n);


volatile int tot_segnali=0; // non inizializzarlo altrove!
// funzione che viene invocata quando viene ricevuto un segnale USR1
void handler(int s)
{
  tot_segnali++;
  printf("Segnale %d ricevuto dal processo %d (tot=%d)\n", s, getpid(),tot_segnali);
}


int main(int argc,char *argv[])
{
  if(argc!=3) {
    fprintf(stderr,"Uso\n\t%s m num_proc\n", argv[0]);
    exit(1);
  }
  // conversione input
  int m= atoi(argv[1]);
  assert(m>0);
  int n= atoi(argv[2]);
  assert(n>0);

  // definisce signal handler 
  struct sigaction sa;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);     // setta a "insieme vuoto" sa.sa_mask maschera di segnali da bloccare 
  sa.sa_flags = SA_RESTART;     // restart system calls  if interrupted
  //  sa.sa_flags |= SA_NODEFER;    // questa non aiuta (vedi Osservazioni)
  sigaction(SEGNALE,&sa,NULL);  // handler per USR1

  // creazione array memoria condivisa
  int shmid= xshmget(IPC_PRIVATE, n*sizeof(int), 0600,__LINE__,__FILE__);
  int *a= xshmat(shmid, NULL, 0,__LINE__,__FILE__);
  assert(a!=NULL);

  // creazione processi figlio
  for(int i=0; i<n; i++) {
    pid_t pid= xfork(__LINE__, __FILE__);
    if(pid==0) { //processo figlio
      int conta=0;
      for(int j=1+2*i; j< m; j+=2*n)
         if(primo(j)) conta++;
      // scrivo il valore di conta nella memoria condivisa
      a[i]= conta;
      // detach memoria condivisa
      xshmdt(a, __LINE__, __FILE__);
      fprintf(stderr,"Processo %d terminato\n",i);
      int e = kill(getppid(),SEGNALE); // manda segnale USR1 al padre
      assert(e==0);
      exit(0);
    }
  }
  // codice processo padre
  // aspetta che abbiano finito i figli: 
  
  // il modo corretto e' con la wait
  //    for(int i=0; i<n; i++)  xwait(NULL, __LINE__, __FILE__);
  // ma noi vogliamo sperimentare l'uso dei segnali

  // metodo alternativo basato sui segnali
  int volte = 0;  // conto quante volte eseguo il body del loop
  while(tot_segnali<n) {
    volte++;  
    sleep(1);
  }
  fprintf(stderr,"Ho eseguito il ciclo %d volte\n",volte);
    
    
  // calcola e restituisce il risultato 
  int conta = 0;
  for(int i=0; i<n; i++) conta += a[i];
  printf("Numero primi dispari tra 1 e %d (escluso): %d\n",m,conta);
  
  // detach e rimozione memoria condivisa
  xshmdt(a, __LINE__, __FILE__);
  xshmctl(shmid, IPC_RMID, NULL, __LINE__, __FILE__);
  return 0;
} 


bool primo(int n)
{
    int i;
    if(n<2) 
        return false;
    if(n%2==0) 
    {
        if(n==2)
            return true;
        else
            return false;
    }
    for(i=3; i*i<=n; i+= 2) 
    {
        if(n%i==0) 
        {
            return false;
        }
    }
    return true;
}

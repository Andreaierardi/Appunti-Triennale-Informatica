#define _GNU_SOURCE
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>

typedef struct {
  int bytesLeft;             // bytes attualmente disponibili
  pthread_cond_t cond;    // condition variable
  pthread_mutex_t mutex;  // mutex associato alla condition variable
} heap;

typedef struct
{
    int mem;
    int sec;
    heap *h;
} dati;

heap *h;
int heap_init(heap *h, int maxSize);
int allocate_memory(heap *h, int size);
int free_mem(heap *h, int size);

void *tbody(void *arg)
{
    dati *a = (dati *)arg;
    printf("mem: %d, sec: %d\n",a->mem, a->sec);

    allocate_memory(a->h,a->mem);
    sleep(a->sec);
    free_mem(a->h, a->mem);
    pthread_exit(NULL);
}
volatile int tot_segnali = 0;
volatile bool continua = true; // il perche' della keyword volatile lo vediamo a lezione

// funzione che viene invocata quando viene ricevuto un segnale USR1 USR2 o INT (Control-C)
void handler(int s)
{
  tot_segnali++;
  if (s==SIGUSR1)
  {
      pthread_t t;
      dati a;
      int sec, mem;
      printf("Quanta mem e sec ?");
      int e= scanf("%d %d",&mem,&sec);
      if (e!=2) {perror("Errore in scanf");exit(1);}
      a.sec = sec;
      a.mem = mem;
      a.h = h;
      e = pthread_create(&t, NULL, tbody, (void *) &a);
      assert(e==0);
  }

  if (s==SIGUSR2)
  {
      printf("mem heap : %d\n",h->bytesLeft);

  }
}

int main()
{
    h = malloc(sizeof(heap));
    int e = heap_init(h,10);
    if (e!= 0) printf("Errore creazione heap\n");
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);     // setta a "insieme vuoto" sa.sa_mask maschera di segnali da bloccare
    sa.sa_flags = SA_RESTART;     // restart system calls  if interrupted
    sigaction(SIGUSR1,&sa,NULL);  // handler per USR1
    sigaction(SIGUSR2,&sa,NULL);  // handler per USR2*/
    printf("Il PID del padre è : %d\n",getpid());

    while (true)
    {
        sleep(1);
    }

}

int heap_init(heap *h, int maxSize)
{

    if (h == NULL) return 2;
    h->bytesLeft = maxSize;

    int e = pthread_cond_init(&h->cond, NULL);
    if (e!= 0 ) return -2;

    e  = pthread_mutex_init(&h->mutex , NULL);
    if (e!= 0) return -3;
    return 0;
}

int allocate_memory(heap *h, int size)
{
  pthread_mutex_lock(&h->mutex);
  while (h->bytesLeft < size)
    {// aspetto che qualcuno attraverso c indichi che ci sono novita' su byteLeft
        int e = pthread_cond_wait(&h->cond, &h->mutex);
        if (e!= 0 ) return -1;
    }
  h->bytesLeft -= size;
  //h = realloc (h, sizeof(heap)*size);
  int e = pthread_mutex_unlock(&h->mutex);
  if (e!= 0 ) return -2;
  return 0;
}

int free_mem(heap *h, int size)
{
    int e = pthread_mutex_lock(&h->mutex);
    if (e!= 0 ) return -1;
    h->bytesLeft += size;            // modifico byteLeft sotto mutex
    // tutti quelli che stanno aspettando su c sono avvertiti ...
    e = pthread_cond_broadcast(&h->cond);   // ... ma non partono subito perche' c'e' il mutex
    if (e!= 0) return -2;
    e= pthread_mutex_unlock(&h->mutex);
    if (e!= 0 )return -3;
    return 0;
}

// ===== Esempio 2 ==================

/*
// Condition variable usata per realizzare un reader/writer lock

// !!!! Orribili variabili globali

// numero di reader e scrittura in corso
int readers=0;
bool writing=false;

// condition variable e mutex associato
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;;

// in questo esempio m e c si riferiscono alle due variabili
// readers e writing. Chi le cambia deve eseguire il lock su m e se
// sono state liberate delle risorse deve mandare il segnale attarverso c
// I thread che devono eseguire un lock ma non possono farlo devono mettersi in wait su c
void read_lock()
{
  pthread_mutex_lock(&m);
  while(writing)
    pthread_cond_wait(&c, &m);   // attende fine scrittura
  readers++;
  pthread_mutex_unlock(&m);
}

void read_unlock()
{
  pthread_mutex_lock(&m);
  readers--;                  // cambio di stato
  if(readers==0) pthread_cond_signal(&c); // da segnalare ad un solo writer
  pthread_mutex_unlock(&m);
}

void write_lock()
{
  pthread_mutex_lock(&m);
  while(writing || readers>0)
    pthread_cond_wait(&c, &m);   // attende fine scrittura o lettura
  writing = true;
  pthread_mutex_unlock(&m);
}

void write_unlock()
{
  pthread_mutex_lock(&m);
  writing=false;               // cambio stato
  pthread_cond_broadcast(&c);  // da segnalare a tutti quelli in attesa
  pthread_mutex_unlock(&m);
}



// ======= Esempio 3

// Realizzazione di un semaforo usando mutex+condition variable

// il semaforo blocca solo sullo 0
// la condition var e' solo un segnale quindi il modo di bloccare
// dipende dal test prima del cond_ wait quindi puo' essere piu' generale

// un semaforo si puo' realizzare con mutex + condition var
// come mostrato qui sotto


// realizzazione di un semaforo mediante Mutex + CV

typedef struct {
  int tot;  // valore del semaforo, non deve mai diventare negativo
  pthread_cond_t cond;   // condition variable
  pthread_mutex_t mutex; // mutex associatcondition variable
} zem;

// inzializza semaforo al valore q
void zem_init(zem *z, int q)
{
  z->tot = q;
  pthread_cond_init(&z->cond,NULL);
  pthread_mutex_init(&z->mutex,NULL);
}

// analoga alla sem_wait
void zem_down(zem *z, int q)
{
  pthread_mutex_lock(&z->mutex);
  while(z->tot-q<0)
    pthread_cond_wait(&z->cond,&z->mutex);
  z->tot -= q;
  pthread_mutex_unlock(&z->mutex);
}


// analoga alla sem_post
void zem_up(zem *z, int q)
{
  pthread_mutex_lock(&z->mutex);
  z->tot+=q;
  pthread_cond_broadcast(&z->cond);
  pthread_mutex_unlock(&z->mutex);
}

*/

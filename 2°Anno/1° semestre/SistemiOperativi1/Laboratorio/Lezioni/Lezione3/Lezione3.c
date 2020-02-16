/*
conta quanti sono i primi compresi tra argv1 e argv2
Si usa la funzione primo in file separato. Il main non fa altro che prendere due stringhe
dalla linea di comando e conta quanti sono i numeri primi tra n0 e n1.
_____________________________________________________________________________

Secondo programma. Due parametri: numero dei primi e il secondo utilizzando il numero di processi separati
Dobbiamo dividere il lavoro per ogni processo utilizzando un intervallo di numeri.
Se metto 1000 5 --> ogni processo elabora 200 numeri primi (1000 / 5 processi)
Questi processi verranno eseguiti in parallelo. Per un problema così piccolo creare più processi in realtà non aiuta.
Ogni singolo processo do un certo intervallo e ogni processo richiama la funzione cerca.
Main legge tre argomenti. Assegno a n atoi(argv[1]) e atoi argv[2].
Devo creare 4 processi figli e ad ogni processo devo assegnare un certo intervallo.
Devo cercarmi gli intervalli di numeri.
a = 1 + (n/p) * i
b = (i+1==p) ? n : (n/p)*(i+1); --> se siamo ultima interazione b = n

fork()-> crea processo. Fork ha un comportamento strano. Il valore restituito dalla fork è il pid(process ID).
Se restituisce un valore diverso da 0 allora c'è stato un errore.
Se avvenuto con successo computazione viene divisa tra processo padre e processo figlio.
Processo padre ottiene il numero del processo figlio(diverso da 0 ), mentre il processo figlio ottiene il valore 0
Se valore restituito da fork() (pid= fork()) quindi pid < 0 allora vi è un errore nella creazione del processo.
Codice sotto if(pid=fork()==0) viene eseguito dai processi figli.
Ad ogni interazione del ciclo for viene creato un nuovo processo fino a 'p' processi figli.
Il loro codice poi parte (quello dell'IF).
Ai processi figli viene passata l'immagine corrente del programma.
I valori a e b non ho bisogno di passarli. Quando parte il prcesso figlio lui sa già l'intervallo su cui deve lavorare.
Nella variabile tot metto i numeri primi compresi tra 'a' e 'b'.
Quindi ad ogni processo si avrà una variabile tot differente.
Per prima cosa viene stampato il figlio e il numero dei figli. Viene stampato anche ID del processo i-esimo.
A questo punto viene creato l'intervallo tra 'a' e 'b' e messo in tot.

Come si comunicano i risultati tra processi figli e processi padre? Ci sono vari modi per farlo.
Ne usiamo uno (non va più USATO se non richiesto poichè non è troppo efficiente)
Ogni processo figlio crea un file in cui ci mette dentro il risultato. Ho bisogno di nomi distinti per ogni file.
Il processo padre dovrà poi leggere i risultati di tutti i processi. Quindi se si avessero nomi di file uguali tra
processi verrebbbero sovrascritti. Per far ciò verrà messo insieme a conta il PID del processo figlio.
Per creare questa stringa il metodo più semplice è ASPRINTF.
E' come una printf ( FILE, "%s", getpid())
Invece che stampare a schermo, questa stringa viene messa dentro un oggetto che è passato alla fopen come stringa.
Il problema è che nel C le variabili stringhe sono array di caratteri e quindi ho bisogno di allocare lo spazio sufficiente.
ASPRINTF fa tutto lei--> Vede lunghezza stringa e fa malloc della lunghezza della stringa.
Se PID 1521 si avrà *s = "conta1521.txt". *s viene passata a fopen. Free(s) poichè è stata allocata.
Exit(0)--> successo è andato tutto bene. La funzione più importante è la EXIT(0)!!
Se non la si mette succedono guai a non finire--> PROCESSO NON TERMINA.
Il processo figlio passa al ciclo for con i = 1 quindi distinto dal processo padre.
Se tutto è andato bene ogni processo figlio ha creato files con il numero dei primi.
Il processo padre a questo punto ha il compito di calcolare tutti i primi contati dai processi figli.
Per far ciò il padre deve leggere il contenuto del file letti precedentemente.
Però il processo padre non può mettersi subito a leggere i files e vedere cosa c'è.
Il processo padre deve attendere quindi la terminazione dei vari processi figli.
COl secondo ciclo for il padre aspetta i figli uno alla volta utilizzando la funzione:   */
///pid = wait(&status)   --> attende terminazione del primo figlio
/*
Padre si risveglia e il processo padre troverà in PID il numero del processo figlio appena terminato.
Se non vi sono errori , il padre crea la stringa con il PID del processo figlio e apre il file in lettura.
Legge file con fscanf(f, "%d" , &x) . Nella variabile x viene immagazzinato il numero di primi letti dal processo figlio.
La somma dei valori dei numeri primi letti dai processi figli.

Bisogna aggiungere #define _GNU_SOURCE dovrebbe risolvere alcuni warning.

PER FINIRE : makefile.
Parecchi warning ---> funzione che restituisce un valore e io la sto ignorando. ASPRINTF da problemi.
ASPRINTF restituisce il numero di bytes letti. Non utilizziamo quel valore perchè a noi non interessa.

contaprimi 1 1000
--> 168

contapar 1000 5
--> Vengono stampati i figli e i loro PID.
Alla fine viene restituito il valore 168.

F Figlio 3 con pid 2519 cerca fra 601 e 800
F Figlio 1 con pid 2517 cerca fra 201 e 400


cat conta2517.txt
--> 32   (Numero di primi tra 201 e 401)

Lo SCHEDULER decide l'ordine dei processi da eseguire per primi.

NB. I processi di errore vengono scritti con fprintf sul file STDERR --> Viene mostrato a schermo.
Scrivengdo a stderr non li mischio con l'output e in caso se voglio lo stampo.
In modo da avere o solo errori o solo output vero. La funzione PERROR già stampa di suo su stderror.*/

///Mancano i test sull'apertura del file
/*
Mi devo creare una mia xfopen che però mette in più il controllo se file è aperto in modo corretto

XFOPEN

FILE  *xfopen(const char *path, const char *mode, int linea, char *file)
{
    FILE *f= fopen(path,mode);
    if (f == NULL)
    {
        fprintf(stderr, "== %d == Linea: %d, File: %s\n",getpid(),line, file);  // faccio stampare l'INT del processo. Usando __FILE__ e __LINE__
        perror("Errore apertura file");                                                 //La linea del file e il nome del file ma è un informazione totalmente inutile perchè l'errore non è nella linea di questa fprintf(stderr,...)
                                        //Bisogna quindi passare il numero di linea e il nome del file alla xfopen(s,"r",__LINE__,__FILE__);
        exit(1);
    }
    return f;
}


contapar 2000 3
--> 303

Cambio in asprintf dei figli l'estensione dei file in modo tale che mi dia degli errori.
Avendo messo i controlli mi dice il problema, sennò mi avrebbe dato solamente segmentation fault.
Errore apertura file : NO such file or directory.

___________________________________________________________________________

Non è un buon meccanismo utilizzare questo sistema dei file. Dobbiamo usare un sistema interno al programma e che non deve leggere file.
Per questo motivo utilizziamo le PIPE!
Pipe --> collegamento tra input e output. Non lavorano con file ma con file descriptor quindi con interi.

Per creare una PIPE:

definiamo un array di due interi
#define _GNU_SOURCE
#include <unistd.h>

int up[2];
O vanno dal figlio al padre o dal padre al figlio. La comunicazione va in questo senso.
La comunicazione verso il padre (basso verso alto) quindi la chiamiamo up.

MAN --> int pipe(int pipefd[2]);
i figli in questo caso scriveranno in up[1] e scriveranno da up[0]
Se tutto va bene la funzione restituisce 0

ERRORI con PIPE --> viene restituito -1 . Devo invocare perror poichè errore scritto in errno.


int up[2];
e = pipe(up);
if (e!=0) {perror("Creazione pipe up"); exit(1);}

Come programma di prima ma sparisce tutto il codice della creazione file di prima (ASPRINTF , FOPEN ecc)

for (...){
    a=...
    b=...
    if (...){

        fprintf(stderr...);
        int tot = cerca(..);

        close(up[0]); --> ogni figlio chiude la propria lettura

        e= write(up[1], &tot, sizeof(int)) --> primo elemento è file descriptor. Quindi dove verrà scritto, secondo elemento puntatore dove prendere dati da scrivere e numero bytes da scrivere

        assert(e== sizeof(int));
        close(up[1]); --> chiusura di scrittura
        exit(0);

// Se figlio vuole scrivere, l'altro figlio deve attendere che abbia scritto.
Quando figlio scrive certa quantità di dati non troppo elevate dentro PIPE, i dati vengono messi in un modo contiguo.
Tutti i dati del primo, tutti i dati del secondo ecc...
NON SERVE LA WAIT.

close(up[1]); --> chiusura filedescriptor 1
tot = 0 ;
while ( true )
{
    int x;
    e = read(up[0], &x, sizeof(int));  --> i valori letti dalla pipe vengono messi in x
    //Quando padre in lettura, se non c'è nulla in pipe il padre aspetta che arrivino 4 bytes--> offrono meccanismo di sincronizzazione. Attesa in automatico fatta dalla PIPE

    //Se non è aperta da figli estremità di scrittura della PIPE e non c'è nulla in PIPE al padre viene restituito 0;
    //Padre capisce che ha letto tutto ciò che deve leggere e esce.
    if (e==0)break;
    if (e != sizeof(int)){perror("Errore in lettura PIPE"); exit(1);}

    tot += x;

}


Conviene creare un file in c apposito per gli errori chiamato XERRORS.c
Non avrà main ma solo funzioni tipo xfopen() --> collezioni di funzioni.
Nel make file dovrò aggingere
contapar: contapar.o primo.o xerrors.o

Metteremo i test nel file xerrors.c --> creeremo un file xerros.h in cui metteremo i prototipi e poi includeremo nel main.c
*/

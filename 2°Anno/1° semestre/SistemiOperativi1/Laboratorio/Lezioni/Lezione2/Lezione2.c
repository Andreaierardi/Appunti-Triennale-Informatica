/* LEZIONE 2
Non c'è nessuna distinzione tra file di testo e file binario.
Nel file di testo di scriviamo con una fprintf, nei file binari scriviamo con fwrite
fwrite parte dall'indirizzo del puntatore e scrive byte in base a sizeof(int), 1  --> moltiplica
Ogni chiamata va controllata e 'perror' oltre a segnalare errore vi è un return null con exit(1)
Variabile errno registra il numero di errore verificato --> perror guarda variabile errno e stampa messaggio d'errore relativo

-- scrivi 10 pippo
-- ll pippo
--> giovanni giovanni 40 Oct 26 09:40 ecc...  40 sta per bytes

COMANDO : OD (Octal Dump) --> contenuto file in ottale

-- od pippo -t d1     ( Voglio vedere il contenuto di pippo , -t d1 mi dice "considera un byte alla volta e stampa contenuto in decimale")
--> 0000000   1 0 0 0 2 0 0 0 3 0 0 0 4 0 0 0
     0    0
    0000020   5 0 0 0 6 0 0 0 7 0 0 0 8 0 0 0
     0   0
    0000040   9 0 0 0 10 0 0 0
    0000050

i numeri a sinistra sono la posizione all'interno dei file dei numeri a destra
(File binario scritto con macchina intel non funziona su rasberri)

-- od pippo -t d4 -Ad   --> mi raggruppa i byte
--> 0000000    1    2   3   4
    0000016    5    6   7   8
    0000032    9   10
    0000040

-- od makefile -t c -Ad
--> ritorna i caratteri del make file

_____________________________________

-- scrivi -10 pippo
--> Errore  (Assertion 'n>0' failed)

-- scrivi 10 /pippo
--> Errore  (Non posso scrivere un file nella root)
    Errore apertura file : Permission Denied
____________________________________

FILE *f = fopen(nome,"rb");

Quando file finisce fread non legge più nulla, quindi quando e== 0 file finito ed esco.
Se invece fread restituisce valore che non è 0 nè 1 , c'è un problema e stampo errore
Bisognava distinguere i casi in cui feof e ' e == 0'
____________________________________

- valgrind leggi pipppo  (Quindi nome file errato)
--> errore in fread

due puntatore in read , uno sbagliato. Il problema potrebbe essere f (quindi il file potrebbe essere NULL se il file non esiste)
C'è bisogno del controllo!!

if (f == NULL) perror("Errore in lettura") exit(1)
________________________________________

*/ ///Lettura e scrittura con le system call
/*

int fd = open(nome , O_RDONLY)   *////Sto aprendo il file in lettura
/*
if (fd<0) {perror("Errore in apertura file"); exit(1); */  ///in caso di errore da numeri minori di 0 la open.

/*
int somma = 0;
while (true)
{
    int i ;
    int e = read (fd, &i, sizeof(int)); */ ///vuole sapere quanti byte voglio leggere
    /*
    if (e==0) break;  */ /// fine del file
    /*
    if (e<sizeof(int)){ perror("Errore lettura file"); exit(1);}*/ ///errore in lettura
    /*
}


E' pericoloso avere un intero per apertura del file

time leggi pippo  --> determina il tempo di esecuzione

La più lenta è quella con chimate di sistema poichè deve passare in modalità kernel

-fread-
real  0m0.016s
user  0m0.016s
sys   0m0.000s

-read-
real  0m0.203s
user  0m0.016s
sys   0m0.187s

fread fa un solo accesso al disco. Il problema di uso di buffer è che se c'è un problema vengono messi sul disco dati errati
________
*////WRITE
/*
void scriviln(int n , char *nome)
{
int fd = open( nome , O_WRONLY | O_CREAT | 0_TRUNC , 0666);
if (fd<0) {perror("Errore apertura file"); exit(1);
for (int i = 1 ; i<= n; i++)
{
    int e = write(fd, &i, sizeof(int));
    if ( e!=sizeof(int)){perror("Errore scrittura file"); exit(1);}

}
*/
///Con flag si fa in modo di sovrascrivere il file se se ne trova uno con lo stesso nome,
///Il 0666  (in ottale  110 110 110) sono i permessi per rwx per u , g , o . Eseguibile da nessuno.
/// In realtà sono in combinazione con quelli settati in mask
/*umask -p  --> limita ciò che mettete nei permessi del file ovvero
--> umask 0022

quindi 110 110 110
       000 010 010
       __________
       000 010 010

--> umask serve per non dare permessi ad alcune entità
Non da i permessi a quelli con 1 , quindi non possono scrivere  g , o
*/

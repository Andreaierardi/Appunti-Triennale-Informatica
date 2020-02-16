#include <stdio.h>
#include <stdlib.h>

//Definisco la struttura coordinate
typedef struct
{
    int x ;
    int y ;
} COORDINATE;
//Definisco la struttura per la creazione delle liste
typedef struct linked_list
{
    COORDINATE d;
    struct linked_list *next;
} ELEMENT;
typedef ELEMENT *LINK;
//Definisco la funzione newnode
LINK newnode()
{
     return (malloc(sizeof(ELEMENT))); //Alloco memoria in grado da contenere ELEMENT memoria
}

//Prototipi delle funzioni
LINK creaDaFile();
COORDINATE piuNord(LINK lis, COORDINATE punto);
LINK sottoEquatore(LINK lis);
void printLis(LINK lis);

//Main
int main()
{
    printf("\n=======================================\n\nLista dal file\n"); //print per organizzare al meglio la stampa
    LINK lis = creaDaFile(); //Assegno la lista ritornata dalla funzione creaDafile() alla lista del main
    printLis(lis); //Richiamo la funzioni di stampa per verificare che la lista sia stata creata correttamente

    printf("\n======================\nCerca il punto più al nord del quadrante:  ");
    COORDINATE point; //definisco un punto
    int e = scanf("%d %d",&point.x, &point.y);  //Utilizzo la scanf per passare tramite terminale le coordinate
    //del punto da passare alla funzione piuNord()
    //verifico che la scanf abbia realmente letto due interi
    if (e != 2 ){perror("Errore dati in input");exit(1);} //Scrivo che è avvenuto un errore ed esco dal programma
    COORDINATE nord = piuNord(lis, point); //Definisco una nuova COORDINATE e la pongo uguale a quella ritornata dalla funzione
    //Siccome non è detto che vi siano punti, essendo tmp inizializzato a 0 nella funzione.
    //Quindi quando ricevo un punto (0,0) significa che vi è qualche errore
    if (nord.x != 0 && nord.y != 0 )printf("Coordinata più a nord del  punto: (%d,%d)\n",nord.x,nord.y);
    //
    else printf("Nessuna coordinata più a nord del punto: (%d,%d)\n",nord.x,nord.y);
    printf("\n======================\nCoordinate al di sotto dell'asse delle X\n");
    LINK newlista = sottoEquatore(lis);
    printLis(newlista);
}
//Funzione per la stampa di una lista
void printLis(LINK lis)
{
    //scorro tutta la lista ed ad ogni iterazione stampo i campi x e y
    while (lis != NULL)  {printf("(%d,%d)\n",lis->d.x,lis->d.y); lis = lis->next;}
}

//Funzione per la creazione di una lista tramite lettura da file
LINK creaDaFile()
{

    FILE *fp = fopen("coordinate.txt", "r");  //Apertura del file fp di nuove coordinate.txt in lettura (r)
    if(fp == NULL ) {perror("Errore apertura file"); exit(1);} //verifico che il file esista

    //Stesso metodo di aggiunta in coda del corso di fondamenti
    LINK lista;
    LINK head , tail;
    head = NULL;
    tail = NULL;
    //scorro finchè non raggiungo feof del file fp --> Il che significa che scorro fino EOF (end of file, fine del file)
    //E' una funzione del linguaggio e viene passato il puntatore del file come paramentro. Si può trovare nel manuale da terminale
    while (!feof(fp))
    {
        lista = newnode(); //creo un nuovo nodo
        int e = fscanf(fp,"%d %d", &lista->d.x, &lista->d.y);  //utilizzo la fscanf per prelevare i dati di x e y dal file
        if (e != 2 ) break ; //Verifico che la fscanf legga effettivamente due interi ad iterazione del ciclo
        lista->next = NULL; //lista -> next = NULL il puntatore all'elemento successivo è impostato a NULL

        if ( head == NULL ) {head = lista; tail = lista;} //Se non ho elementi in testa li aggiungo e aggiorno coda e testa
        else {tail -> next = lista ; tail  = lista;} //Se ho elementi in testa aggiungo in coda


    }
    return head;  //ritorno la testa della lista

}
//Funzione che trova il punto più nord del quadrante che contiene il punto passato come parametro
//Siccome deve ritornare una coordinata la funzione è definita con COORDINATE piuNord()
COORDINATE piuNord(LINK lis, COORDINATE punto)
{

    int quadrante; //definisco un intero quadrante
    //Determino in quale quadrate si trova il punto passato come paramentro
    if ((punto.x<=0) && (punto.y>=0))  quadrante= 1;  //Se x <= 0 e y >= 0 allora il punto si trova nel primo quadrante ecc..
    if ((punto.x>=0) && (punto.y>=0))  quadrante= 2;
    if ((punto.x<=0) && (punto.y<=0))  quadrante= 3;
    if ((punto.x>=0) && (punto.y<=0))  quadrante= 4;
    //definisco una coordinata di supporto in modo che trovi il punto più a nord di un determinato quadrante
    COORDINATE tmp;
    tmp.x = 0;
    tmp.y = 0 ;
    while ( lis != NULL)
    {
        if ((quadrante == 1)&&(lis->d.x<0)&&(lis->d.y>0))
            if ((lis->d.y> tmp.y) &&(lis->d.y > punto.y))
                tmp = lis->d;
        if ((quadrante == 2)&&(lis->d.x>0)&&(lis->d.y>0))
            if ((lis->d.y> tmp.y) &&(lis->d.y > punto.y))
                tmp = lis->d;
        if ((quadrante == 3)&&(lis->d.x<0)&&(lis->d.y<0))
        {printf("Quadrante 3\nLIS: %d - TMP: %d - PUNTO: %d\n",lis->d.y,tmp.y,punto.y);
           if (-2 > -3 ) printf("\nUAUAU\n");
            if ((lis->d.y> tmp.y) &&(lis->d.y >punto.y))
                tmp = lis->d;}
        if ((quadrante == 4)&&(lis->d.x>0)&&(lis->d.y<0))

            {if ((lis->d.y > tmp.y) &&(lis->d.y > punto.y))
                tmp = lis->d;
            }

        lis = lis->next ;

    }
    return tmp;

}

//Funzione che ritorna una lista di punti che si trovano tutti al di sotto dell'equatore (quindi con y<0)
LINK sottoEquatore(LINK lis)
{
    //Solita struttura di aggiunta in coda definita nel corso di sperimentazioni
    LINK lista, head , tail ;
    head = tail = NULL;

    while ( lis != NULL )//Ciclo while per scorrere tutta la lista
    {
        if (lis->d.y < 0 ) //Se la coordinata si trova al di sotto dell'asse delle x (quindi y<0 )
        {
            lista  = newnode(); //Allora creo un nuovo nodo
            lista -> d = lis->d;//Pongo il riferimento del nodo appena creato con la coordinata della lista
            lista -> next = NULL; //Il riferimento al nodo successivo è nullo
            if (head== NULL){head = lista ; tail = lista ; } //Se lista vuota aggiungo in testa
            else {tail-> next = lista ; tail = lista;}//altrimenti aggiungo in coda
        }
        lis = lis->next; //Scorro la lista sia che l'elemento è stato aggiunto, sia che non è stato aggiunto
    }

    return head ; //ritorno la testa della lista
}

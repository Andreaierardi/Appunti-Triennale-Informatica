#include "scopa.h"

int main()
{
    Pila *p1= makePila();
    Pila *p2= makePila();
    Pila *p3= makePila();
    Pila *p4= makePila();

    Lista *tavolo = makeLista();
    Coda *mazzo = creaMazzo(40);
    puts("\n=================MAZZO==================\n");
    stampa(mazzo->primo);

    puts("\n===========MAZZO MESCOLATO============\n");
    Mescola(mazzo);
    stampa(mazzo->primo);
    puts("===========DAI CARTE================\n");
    for (int i = 0; i<3 ; i++)
    {
          p1 = DaiCarte(mazzo,p1);
          p2 = DaiCarte(mazzo,p2);
          p3 = DaiCarte(mazzo,p3);
          p4 = DaiCarte(mazzo,p4);
    }


    printf("G1: ");stampa(p1);
    printf("G2: ");stampa(p2);
    printf("G3: ");stampa(p3);
    printf("G4: ");stampa(p4);

    puts("==============TAVOLO=================\n");
    tavolo = CarteSulTavolo(mazzo);
    stampa(tavolo);

    puts("==============FASE DI GIOCO==============");
    int mano = 1;
    while (mazzo->primo!=NULL)
    {
        printf("_________________________________\nMano: %d |\n________|\n\n",mano);
        mano++;

        if((p1==NULL) &&(p2==NULL) &&(p3==NULL) &&(p4==NULL))
        {
            printf("CARTE\n");
           for (int i = 0; i<3 ; i++)
            {
              p1 = DaiCarte(mazzo,p1);
              p2 = DaiCarte(mazzo,p2);
              p3 = DaiCarte(mazzo,p3);
              p4 = DaiCarte(mazzo,p4);
            }

        }
        printf("G1: ");stampa(p1);
        printf("G2: ");stampa(p2);
        printf("G3: ");stampa(p3);
        printf("G4: ");stampa(p4);

        while( (p1!=NULL)&&(p2!=NULL) &&(p3!=NULL) &&(p4!=NULL))
        {

            tavolo= inserisci(pop(&p1),tavolo);
            tavolo= inserisci(pop(&p2),tavolo);
            tavolo= inserisci(pop(&p3),tavolo);
            tavolo= inserisci(pop(&p4),tavolo);

        }
        printf("----------TAVOLO---------\n");stampa(tavolo);


    }
    puts("======SITUAZIONE FINALE=========\n");
    puts("Giocatori senza carte\n_________________");
	puts("GIOCATORE 1: ");
	stampa(p1);
	puts("GIOCATORE 2: ");
	stampa(p2);
	puts("GIOCATORE 3: ");
	stampa(p3);
	puts("GIOCATORE 4: ");
	stampa(p4);
    puts("\nTavolo tutte le carte\n_________________");
	puts("TAVOLO");
	stampa(tavolo);
	puts("\n=======FINE DEL GIOCO========");

    return 0;

}

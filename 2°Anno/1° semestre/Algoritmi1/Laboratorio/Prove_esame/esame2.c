#include <stdio.h>
#include <stdlib.h>
//Strutture
struct nodo
{
    int inforadice;
    struct nodo *sinistro,*destro;
};

struct nodo *radice;

struct nodo *inserisci( struct nodo *radice, int e )
{
    struct nodo *aux;
    if (radice == NULL)
    {
        aux = malloc(sizeof(struct nodo));
        if (aux)
        {
            aux->inforadice = e;
            aux->destro = aux->sinistro = NULL;
            return aux;
        }
        else
        {
            printf("Memoria non allocata\n");
        }
    }
    else if (e < radice->inforadice)
        radice->sinistro = inserisci(radice->sinistro,e);
    else if(e> radice->inforadice)
        radice->destro = inserisci (radice->destro,e);

    return radice;

}
void print(struct nodo *radice, int V);
int altezza(struct nodo *radice);
void minMax(struct nodo *radice, int *min , int *max);

int main()
{
    struct nodo *root = NULL;
    root = inserisci ( root, 50);
    root = inserisci ( root, 72);
    root = inserisci ( root, 54);
    root = inserisci ( root, 76);
    root = inserisci ( root, 67);
    root = inserisci ( root, 17);
    root = inserisci ( root, 23);
    root = inserisci ( root, 12);
    root = inserisci ( root, 9);
    root = inserisci ( root, 14);
    root = inserisci ( root, 19);
    int val = 20;
    printf("Elenco numeri <= a %d: ",val);
    print(root,val);
    int h = altezza(root);
    printf("\nAltezza dell'albero: %d\n",h);
    int max,min ;
    minMax(root,&min, &max);
    printf("Massimo :%d\nMinimo: %d\n",max,min);
}

void print(struct nodo *radice, int V)
{
    if (radice != NULL)
    {
        if(radice->inforadice <= V)
                printf("%d ",radice->inforadice);

        if (radice->inforadice >= V)
            print(radice->sinistro,V);
        if(radice->inforadice < V )
        {
            print(radice->sinistro,V);
            print(radice->destro,V);
        }
    }
}

int max(int a, int b)
{
    if (a>=b)
        return a;
    return b;
}
int altezza(struct nodo *radice)
{
    if (radice == NULL) return -1;
    return 1+max(altezza(radice->destro),altezza(radice->sinistro));
}

void minMax(struct nodo *radice, int *min , int *max)
{
    if (radice == NULL)
    {
        *min = -1;
        *max = -1;
    }

    struct nodo *tmp = radice;
    while (tmp->destro != NULL)
        tmp = tmp->destro;
    *max = tmp->inforadice;

    tmp = radice;
    while ( tmp->sinistro != NULL)
        tmp = tmp->sinistro;
    *min = tmp ->inforadice;
}

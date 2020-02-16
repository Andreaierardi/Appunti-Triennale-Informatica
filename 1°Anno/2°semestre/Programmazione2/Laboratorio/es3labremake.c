#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#define BUFFER 100

typedef struct COORDINATE
{
    int x;
    int y;
} COORDINATE;

typedef struct linked_list
{
    COORDINATE d;
    struct linked_list  *next;
} ELEMENT;
typedef  ELEMENT *LINK;

LINK newnode(){return(malloc(sizeof(ELEMENT)));}

//function calls
LINK makecolist();
void printlist(LINK lis);

int main()
{
    LINK lista=makecolist();
    printlist(lista);
}

LINK makecolist()
{
    LINK p, head,tail;
    head=NULL;
    tail=NULL;
    int n;
    int i=0;

    printf("Quante coordinate vuoi aggiungere? \n");
    scanf("%d",&n);

    while(i<n)
        {
            p=newnode();
            printf("Valore di X: ");
            scanf("%d",&p->d.x);
            printf("Valore di Y ");
            scanf("%d",&p->d.y);

            if (head==NULL){head=p;tail=p;}
            else{tail->next=p;tail=p;}
            i++;
        }
        return (head);

}

void printlist(LINK lis)
{
    int i =1;
    printf("\n");
    while (lis!=NULL)

    {
        printf("%d° - (%d , %d) \n",i,lis->d.x,lis->d.y);

        lis=lis->next;
        i++;
    }
}

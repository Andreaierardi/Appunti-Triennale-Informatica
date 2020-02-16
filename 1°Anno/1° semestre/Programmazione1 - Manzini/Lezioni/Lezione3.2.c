#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int n,m;


    printf("Inserisci un intero\n");
    int tot= scanf("%d  %d",&n,&m);
    printf("Hai inserito: %d valori \n",tot);
    printf("La loro somma è %d\n",n+m);
    return 0;

}

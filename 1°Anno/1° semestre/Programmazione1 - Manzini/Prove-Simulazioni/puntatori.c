#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    int numero=3;
    int *puntatore=&numero;
    printf("Il numero � %d\n--------\nIl puntatore � %d\n------\nIl numero a cui punta p � %d\n",numero,puntatore,*puntatore);
    return 0;

}

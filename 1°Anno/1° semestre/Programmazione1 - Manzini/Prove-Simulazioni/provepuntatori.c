#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>

int printArray(int *v, int n)
{
    for (i=0;i<n; i++){
        printf("Elemento [%d]: %d\n",i,v[i]);
    }
}

int main()
{
    int v[]= { 3,5,2,7,4,2,7 };
    printArray(v,7);
}


int main(){
    int *v;
    int i,n ;
    printf ("Quanti elementi vuoi nell'array ");
    scanf("%d",&n);

    v = (int*) malloc(n*sizeof(int));

    for (i=0; i<n;i++){
        printf(" Elemento n. %d: \n",i+1 );
        scanf("%d",&v[i]);
    }

    for (i=0; i<n; i++){
        printf("Elemento n. %d: %d\n");
    }
    free(v);
    return 0;
}


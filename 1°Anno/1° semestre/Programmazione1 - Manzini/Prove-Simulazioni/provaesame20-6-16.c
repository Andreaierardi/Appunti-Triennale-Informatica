#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <assert.h>

int *dispari(int a[], int n ){
        int *disp=(int *)malloc(n*sizeof(int));
        assert(disp!=0);
        for (int i=0;i<n;i++)
            if (a[i]%2!=0)
                disp[i]=a[i];
        return disp;
}

int *pari(int a[],int n){
        int *par=(int *)malloc(n*sizeof(int));
        assert(par!=0);
        for (int i=0;i<n;i++)
            if (a[i]%2==0)
                par[i]=a[i];
        return par;

}

int main(int argc, char *argv[])
{
    if(argc==1) {
        printf("Uso: %s numero\n",argv[0]);
        return 1;
    }\
    int n = argc-1;
    int a[n]; // ho creato a[0], a[1], ... a[n-1]
    // conversione da stringa a interi
    for(int i=0;i<n;i++) {
        a[i] = atoi(argv[i+1]);
        }

    int *k;
    k= dispari(a,n);

    int parisomma=0;
    int *som;
    assert(som!=0);
    som= pari(a,n);
    for(int i=0;i<n;i++){
        parisomma +=som[i];
    }

    int conta=0;
    for(int i=0; i<n; i++){
        if (k[i]!=0){
            conta +=1;
    }}
    printf("\nNumero elementi dispari: %d\n",conta);
    printf("Elementi dispari: ");
    for(int i=0; i<n; i++){
        if (k[i]!=0){
            printf("%d ",k[i]);
    }}
    printf("\nSomma dei pari: %d\n",parisomma);
    }

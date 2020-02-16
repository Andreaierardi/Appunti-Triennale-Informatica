#include <stdio.h>
#include<stdbool.h>
#include <stdlib.h>
#include <assert.h>
void func(int n,char a[]){

    for (int i=0;i<n;i++)
    printf("%d\n",a[i]);
}
int conta(int n, char a[])
{
    int conta=0;
    for (int i=0;i<n;i++)
        conta+=1;
    return conta;
}
int main(int argc, char *argv[]){
    int n= argc-1;
    char a[n];
    for (int i=0;i<n;i++)
            a[i]=atoi(argv[i+1]);

    func(n,a);
    int l=conta(n,a);
    printf("-----------\nIl numero di elementi è %d\n",l);
    return 0;
}

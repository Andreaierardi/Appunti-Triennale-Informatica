#include <stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<stdbool.h>

int main(int argc, char*argv[]){
    if(argc!=2) {
        printf("Uso: %s n1 n2 n3 n4 .... \n",argv[0]);
        return 1;
    }
    int n=atoi(argv[1]);
    int c;
    int count1=0,count2=0, count3;
    for (int i=0; i<n ; i++){

        puts("Inserisci una figa: ");
        scanf("%d",&c);
        if (c>=1&&c<=10)
            count1+=1;
        if (c>=30&&c<=40)
            count2+=1;
        if (c>=5&&c<=50)
            count3+=1;
    }
    printf("\nNumeri in 1-10: %d\n",count1);
    printf("Numeri in 30-40: %d\n",count2);
    printf("Numeri in 5-50: %d\n",count3);
    return 0;
    }


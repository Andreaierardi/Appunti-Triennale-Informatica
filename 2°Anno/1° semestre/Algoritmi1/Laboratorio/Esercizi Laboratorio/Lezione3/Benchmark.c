//Andrea Ierardi N.Matricola :20018785
//Edoardo Favorido N. Matricola :20018971
#include <stdlib.h>
# include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX 20
#define NUMERO_RUN 10

void  bubblesort(int A[], int N);

void quicksort(int array[], int begin, int end);
int partition(int array[], int begin, int end);

void fixHeap(int A[], int i, int HeapSize);
void HeapSort(int A[], int ArraySize);
void Heapify(int A[], int ArraySize);
int left(int i);
int right(int i);
int parent (int i);

void benchmark();
void swap(int *A,int *B);

int * copyaArray (int *inputArray, int N);
int *creaArrayRandom (int N);
bool check_sort(int *a, int n);
void stampasufile(char *nome, double *array,int lung, FILE *fp);

int main()
{
   benchmark();

}

void benchmark()
{
    FILE *fp = fopen("ris.csv","w");
    if (fp == NULL) {perror("Errore apertura file");exit(1);}
    int lung = 0 ;
    int dimensioni[] = {5, 10 , 25, 50, 100, 200, 500, 1000, 2000, 5000,10000};
    lung = 11;

    double bubble[lung];
    double heap[lung];
    double quick[lung];
    fprintf(fp,"ALGORITMI,");
    for (int i = 0 ; i < lung ; i++)
    {
        if (i+1 == lung) fprintf(fp,"%d\n",dimensioni[i]);
        else fprintf(fp,"%d,",dimensioni[i]);
    }
    printf("\n==========Risultati==========\n");
    for (int i = 0 ; i < lung; i++)
    {
        int N = dimensioni[i];

        double timeQuick, timeBubble, timeHeap;
        timeBubble= timeQuick = timeHeap= 0;
        for (int k = 1 ; k < NUMERO_RUN; k++)
        {
            clock_t T1, T2;
            int *testArray = creaArrayRandom(N);
            int *arrayDaOrdinare = copyaArray(testArray, N);


            T1 = clock();
            bubblesort(arrayDaOrdinare, N);
            T2 = clock();
            if (!check_sort(arrayDaOrdinare,N)) {perror("Bubblesort non ordina correttamente");exit(1);}
            timeBubble+= ((double)(T2 - T1))/CLOCKS_PER_SEC;
            free(arrayDaOrdinare);

            arrayDaOrdinare = copyaArray(testArray, N);
            T1 = clock();
            quicksort(arrayDaOrdinare,0, N);
            T2 = clock();
            if (!check_sort(arrayDaOrdinare,N)) {perror("Quicksort non ordina correttamente");exit(1);}
            timeQuick+= ((double)(T2 - T1))/CLOCKS_PER_SEC;
            free(arrayDaOrdinare);


            arrayDaOrdinare = copyaArray(testArray, N);
            T1 = clock();
            HeapSort(arrayDaOrdinare,N);
            T2 = clock();
            if (!check_sort(arrayDaOrdinare,N)) {perror("Heapsort non ordina correttamente");exit(1);}
            timeHeap+= ((double)(T2 - T1))/CLOCKS_PER_SEC;
            free(arrayDaOrdinare);

            free(testArray);

        }

        printf("BubbleSort: %lf --- QuickSort: %lf --- HeapSort: %lf ---\n",timeBubble,timeQuick,timeHeap);
        bubble[i] = timeBubble;
        quick[i]= timeQuick;
        heap[i]= timeHeap;
    }

    stampasufile("BubbleSort",bubble,lung,fp);
    stampasufile("QuickSort",quick,lung, fp);
    stampasufile("HeapSort",heap,lung ,fp);
    fclose(fp);
}
void stampasufile(char *nome, double *array,int lung, FILE *fp)
{
    fprintf(fp,"%s,",nome);
    for (int i = 0 ; i<lung ; i++)
    {
        if(i+1 == lung)fprintf(fp,"%fl\n",array[i]);
        else fprintf(fp,"%fl,",array[i]);
    }
}

///Generare Array Random
int *creaArrayRandom (int N)
{
    srand(time(NULL));
    int *arr= (int *)malloc (N * sizeof (int));

    for (int i= 0; i < N; i++) arr[i] =rand()%N;
    return arr;
}

///Copia di un Array
int * copyaArray (int *inputArray, int N)
{
    int *arr= (int *)malloc (N * sizeof (int));
    memcpy(arr, inputArray, N * sizeof(int));
    return arr;
}
///Check sort
bool check_sort(int *a, int n)
{
  for(int i=0; i < n-1; i++)
     if(a[i] > a[i+1]) return false;
  return true;
}
///Codice Quick Sort
int partition(int array[], int begin, int end)
{

    int pivot, l, r;
    pivot = array[begin];
    l = begin + 1;
    r = end;
    while(l <= r)
    {
        while(array[r] > pivot) r=r-1;
        while((array[l] <= pivot) && (l <= r)) l=l+1;
        if (l<r)
        {
            swap (&array[l], &array[r]);
            l++;
            r--;
        }
    }
    swap (&array[begin], &array[r]);
    return r;
}

void quicksort(int array[], int begin, int end) {
    int q;
    if (begin<end)
    {
        q= partition(array, begin, end);
        quicksort(array, begin, q-1);
        quicksort(array, q+1, end);
    }
}

///Codice Heap Sort


void swap(int *A,int *B)
{

     int temp;
	  temp=*A;
	  *A=*B;
 	  *B=temp;
}

int left(int i)
    {
        return 2*i+1;
    }

int right(int i)
{
    return 2*i+2;
}

int parent (int i)
{
     return (i-1)/2;
}


void Heapify(int A[], int ArraySize)
{
    for(int i=ArraySize/2;i>=0;i--)
        fixHeap(A, i, ArraySize);

}

void fixHeap(int A[], int i, int HeapSize)
{
    int l = left(i);
    int r = right(i);
    int largest;
    if ((l < HeapSize) && (A[l] > A[i]))
        largest=l;
    else
       largest= i;
    if ((r < HeapSize) &&(A[r] > A[largest]))
        largest = r;
    if (largest != i)
        {
            swap(&A[i], &A[largest]);
            fixHeap (A, largest, HeapSize);
        }
}
void HeapSort(int A[], int ArraySize)
{
    int HeapSize=ArraySize;
    Heapify(A, ArraySize);
    for(int i=ArraySize-1;i>=1;i--)
        {
            swap(&A[0], &A[i]);
            HeapSize=HeapSize - 1;
            fixHeap(A, 0, HeapSize);
        }
}



///Codice Bubble Sort
void  bubblesort(int A[], int N)
{

    int ultimo = N-1;
    int scambiati = 1;
    int tmp ;
    while (scambiati > 0)
    {
        scambiati = 0;
        for (int i = 0; i<ultimo;i++)
            if (A[i]> A[i+1])
            {
                swap(&A[i], &A[i+1]);
                tmp = i ;
                scambiati = 1;
            }
         ultimo = tmp;
    }
}

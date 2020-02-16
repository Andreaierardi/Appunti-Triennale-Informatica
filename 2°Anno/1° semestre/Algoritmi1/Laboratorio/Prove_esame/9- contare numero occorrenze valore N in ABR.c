// contare il numero di occorrenze di N in un albero binario
int numeroOccorrenzeDiN (Albero a, int n){
    if(a == NULL)
        return 0;

    if(a->radice == n){
        return 1 + numeroOccorrenzeDiN(a->sinistro, n) + numeroOccorrenzeDiN(a->destro, n);
    }

    else {
        return numeroOccorrenzeDiN(a->sinistro, n) + numeroOccorrenzeDiN(a->destro, n);
    }
}

// Calcolare il numero di nodi di un albero binario.
int numeroNodi (Albero a){
    if (a == NULL){
        return 0;
    }
    if ((a->sinistro == NULL) && (a->destro == NULL)){
        return 1;
    }
    int numNodiSx = numeroNodi(a->sinistro);
    int numNodiDx = numeroNodi(a->destro);
    return 1 + numNodiSx + numNodiDx;
}

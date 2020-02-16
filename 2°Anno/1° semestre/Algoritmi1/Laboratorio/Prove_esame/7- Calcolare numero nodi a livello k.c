// Fissato un livello K, calcolare il numero di nodi presenti a livello K.
int numeroNodiALivello (Albero a, int k){
    if (a == NULL)
        return 0;

    if(k == 0)
        return 1;

    return (numeroNodiALivello(a->sinistro, k-1) + numeroNodiALivello(a->destro, k-1));
}

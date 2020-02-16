// Calcolare il numero di foglie di un albero binario.
int numeroFoglie (Albero a){
    if (a == NULL){ //se nullo ritorno 0
        return 0;
    }
    if ((a->sinistro == NULL) && (a->destro == NULL)){
        return 1; //se il nodo non ha figli ritorno 1 perchè vuol dire
        //che è una foglia
    }
    int numfoglieSx = numeroFoglie(a->sinistro); //scendo a sinistra
    int numfoglieDx = numeroFoglie(a->destro); //scendo a destra
    return (numfoglieSx + numfoglieDx); //sommo i numeri delle foglie
    //dei sottoalberi sinistro e destro
}

// Data un nodo di un ABR, restituire il suo predecessore
Albero predecessore (Albero a, int k){
    if(a == NULL)
        return NULL;

    Albero *tmp = NULL;

    if(a->radice == K)
        tmp = a->radice;

    if(tmp == NULL)
        tmp = predecessore(a->destro, k);
    if(tmp == NULL)
        tmp = predecessore(a->sinistro, k);

    return tmp;
}

Albero predecessore (Albero a, Albero elem){
    Albero pred = NULL;
    while (a != NULL){
        if(elem <= a->radice)
            a = a->sinistro;
        else {
            pred = a;
            a = a->destro;
        }
    }

    return pred;
}

Albero successore(Albero a, Albero elem){
    Albero succ = NULL;

    while (a != NULL){
        if(elem >= a->radice)
            a = a->sinistro;
        else{
            succ = a;
            a = a->destro;
        }
    }

    return succ;
}

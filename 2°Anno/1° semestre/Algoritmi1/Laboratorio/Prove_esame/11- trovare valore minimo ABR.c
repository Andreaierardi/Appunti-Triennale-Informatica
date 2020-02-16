// Cercare il valore minimo dell’albero sfruttando le caratteristiche dell’ABR
Albero cercaValoreMinimoABRricorsivo (Albero a){
    if(a == NULL)
        return NULL;

    if(a->sinistro == NULL)
        return a;

    else
        return(cercaValoreMinimoABRricorsivo(a->sinistro));
}

ALbero cercaValoreMinimoABRiterativo (Albero a){
    if(a == NULL)
        return NULL;

    if(a->sinistro == NULL)
        return a;

    while(a->sinistro != NULL){
        a = a->sinistro;
    }
    return a;
}

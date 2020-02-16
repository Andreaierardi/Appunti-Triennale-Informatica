// calcolare l’altezza minima di un albero binario
int altezzaMinima(Albero a){
    if(a == NULL){
        return -1;
    }
    if (a->sinistro == NULL){
        return altezzaMinima(a->destro) + 1;
    }
    if (a->destro == NULL){
        return altezzaMinima(a->sinistro) + 1;
    }

    return (min(altezzaMinima(a->sinistro), altezzaMinima(a->destro)) + 1);
}

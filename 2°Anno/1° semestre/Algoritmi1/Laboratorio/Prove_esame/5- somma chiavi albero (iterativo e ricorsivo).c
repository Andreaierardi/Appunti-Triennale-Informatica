// Sommare le chiavi di un albero binario (ricorsivamente ed iterativamente).
int sommaChiavi(Albero a){ //ricorsivo
    if (a == NULL)
        return 0;

    else{
        return (a->radice + sommaChiavi(a->sinistro) + sommaChiavi(a->destro));
    }
}

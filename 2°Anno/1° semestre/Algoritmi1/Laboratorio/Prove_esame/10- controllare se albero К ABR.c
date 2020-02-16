//Controllare che un albero binario è anche un albero binario di ricerca.
int controlloAlberoSeABR(Albero a){
    Albero prev = NULL;

    if (a == NULL)
        return 1;

    if(!controlloAlberoSeABR(a->sinistro))
        return 0;

    if(prev != NULL && a->radice <= prev->radice)
        return 0;

    prev = a;

    return controlloAlberoSeABR(a->destro);
}

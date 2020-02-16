//Determinare se un albero binario � �pieno�.
bool alberoPieno(Albero a){
    if(a == NULL)
        return true;

    if(a->sinistro == NULL && a->destro == NULL)
        return true;

    if(a->sinistro != NULL && a->destro != NULL){
        return (alberoPieno(a->sinistro) && alberoPieno(a->destro));
    }
    return false;
}

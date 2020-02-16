// Data la root di un BST, implementare la funzione “transpose” che “ribalta” orizzontalmente l’albero
Albero ribaltaAlbero (Albero a){
    Albero tmp = a->sinistro;
    a->sinistro = a->destro;
    a->destro = tmp;
    if(a->sinistro != NULL)
        ribaltaAlbero(a->sinistro);
    if(a->destro != NULL)
        ribaltaAlbero(a->destro);
}

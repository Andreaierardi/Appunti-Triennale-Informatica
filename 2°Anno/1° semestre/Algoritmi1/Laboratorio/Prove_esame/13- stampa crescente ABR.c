// Stampare gli elementi di un ABR in maniera crescente
void stampaElementiABRCrescente (Albero a){
    if (a == NULL)
        return;

    stampaElementiABRCrescente(a->sinistro);

    printf("Elemento: %d", a->radice);

    stampaElementiABRCrescente(a->destro);
}

//calcolare l'altezza di un albero binario
int altezzaABR (Albero a){
    if (a == NULL){ //se nullo ritorno -1
        return -1;
    }
    int altezzaSx = altezzaABR(a->sinistro); //scendo nella parte sinistra
    int altezzaDx = altezzaABR(a->destro); //scendo nella parte destra
    return 1 + max(altezzaSx, altezzaDx); //sommo uno al massimo tra Dx e Sx
}

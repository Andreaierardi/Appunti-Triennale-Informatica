//Cercare un elemento x tra le chiavi di un albero binario.
Albero ricercaChiave(Albero a, int chiave){
    if((a == NULL) || (a->radice == chiave))
        return a;
    else if (chiave <= a->radice)
        ricercaChiave(a->sinistro, chiave); //se minore ricerco solo nel sottoalbero sinistro (proprità ABR)
    else
        ricercaChiave(a->destro, chiave); //se maggiore ricerco solo nel sottoalbero destro (proprietà ABR)
}

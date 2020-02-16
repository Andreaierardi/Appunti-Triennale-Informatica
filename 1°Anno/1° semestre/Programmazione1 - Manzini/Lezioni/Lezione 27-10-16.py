# esercizi su liste


# data una lista di interi e un intero n
# verificare se tutti gli interi sono < n
def tutti_minori(lis, n):
    assert isinstance(lis, list), "Il primo agomento deve essere lista"
    assert isinstance(n,int), "Il secondo argomnto deve essere intero"
    for i in range(0,len(lis)):
        if lis[i]>= n:
            return False
    return True

# come sopra ma senza usare il return in mezzo al codice
def tutti_minori_noreturn(lis, n):
    assert isinstance(lis, list), "Il primo agomento deve essere lista"
    assert isinstance(n,int), "Il secondo argomnto deve essere intero"
    tutti_piccoli = True
    for i in range(0,len(lis)):
        if lis[i]>= n:
            tutti_piccoli = False
            break
    return tutti_piccoli


# come sopra ma senza usare ne return ne break
# il ciclo for deve essere restituito da un while
def tutti_minori_nobreak(lis, n):
    assert isinstance(lis, list), "Il primo agomento deve essere lista"
    assert isinstance(n,int), "Il secondo argomnto deve essere intero"
    tutti_piccoli = True
    i=0
    while i<len(lis) and tutti_piccoli==True:        
        if lis[i]>= n:
            tutti_piccoli = False
        i += 1    
    return tutti_piccoli



# data una lista di stringhe restituisce la piu' lunga
def stringa_lunga(lis):
    assert isinstance(lis, list), "Il primo agomento deve essere lista"
    assert len(lis)>0, "Non voglio lista vuota"
    stringa_lunga = lis[0]
    for  i in range(1,len(lis)):
        if len(lis[i])>len(stringa_lunga):
            stringa_lunga = lis[i]
    return stringa_lunga


# data una lista di stinghe lis
# restituisce la lista degli elementi di lis di lunghezza massima
def stringhe_lunghe(lis):
    assert isinstance(lis, list), "Il primo agomento deve essere lista"
    assert len(lis)>0, "Non voglio lista vuota"
    max_lung = len(stringa_lunga(lis))
    # ora creo lista di tutte le stringhe di lunghezza max_lung
    risultato = []
    for  i in range(0,len(lis)):
        if len(lis[i])==max_lung:
            risultato = risultato + [ lis[i] ]
    assert len(risultato)>0, "Qualcosa non va non so cosa"        
    return risultato


# crea una nuova lista contenente gli elementi di lis
# ma senza duplicati
def elimina_duplicati(lis):
    risultato = []
    for i in range(0,len(lis)):
        # aggiunge lis[i] a risultato solo se non e' gia' presente
        if (lis[i] in risultato)==False:
            risultato += [ lis[i] ]
    return risultato


# calcola intersezione delle liste lis1 lis2            
def intersezione(lis1,lis2):
    risultato = []
    for i in range(0,len(lis1)):
        if lis1[i] in lis2:
            # non mette duplicati nell'intersezione 
            if (lis1[i] in risultato)==False:
                risultato += [ lis1[i] ]
    return risultato

# esercizio per casa 1
# riscrivere la funzione stringhe_lunghe senza 
# chiamare stringa_lunga, cioe' facendo un unico passaggio
# sullla lista data in input

# esercizio per casa 2
# scrivere una funzione che data una lista di interi
# restituisce True se gli elementi >= 0 sono maggiori
# di quelli <0, e False altrimenti

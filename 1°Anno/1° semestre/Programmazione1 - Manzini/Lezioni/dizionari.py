# funzione da usare con sorted per ordinare
# una lista di coppie (array di due elementi) sulla base
# del secondo elemento della copia, scrivendo ad esempio
# sorted(a,key=secondo)
#
def secondo(x):
    return x[1]

# ==================================
# esempi di uso dei dizionari

# Funzione che data una stringa restituisce il 
# suo carattere piu' frequente
def carfreq(s):
    # costruisco dizionario che conta le occorrenze di ogni carattere
    d = {}
    for c in s:
        if c in d:
            d[c] = d[c] + 1  # carattere gia' incontrato
        else:
            d[c] = 1         # prima occorrenza di c
    # cerco il carattere piu' freq
    car = ""
    volte = -1
    for k in d:    # a = list(g.items())scorre tutte le chiavi del dizionario 
        if d[k]> volte:  # se trova un carattere piu' frequente di car
            volte = d[k] # aggiorna car e volte 
            car = k
    return car

# restituisce la lista delle parole piu' frequenti di un file
def parolefreq(s):
    assert isinstance(s,str)
    f = open(s)
    d = {}
    for linea in f:
        for p in linea.split():
            if p in d:      # p era gia' nel dizonario
                d[p] += 1
            else:
                d[p] = 1
    f.close()
    # costruisco elenco parole piu' frequente
    parole = []
    volte = 0
    for p in d:
        if d[p] > volte:
            parole = [p]
            volte = d[p]
        elif d[p]==volte:
            parole += [p]
    # restituisce le parole piu' frequenti ordinate lessicograficamente        
    return sorted(parole)

# =============================================
# funzioni che utilizzano il file seriA.txt

# dato un elenco di partite con i risultati
# restituisce la squadra che ha segnato di piu'
def attacco_migliore(partite):
    g = {}  # dizionario che associa ad ogni squadr i goal segnati
    f= open(partite)
    for linea in f:
        if len(linea)>3:  # considera solo linee non vuote
            sq0, gol0, sq1, gol1 = spezza_partita(linea)
            g = aggiorna_gol_segnati(g,sq0,gol0)
            g = aggiorna_gol_segnati(g,sq1,gol1)
    f.close()
    # a questo per ogni squadra in g abbiamo i gol fatti
    # costruisco la lista con le coppie (squadra,gol)
    a = list(g.items())
    # ordino per gol segnati decrescenti
    b = sorted(a,key=secondo,reverse=True)
    # restituisco il nome della squadra che segnato di piu' 
    return b[0][0]

# aggiorna il numero di gol di sq nel dizionario golsegnati
def aggiorna_gol_segnati(golsegnati,sq,gol):
    if sq in golsegnati:
        golsegnati[sq] += gol
    else:
       golsegnati[sq] = gol
    return golsegnati


# dato un elenco di partite con i risultati restituisce
# il dizionario contenente la classifica risultante
def classifica(partite):
    punti = {}  # dizionario che associa ad ogni squadr i goal segnati
    f= open(partite)
    for linea in f:
        if len(linea)>3:  # considera solo linee non vuote
            sq0, gol0, sq1, gol1 = spezza_partita(linea)
            if gol0>gol1:
                # dai tre punti a sq0
                punti = aggiorna_classifica(punti,sq0,3)
                punti = aggiorna_classifica(punti,sq1,0)
            elif gol0<gol1:
                # dai tre punti a sq1
                punti = aggiorna_classifica(punti,sq1,3)
                punti = aggiorna_classifica(punti,sq0,0)
            else:
                # dai un punto a sq0 e sq1
                punti = aggiorna_classifica(punti,sq0,1)
                punti = aggiorna_classifica(punti,sq1,1)
    f.close()
    # a questo per ogni squadra abbiamo i punti
    return punti

# aggiorna il punteggio di sq nel dizionario c
def aggiorna_classifica(c,sq,punt):
    if sq in c:
        c[sq] += punt
    else:
        c[sq] = punt
    return c

# funzione usata per dividere un linea del file dei risultati
# nelle sue quattro componenti (nomi delle squadre e punteggi)
def spezza_partita(linea):
    a = linea.split()
    gol = a[0].split("-")
    squadre = a[1].split("-")
    return squadre[0], int(gol[0]), squadre[1], int(gol[1])

def attacco_migliore(partite):
    g = {}
    f=open(partite)
    for linea in f:
        if len(linea)>3:
            a = linea.split()
            gol = a[0].split("-")  #a[0] 3-0 a[1] Lazio-Chievo
            squadre = a[1].split("-")#con le parentesi tolgo il carattere "-")
            if squadre[0] in g:
                g[squadre[0]] += int(gol[0])
            else:
                g[squadre[0]] = int(gol[0])
            if squadre[1] in g:
                g[squadre[1]] += int(gol[1])
            else:
                g[squadre[1]] = int(gol[1])
    f.close()
    return g


#______________________________________________________________________________


def spezza_partita(linea):
     a = linea.split()
     gol = a[0].split("-")  #a[0] 3-0 diventa 3,0
     squadre = a[1].split("-")
     return squadre[0], int(gol[0]), squadre[1], int(gol[1])

#>>> spezza_partita("2-1 Verona-Milan")
#('Verona', 2, 'Milan', 1)


def attacco_migliore2(partite):
    g = {}
    f=open(partite)
    for linea in f:
        if len(linea)>3:   #considera solo linee non vuote
            sq0, gol0, sq1, gol1 = spezza_partita(linea)
            g = aggiorna_gol_segnati(g,sq0,gol0)
            g = aggiorna_gol_segnati(g,sq1,gol1)       
    f.close()
    return g


def aggiorna_gol_segnati(golsegnati,sq,gol):  #DA SAPERE PER L'ESONERO
    if sq in golsegnati:
        golsegnati[sq] += gol
    else:
        golsegnati[sq] = gol
    return golsegnati











    

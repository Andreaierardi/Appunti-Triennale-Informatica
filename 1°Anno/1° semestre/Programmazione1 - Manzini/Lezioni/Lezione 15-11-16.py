"""
>>> a = [5,7,2,-6]
>>> b=a
>>> b
[5, 7, 2, -6]

b[0]=40
>>> b
[40, 7, 2, -6]
>>> a
[40, 7, 2, -6]

>>> c = a[:]
>>> c

[40, 7, 2, -6]
>>> a[0]=8
>>> a
[8, 7, 2, -6]

>>> sorted(c)
[-6, 2, 7, 40]
"""#nuovo array con elementi di c ordinati

"""
>>> c.sort()
>>> c
[-6, 2, 7, 40]
"""#ordina elementi di c

#se ordino un array che punta ad una certa parte di memoria, allora anche il secondo
#viene ordinato

"""
>>> aord= sorted(a)
>>> aord
[-6, 2, 7, 8]
>>> a
[8, 7, 2, -6]


sorted(a,reverse=True)
[8, 7, 2, -6]

a = ["ciao","mio","amore"]
>>> sorted(a)
['amore', 'ciao', 'mio']
""" #ordine lessografico per le stringhe

"""
>>> a=["ciao","mio","amore","abate","zorro","abaco"]
>>> sorted(a)
['abaco', 'abate', 'amore', 'ciao', 'mio', 'zorro']
>>> sorted(a,key=len)
['mio', 'ciao', 'amore', 'abate', 'zorro', 'abaco']
""" #con key determino l'ordine, in questo caso la lunghezza

    #POSSO ANCHE UTILIZZARE UNA FUNZIONE MIA NEL KEY
#            |
#            |
#            |
#            |
#            V
def secondo(x):
    return x[1]

"""
v = [ [2,3], [4,0], [5,-1] , [6,2]]
sorted(v,key=secondo)
[[5, -1], [4, 0], [6, 2], [2, 3]]
"""
#vede la seconda componente delle coppie e li ordina

"""
sorted(v,key=sum)
[[4, 0], [5, -1], [2, 3], [6, 2]]

sum([2,3,9])
14
>>> 
"""
#fa la somma di ogni coppia e li mette in ordine


"""
>>> sorted(v,key=min)
[[5, -1], [4, 0], [2, 3], [6, 2]]
"""

#------------------------------------------------------
                #DIZIONARI IN PYTHON

"""
d={}
>>> d["juve"] = 10
>>> d
{'juve': 10}

>>>d["roma"]=8
>>> d
{'roma': 8, 'juve': 10}
""" #associo alla chiave juve il valore 10 e alla chiave roma il valore 8
"""
>>> d["juve"]
10
>>> d["napoli"] = 8
>>> d
{'roma': 8, 'napoli': 8, 'juve': 10}
>>> d["napoli"] = 9
>>> d
{'roma': 8, 'napoli': 9, 'juve': 10}
"""# ci possono essere stessi valori a due chiavi differenti ma non due chiavi con
   # lo stesso nome

"""
>>> d[33]="booo"
>>> d
{'roma': 8, 'napoli': 9, 'juve': 10, 33: 'booo'}
""" #posso anche associare un numero ad una chiave stringa


#FUNZIONE CHE DATA UNA STRINGA VOGLIO OTTENERE IL CARATTERE PIU' FREQUENTE

def carfreq(s):
    #costruisco dizionario che conta le occorrenze
    d = {}
    
    for c in s:
        """d[c] = d[c] + 1"""#alla chiave c assegno il valore aumentato di 1
                             #MA NON POSSO
        if c in d:
            d[c] = d[c] + 1
        else:
            d[c] = 1 #se lo vedo per la prima volta associo il valore 1
            #print("Parziale: ",d)
            
    #cerco il carattere più frequente
    car = ""
    volte = -1
    for k in d:
        if d[k]> volte:
            volte = d[k]
            car = k
    return k


# cerca parola più frequente in un file

def parolafreq(s):
    assert isinstance(s,str)
    f = open(s)
    d = {}
    for linea in f:
        for p in linea.split():  #p assume ogni volta stringhe diverse
            if p in d:       #p era già nel dizionario
                d[p] += 1 
            else:           #p parola nuova
                d[p] = 1   
    f.close()
    parole = []
    volte = 0
    for p in d:
        if d[p] > volte:
            parole = [p]
            volte = d[p]
        elif d[p]==volte:
            parole += [p]
    return  sorted(parole)

"""
>>> a = "3-0 Lazio-Chievo"
>>> linea=a
>>> a=linea.split()
>>> a
['3-0', 'Lazio-Chievo']
>>> a[0]
'3-0'
>>> a[1]
'Lazio-Chievo'
>>> a[0].split("-")
['3', '0']
>>> a[1].split("-")
['Lazio', 'Chievo']
"""

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
    a = list(g.items())
    b = sorted(a,key=secondo,reverse=True)
    return b[0][0]  #restituisce l'elemento 0 di b[0] quindi la squadra di calcio


def aggiorna_gol_segnati(golsegnati,sq,gol):  #DA SAPERE PER L'ESONERO
    if sq in golsegnati:
        golsegnati[sq] += gol
    else:
        golsegnati[sq] = gol
    return golsegnati
                                    
#PER UTILIZZARE SORT DEVO TRASFORMARE IL DIZIONARIO IN UNA LISTA 
"""
>>> g=attacco_migliore2("seriea.txt")
>>> g
{'Milan': 3, 'Fiorentina': 6, 'Napoli': 6, 'Catania': 0, 'Roma': 6, 'Genoa': 2, 'Sampdoria': 2, 'Chievo': 2, 'Lazio': 4, 'Verona': 2, 'Juventus': 5, 'Cagliari': 4, 'Atalanta': 1, 'Parma': 2, 'Sassuolo': 1, 'Udinese': 3, 'Veron': 0, 'Inter': 4, 'Bologna': 2, 'Livorno': 6}
>>> a = list(g.items())
>>> a
[('Milan', 3), ('Fiorentina', 6), ('Napoli', 6), ('Catania', 0), ('Roma', 6), ('Genoa', 2), ('Sampdoria', 2), ('Chievo', 2), ('Lazio', 4), ('Verona', 2), ('Juventus', 5), ('Cagliari', 4), ('Atalanta', 1), ('Parma', 2), ('Sassuolo', 1), ('Udinese', 3), ('Veron', 0), ('Inter', 4), ('Bologna', 2), ('Livorno', 6)]

>>> secondo(('Roma',25))
25
>>> b =sorted(a,key=secondo)
>>> b
[('Catania', 0), ('Veron', 0), ('Sassuolo', 1), ('Atalanta', 1), ('Bologna', 2), ('Genoa', 2), ('Chievo', 2), ('Verona', 2), ('Parma', 2), ('Sampdoria', 2), ('Udinese', 3), ('Milan', 3), ('Lazio', 4), ('Inter', 4), ('Cagliari', 4), ('Juventus', 5), ('Roma', 6), ('Fiorentina', 6), ('Napoli', 6), ('Livorno', 6)]

>>>b =sorted(a,key=secondo,reverse=True)
>>> b
[('Roma', 6), ('Fiorentina', 6), ('Napoli', 6), ('Livorno', 6), ('Juventus', 5), ('Lazio', 4), ('Inter', 4), ('Cagliari', 4), ('Udinese', 3), ('Milan', 3), ('Bologna', 2), ('Genoa', 2), ('Chievo', 2), ('Verona', 2), ('Parma', 2), ('Sampdoria', 2), ('Sassuolo', 1), ('Atalanta', 1), ('Catania', 0), ('Veron', 0)]

"""

def attacco_migliore3(partite):
    g = {}
    f=open(partite)
    for linea in f:
        if len(linea)>3:   #considera solo linee non vuote
            sq0, gol0, sq1, gol1 = spezza_partita(linea)
            g = aggiorna_gol_segnati(g,sq0,gol0)
            g = aggiorna_gol_segnati(g,sq1,gol1)       
    f.close()
    
    squadra= ""
    gol = -1
    for s in g:
        if g[s]>gol:
            squadra = s
            gol = g[s]
    return squadra    #ottengo la squadra che ha fatto più gol


def classifica(partite):
    punti = {}
    f=open(partite)
    for linea in f:
        if len(linea)>3:   #considera solo linee non vuote
            sq0, gol0, sq1, gol1 = spezza_partita(linea)
            if gol0>gol1:
                # dai tre punti a sq0
                punti = aggiorna_classifica(punti,sq0,3)
                punti = aggiorna_classifica(punti,sq1,0) #in questo modo se squadra perde
                                                         #non da punti ma la mette in classifica
            elif gol0<gol1:
                #dai tre punti a sq1
                punti = aggiorna_classifica(punti,sq1,3)
                punti = aggiorna_classifica(punti,sq0,0)
            else:
                #dai un punto a sq0 e sq1
                 punti = aggiorna_classifica(punti,sq0,1)
                 punti = aggiorna_classifica(punti,sq1,1)
    f.close()
    return punti

def aggiorna_classifica(c,sq,punt):
    if sq in c:
        c[sq] += punt
    else:
        c[sq] = punt
    return c










def lol():
     l=[]
     a=[('sukia', 2), ('ciao', 1)]
     for i in range(len(a)):
            for j in range(len(a[i])):
                   l=l+[a[i][j]]
                
     return l



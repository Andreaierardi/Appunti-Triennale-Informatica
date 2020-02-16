#Ho una lista e voglio ottenerne una nuova con gli elementi
#della prima raddoppiatti

def raddoppia(lis):
    ris=[]
    for i in range(0,len(lis)):
        ris=ris+[lis[i]]*2   #oppure ris += [lis[i], lis[i]]
    return ris

#raddoppio di una stringa

def raddoppia_s(s):
    ris= ""
    for i in range(0,len(s)):
        ris +=s[i]*2
    return ris

#con ciclo FOR differente

def raddoppia2(lis):
    ris=[]
    for x in lis:   #x scorre tutti gli elementi della lista
        ris +=[x]*2
    return ris

def raddoppia_s2(s):
    ris=""
    for c in s:
        ris += 2*c
    return ris 
        
#FORMA SENZA SENSO
    for x in lis:
        a=lis[x]   #in questo caso abbiamo già specificato x in lis 
        
#==================================================================
#data una lista di interi tra 1 e 100
#dire qual è il più frequente

def frequenza(lis):
    piufreq= None
    volte=0
    for x in lis:
        #conto quante volte x appare in lis
        quantex= 0
        for y in lis:
            if y==x:
                quantex += 1
        if quantex>volte:
            piufreq= x
            volte= quantex
    return piufreq

"""
x è 2,3,4,5
y assumerà i valori 2,3,4,5 e finisce il ciclo y
dopodiche il ciclo sulla x aumenta fino a 3 e ripercorrre il ciclo
"""

#per renderla più frequente ulilizziamo un array di 101 lemneti che si
#chiama CONTATORE. Il contatore se compare 2 volte in lis è 2

def frequente2(lis):

    contatori =101*[0]
    for x in lis:
        assert x>=0 and x<=100, "Valore fuori range"
        contatori[x] +=1
    piufreq = None
    volte = 0
    for i in contatori:
        if i >= volte:
            volte = x
            piufreq = i
    return piufreq
    
"""
ci dice ogni quanto compare un numero

"""
#=================================================================

#APRIRE FILE DI TESTO ESTERNI

def visualizza(nome):
    assert isinstance(nome,str),"input deve essere nome"
    print("======= Ora cerco di aprire il file ",nome)
    f = open(nome) 
    for s in f:
        print(s,end="")
    print("======= Fine lettura")
    close(f) 
    return 



























    

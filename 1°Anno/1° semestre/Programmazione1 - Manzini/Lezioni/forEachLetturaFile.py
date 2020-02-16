# ===================================
# versione alternativa del ciclo for

# funzioni che eseguono il raddoppio degli elementi di
# una lista e di stringa con ciclo for tradizionale 
def raddoppia(lis):
    ris = []
    for i in range(0,len(lis)):
        ris += [ lis[i], lis[i] ]
    return ris

def radd(lis):
    ris=[]
    for i in range(0,len(lis)):
        ris+=[lis[i]]*2
    return ris

def raddoppia_stringa(s):
    ris = ""
    for i in range(0,len(s)):
        ris += 2*s[i]
    return ris

# come sopra ma usando la nuova versione del
# ciclo for senza il range. Notare la maggiore semplicita' 
def raddoppia2(lis):
    ris = []
    for x in lis:
        ris += [x , x]
    return ris

def raddoppia_stringa2(s):
    ris = ""
    for c in s:
        ris += 2*c
    return ris


# =========================================
# Esercizio.
# Data una lista di interi tra 1 e 100
# dire qual e' il piu' frequente
# Ad esempio con input 
#   [3,6,7,3,10,7,1,10,3,7,7]
# L'output deve essere 7

# prima soluzione: fuziona ma a causa dei
# due cicli for annidati e' inefficinte
def frequente(lis):
    # inizializza piufreq e volte 
    piufreq = None
    volte = 0
    # considero dutti gli elementi di lis
    for x in lis:
        # conto quante volte x appare in lis
        quantex= 0
        for y in lis:
            if y==x:
                quantex += 1
        # verifico se x e' piu' frequente di piufreq         
        if quantex>volte:  #[3,6,7,3,10,7,1,10,3,7,7]
            piufreq = x
            volte = quantex
    # restituisco elemento piu' frequente        
    return piufreq

# seconda soluzione: usa  lista contatori[]
# per contare le occorrenze di ogni elemento
def frequente2(lis):
    # inizializza contatori con 101 zeri
    contatori = 101*[0]
    # calcola contatori
    for x in lis:
        assert x>=0 and x<= 100, "Valore fuori range"
        contatori[x] += 1
    # ora ho contato quante volte appare ogni valore i
    # ricerca piu' frequente guardando solo contatori[]
    piufreq = None
    volte = 0
    for i  in range(0,len(contatori)):
        x = contatori[i]
        if x > volte:
            volte = x
            piufreq = i
    return piufreq

# ==============================================
# Esempio lettura di file di testo
# visualizza sulla schermo il contenuto di un file di testo
# una linea alla volta
def visualizza(nome):
    assert isinstance(nome,str),"input deve essere nome di file"
    print("==== Ora cerco di aprire il file", nome)
    f = open(nome) # di defualt il file viene aperto il lettura
    for s in f:
        print(s,end="") # end="" impedisce che venga stampato un ulteriore \n
    print("==== Fine lettura")
    f.close()  # chiudo il file 
    return


    
# ======================================================
# Esercizio 1
# Modificare la funzione frequente2 in modo che restituisca
# la lista degli elementi piu' frequenti. Ad esempio
#   frequente2([3,6,7,3,10,7,1,10,3,7,7]) -> [7]
#   frequente2([3,6,7,3,10,7,1,10,3,7,3,7]) -> [3,7]

def frequente3(lis):
    ris=[]
    contatore=0
    r=0
    for i in range(len(lis)):
        for x in lis:
            if x>lis[i]:
                print(x)
            
        

# ======================================================
# Esercizio 2
# Scrivere una funzione dimensione() che dato il nome di un file
# di testo restituisce la sua dimensione, cioe' il numero di
# byte in esso contenuti.
# Suggerimento: modificare visualizza() in modo che calcoli
# la somma delle lunghezze delel stringhe lette dal file


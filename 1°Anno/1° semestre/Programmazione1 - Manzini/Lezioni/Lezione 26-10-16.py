#scringa di 10 elementi va da 0 a 9 per quello va out of range
def scorri(s):
    for i in range(0,len(s)):
        print(s[i])


#WHILE è molto più flessibile rispetto al for

def chiedipassword():
    pwd=""              #definisco la variabile per evitare errori
    while len(pwd)<8:
        pwd=input("inserisci password di almeno 8 caratteri")
    return pwd

#per interrompere il ciclo con break(ciclo dowhile di altri linguaggi)
def chiedipassword2():
    while True:
        pwd=input("Inserisci password di almeno 8 caratteri")
        if len(pwd)>=8:
            break
    return pwd

#________________________________________________________________________

#il numero 10001simo
def primo(n):
    if n<2:
        return False
    elif n%2==0:
        #n pari
        return True
    else:
        #n dispari >= 3
        for i in range(3,n,2):  #con terzo numero determino la frequenza(step) 
            if n%i==0:
                return False
            if i*i>n:           #se i> rad n [con radice darebbe
                                #problemi quindi elevo]
                break          #ferma il ciclo for 
        return True

def primo10001():
    conta=0
    i=1
    while conta<10001:
        i=i+1
        if primo(i):
            conta+=1
    return i

#con for definiamo subito il numero di istruzione da compiere e si
#si interrompe con un BREAK
"""
list(range(0,10)
==>[0,1,2,3,4,5,6,7,8,9]

list(range(0,10,3))
==>[0,3,6,9]
     
list(range(7))
==>[0,1,2,3,4,5,6]
"""

#1) scrivere funzione leggi_stringhe() che dato un intero positivo n legge
#stringhe da tastiera (con il comando input) fino a quando non viene introdotta
#una di lunghezza esattamente n.

def leggi_stringhe(n):
    assert isinstance(n,int),"Il parametro deve essere un intero" 
        #poniamo n che sia un intero
    assert n>=0,"Il parametro deve essere positivo"
        #non esiste una stringa negativa, quindi definiamo un limite

    contatore=0
    while True:
        ciccio=input("Inserisci una stringa")
        contatore += 1
        if len(ciccio)==n:
            break
    return contatore

#_________________________________________________________________________

#LE LISTE (o array) --> variabili che contengono tanti oggetti messi insieme
"""
x=[2, 0, 7, 6]
==>[2, 0, 7, 6]

len(x)
==>4  #numero di elementi della lista

x[0]
==>2

x[1]
==>0

x[2]
==>7

x[3]
==>6

x[4]
==>error

x[-1]
==>6

y=[2,3,"ciao",True]   #posso metterci vari elementi
==>2,3,'ciao,True

x[2]=11
x
==>[2,0,11,6]   #posso sostituire oggetto della lista

c="ciao"
c[2]="e"
==> ERROR

z= [4,2]
z+x
==>[4,2,2,0,7,6]
"""

def crea_lista(a,b):
    lista=[]    #creo una lista vuota con cui posso lavorare 
    for i in range(a,b+1):
        lista=lista+[i]
    return lista


#OPERAZIONE BOOLEANA
"""
lis=crea_lista(3,10)

2 in lis
==>False

5 in lis
==>True

5 in 10
==>ERROR
"""

lis=crea_lista(3,10)
def somma_lista(lis):
    somma=0
    for i in range(0,len(lis)):
        somma=somma+lis[i]
    return


def max_lista(lis):
    assert isinstance(lis,list),"input deve essere una lista non vuota"
    assert len(lis)>0,"Input deve essere una lista non vuota"
    massimo=lis[0]       #se mettessi massimo=0 non si potrebbe utlizzare
                         #per liste con soli numeri negativi 
    for i in range(1,len(lis)):
        if lis[i]>massimo:
            massimo=lis[i]
    return massimo
    
















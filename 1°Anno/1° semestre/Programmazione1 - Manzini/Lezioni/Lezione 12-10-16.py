#RESTITUISCE IL MINIMO TRA DUE NUMERI

def minimo(a,b):
    if (a<b):
        print("Sono dentro l'if")
        return a        #con print esegue anche le istruzioni fuori dall'IF
    print("Io invece sono fuori")
    return b

#______________________________________________________________________________


#RESTITUISCE IL MINIMO TRA TRE VALORI

#mio esempio
def min3(a,b,c):
    if (a<b)and(a<c):
        return a
    if (b<a)and(b<c):
        return b
    else:
        return c

#esempio 1° del prof più complicato
def min3prof(a,b,c):
    if a<b:
        if a<c:
            return a
        return c
    if b<c:
        return b
    return c

#esempio 2° del prof con più funzioni ma più semplice
def min3bis(a,b,c):
    x=minimo(a,b)
    return minimo(x,c) 

#esempio 3° del prof 
def min3ter(a,b,c):
    return minimo(minimo(a,b),c)

#IF COMPLETO
def ifcompleto(a,b):
    if a<b:
        print("Il test è vero")
    else:
        print("Il test è falso")
    print("sono fuori dall'IF")
    return 

#___________________________________________________________________________

#FUNZIONE CHE SCRIVE I MUTIPLI DI 3 TRA A E B

def multipli3(a,b):
    for i in range(a,b+1):
        if i%3==0:
            print(i)

#FUNZIONE CHE CONTA QUANTI SONO I MULTIPLI DI 3 TRA A E B

def n_multipli3(a,b):
    conta=0
    for i in range(a,b+1):
        if i%3==0:
            conta=conta+1
    return conta 

#VOGLIO CONTARE I DIVISORI DI UN NUMERO

def divisori(n):
    conta=0
    for i in range(1,n+1):
        if n%i==0:
            conta+=1  #sarebbe come dire conta=conta+1
    return conta

#TEST DI PRIMALITA'

def primi(n):
    return divisori(n)==2 #se i divisori sono 2 il numero è primo

#CONTARE NUMERI PRIMI <=N

def primimin(n):
    conta=0
    for i in range(1,n+1):
        if primi(i)==True:
            conta+=1
    return conta

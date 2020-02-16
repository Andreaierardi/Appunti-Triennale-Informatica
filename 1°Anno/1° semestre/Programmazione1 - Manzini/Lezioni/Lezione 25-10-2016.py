#operazioni di secondo grado con elif
# ax'2+bx+c=0
# Delta=b'2-4ac
# 3 casi con discriminante <0 , >0 , =0

import math                   #importo la libreria math

def radici(a,b,c):
    assert a!=0 'Il coef. di x'2 deve essere #a deve essere diversa da 0(il programma funziona se soddisfatta
    delta=b**2-4*a*c
    if delta<0:
        return None           #delta negativo, radici complesse
    elif delta==0:
        risultato=(-b)/(2*a)  #delta nullo, una sola radice
        return risultato
    else:
        r=math.sqrt(delta)    #libreria math
        x1=(-b+r)/(2*a)
        x2=(-b-r)/(2*a) 
        soluzioni=x1,x2       #array di due elementi
        return soluzioni
        
#__________________________________________________________________________

#project euler.net esercitazioni python
    
#Multiples of 3 and 5
#Problem 1
#If we list all the natural numbers below 10 that are multiples
#of 3 or 5, we get 3, 5, 6 and 9.The sum of these multiples is 23.

#Find the sum of all the multiples of 3 or 5 below 1000.

def multipli():
    somma=0
    for i in range(1,1000):
        if i%3==0 or i%5==0:
            somma+=i
    return somma

#oppure
def multipli2():
    somma=0
    for i in range(1,1000):
        if i%3==0:
            somma=somma+i
        elif i%5==0:
            somma=somma+i
    return somma

#___________________________________________________________________________

#FUNZIONE CHE RESTITUISCE TRUE SE n E' PRIMO, FALSE ALTRIMENTI NON SIA PRIMO

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


def conto_rovescia():
    for i in range(10,1,-1):  #contatore 1 va avanti invece che indietro
        print(i)
    return

#problema 10 project euler
#somma di numeri primi sotto 2milioni

def sommap():
    somma=0
    for i in range(1,2000000):
        if primo(i):
            somma+=i
    return somma


isinstance(n,int)
prende il valore e vuole sapere il tipo della variabile
Questo oggetto è True se n è un intero e false se n non è intero

s="ciao"
len(s)--> lunghezza stringa

s[0]--> primo carattere
s[1]--> secondo carattere


s[-1]--> ultimo carattere
s[-2]--> penultimo carattere


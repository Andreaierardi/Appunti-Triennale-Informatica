"""
a=oggi è una bella giornata'

a
==> 'oggi è una bella giornata'

a[0]
==> 'o'

a[1]
==> 'g'

a[2:5]
==> 'gi '

a[1:4]
==> 'ggi'

a[0:4]
==>'oggi'

a[2:12]
==>'gi è una "

a[2:12:2]
==> 'g 'ua'

a[12:2:-1]
==> "b anu 'e i"

"""

#a[::-1] modo per ottenere il reverse
#==> "atanroig alleb anu 'e iggo"

#LO STESSO VALE ANCHE PER LE LISTE
"""
b= [1,2,3,4,10,-7]

b[:-1]
==> [1,3,4,10,-7]

b[1:]
==>[3,4,10,-7,-11]

b[:]
==>[1,3,4,10,-7,11]

b
==> [1,3,4,10,-7,11]

x=5
y=x
x=3
y
==>5

b=[1,3,4,10,-7,11]
a=b
a
==>[1,3,4,10,-7,11]
b
==>(1,3,4,10,-7,11]
b[3]=5
b
==>[,3,4,5,-7.11]
a
==>[1,3,4,5,-7,11] 
"""
#a e b puntano allo stesso oggetto quindi se cambio b cambio anche a. (PUNTATORI)
#QUINDI  pongo a = b[:] così creo una copia di b in a

"""
a[0]=80
a
==>[80,3,4,5,-7,11]

b
==>[1,3,4,5,-7,11]
"""
#____________________________________________________________________________

#LIBRERIA OS

import os
os.getcwd()
'/home/giovanni'

#CREAMO UN PROGRAMMA CHE PRENDE IN INPUT IL NOME DI UN FILE
#E NE FA UNA COPIA

def copia(nome):
          assert isinstance(nome,str),"Input deve essere nome file"
          f = open(nome)
          g = open(nome + ".copia", "w") #vogliamo aprire il file in scrittura
                                         #e vogliamo che finisca con .copia

          for s in f:  #legge tutte le righe del file f
              print(s[:-1],file=g)  #stampa caratteri di f dentro g
                                    #oppure (s,end='',file=g) per togliere gli spazi
          g.close()
          f.close()

#s[:-1] prende la stringa tranne ultimo carattere. Col print si aggiunge un
#INVIO alla fine in questo modo non si va a capo


def copia(nome):
          assert isinstance(nome,str),"Input deve essere nome file"
          f = open(nome)
          g = open(nome + ".copia", "w") #vogliamo aprire il file in scrittura
                                         #e vogliamo che finisca con .copia

          for s in f:  #legge tutte le righe del file f
              #print(s[:-1],file=g)  #stampa caratteri di f dentro g
              g.write(s) #prende come agomento s e lo stampa sul file g
          g.close()
          f.close()
          return

def copiaconlungh(nome):
    assert isinstance(nome,str),"input deve essere nome file"
    f = open(nome)
    g = open(nome + ".copia","w")
    for s in f:
        print(s[:-1],len(s),sep=" ---> ",file=g) #stampo s tutte le volte e la sua lunghezza
        #con sep utilizzo dei separatori che preferisco
        #altra possibilità : g.write(s)
    g.close()
    f.close()
    return 

#FUNZIONE SPLIT--> tramuta stringa in lista di parole senza spazi
"""

a= "ciao 6 bello \n\n"
a.split()
==>['ciao','6','bello']

"""

#VOGLIO CONTARE QUANTE PAROLE CI SONO IN UN FILE

def contaParola(nome):
    assert isinstance(nome,str),"input deve essere nome file"
    f = open(nome)
    conta= 0
    for s in f:
        conta += len(s.split())
    f.close()
    return conta

#VOGLIO CONTARE QUANTE PAROLE UNICHE CI SONO NEL MIO FILE

def contauniche(nome):
    assert isinstance(nome,str),"input deve essere nome file"
    f = open(nome)
    parole= []
    conta= 0
    for s in f:
        lista=s.split()   #scorro una alla volta le parole di quella linea
        for p in lista:
            if not (p in parole):
                conta += 1
                parole += [p]
    f.close()
    return parole

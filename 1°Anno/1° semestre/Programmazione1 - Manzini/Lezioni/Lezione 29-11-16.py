#! /usr/bin/env python3
""" specifico che il file va eseguito con python3"""

import sys

for i in sys.argv:
    print (i)

print("--- finito ---")



"""
python Lezione29-11-16.py uno due tre lezione.py

less mini.py

"""

def fatt(n):
    f = 1
    for i in range(n):
        f *= i
    return f

if len(sys.argv) != 2:
    print ("Uso: ", sys.argv[0], "numero")
else:
    print (fatt(int(sys.argv[1])))

#importa libreria sys
#vede funzione fattoriale
#se la lunghezza di quella lista (composta da nome del programma
#più qualsiasi stringa)
#se lunghezza è ==2 
#sennò stampa il fattoriale dell'elemento inserito

"""
./python3 Lezione 29-11-16.py 100
scrive fattoriale di 100
""" 

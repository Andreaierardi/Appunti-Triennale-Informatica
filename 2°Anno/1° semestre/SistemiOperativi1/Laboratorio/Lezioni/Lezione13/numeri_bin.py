#! /usr/bin/env python3

# crea un file di n interi positivi scritti in formato binario (32 bit)
# e stampa la loro somma
# Per visualizzare il contenuto del file dalla linea di comando
# scrivere: od -i nomefile

import random
import sys
import struct

def main(nomefile,n):
  # main file
  f = open(nomefile,"wb")
  somma = 0
  # crea interi random
  for i in range( n ):
    x = random.randint(0, 1000)
    somma += x
    f.write(struct.pack("<i",x))
  f.close();
  print("Somma interi file %s: %d" %(nomefile,somma))

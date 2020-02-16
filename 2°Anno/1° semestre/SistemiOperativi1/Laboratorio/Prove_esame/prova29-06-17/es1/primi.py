#!/usr/bin/env python3
import sys

# dato un intero n>0 restituisce True se n e' primo
# False altrimenti
def primo( n ):
    assert n>0, "L'input deve essere positivo"
    if n==1:
        return False
    if n==2:
        return True
    if n%2 == 0:
        return False
    assert n>=3 and n%2==1, "C'e' qualcosa che non funziona"
    for i in range(3,n//2,2):
        if n%i==0:
            #print ("Ho trovato", i, "che divide", n)
            return False
        if i*i > n:
            break    
    return True

# crea file nome con i primi dispari fino a m escluso
def main(nome,m):
  with open(nome,"w") as f:
    for i in range (3,m,2):
      if primo(i):
        print(i,file=f)
  return

if len(sys.argv)!=3:
  print("Uso:\n\t %s nomefile m" % sys.argv[0])
else:
  main(sys.argv[1], int(sys.argv[2]))

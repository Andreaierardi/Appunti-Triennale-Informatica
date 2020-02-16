#! /usr/bin/env python3
import random
import sys

def main(n,nomefile,pot):
  # main file
  f = open(nomefile,"w");
  fout = []
  # file di potenze
  for i in range(pot):
    fout.append(open(nomefile+".sol."+str(i+1),"w"))
  # crea interi random   
  for i in range(0,n):
    x = random.randint(-20, 20)
    print(x,file=f)
    for i in range(pot):
      print(x**(i+1),file=fout[i])
  f.close();
  for f in fout:
    f.close()

if len(sys.argv)!=4:
  print("Uso:\n\t %s numero_interi file potenze" % sys.argv[0])
else:
  main(int(sys.argv[1]), sys.argv[2], int(sys.argv[3]))

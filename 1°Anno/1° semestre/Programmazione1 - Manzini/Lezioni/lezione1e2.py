# Caricare questo file in IDLE3
# Eseguire le funzioni saluta() e risaluta() e osservare
# che il comportamento e' quello visto a lezione
# Provare ad eseguire raddoppia() e osservare che causa un errore
# al momento dell'esecuzione
# Correggere l'errore e eseguire raddoppia e riraddoppia
# cercando di prevedere in anticipo quale sara' l'output restituito.

# Se vi vengono dei dubbi o delle curiosita' fate modifiche e testate
# non potete fare danni permanenti con questo codice.


def saluta():
  m = input("Inserisci un nome ")
  print("Ciao", m)

def risaluta():
  m = "Clarabella"
  saluta()
  print("RiCiao", m)

# qui c'e' un errore da trovare e correggere 
def raddoppia():
  n = input("Inserisci un intero ")
  print("Il doppio di ", n, "e'", 2*n)

def riraddoppia():
  n = 12
  raddoppia()
  print("Il doppio di ", n, "e'", 2*n)
  

# questa istruzione e' fuori dalle def
# quindi viene eseguita al momento della lettura del programma
print("Letto tutto")













# ------ Uso delle funzioni

# esempio di funzione che chiede i dati con input
# e visualizza il risultato con print
# Comodo per noi ma non per comunicare con le altre funzioni
# NON USARE QUESTO STILE
def area_sbagliata():
    base = int(input("Inserisci base "))
    altezza = int(input("Inserisci altezza "))
    area = base * altezza
    print("L'area e' ", area)

# QUESTO E' LO STILE DA USARE
# funzione che prende i dati dai parametri
# e restituisce l'output con return
# La print serve solo per capire cosa succede
# durante l'esecuzione, dopo i primi test la si puo'
# eliminare e tutto funziona nello stesso modo
def area_rettangolo(base,altezza):
    area = base * altezza
    print("Area del rettangolo e'", area)
    return area

# uso area_rettangolo per calcolare base per altezza
# funziona grazie al fatto che area_rettangolo
# retiruisce il risultato con return  Se si limitasse
# a stamparlo con print non funzionerebbe.
def area_triangolo(base,alt):
    arearet = area_rettangolo(base,alt)
    print("Valore restituito da area_rettangolo",arearet)
    area = arearet/2
    return area


# ------ Introduzione al ciclo for

# esempio piu' semplice di ciclo for:
# stampa gli interi tra 1 e n
def conta_fino_a(n):
    print("Inizio")
    for i in range(1,n+1):  # n+1 perche' il ciclo si ferma al valore precedente
        print(i)
    print("Fine")
    return

# come prima ma invece di stampare i numeri
# tra 1 e n li sommiamo insieme
def somma_da_1_a_n(n):
     
     for i in range(1,n+1):
         print("i vale", i)
         somma = somma + i
         print("La somma ora vale", somma)
     print("Fine")
     return somma


# cambiando la somma in prodotto e il valore di
# partenza da 0 a 1 otteniamo la funzione fattoriale
#   n! = 1*2*3 ... * n
def fattoriale(n):
    fatt = 1
    for i in range(1,n+1):
         #print("i vale", i)
         fatt = fatt * i
         #print("il fattoriale ora vale", fatt)
    return fatt
    
    
# Esercizio:
# Scrivere una funzione numeri che dato l'intero n
# restituisce la stringa "1 2 3 4 ... n".
# Esempio:
#   numeri(3) -> "1 2 3"
#   numeri(10) -> "1 2 3 4 5 6 7 8 9 10"
# La stringa risultato deve essere restituita con 
# return NON stampata sullo schermo con print
# Ricordare che:
#  1) il + esegue la concatenazione fra stringhe
#  2) la funzione str converte un intero in stringa
#     str(4) -> "4"   str(15) -> "15"
#  3) Se scrivo s="" ho messo dentro la variabile s una
#     stringa vuota, cioe' che non contiene nessun carattere

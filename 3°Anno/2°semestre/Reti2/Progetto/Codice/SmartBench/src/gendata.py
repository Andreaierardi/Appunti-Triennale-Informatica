import random

def genBR(n):
    file = open("bracciale.xml2","w")
    file.write("<dati>")
    for i in range(n):
        rand = random.randint(100,120)
        rand2 = random.randint(60,100)
        stringa = " <data pressione= '" +str(rand)+"' /> \n <data frequenza='" +str(rand2) +"' /> "
        print(stringa)
        file.write(stringa)
    file.write("</dati>")
          
def genBL(n):
    print("<dati>")
    for i in range(n):
        print(" <data ripetizione= ' 1 ' /> ")
    print("</dati>")

def genP(n):
    print("<dati>")
    for i in range(n):
        rand = random.randint(10,100)
        print(" <data  peso= '" ,rand ,"' /> ")
    print("</dati>")

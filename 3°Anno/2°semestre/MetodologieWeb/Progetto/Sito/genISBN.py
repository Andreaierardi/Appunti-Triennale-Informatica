import random

def codice_isbn(n):
    for i in range(n):
        print(ninerand())

def rand():
    return random.randint(1, 9)

def ninerand():
    string = ""
    for i in range(9):
         string += str(rand())
    return string


def year(n):
    for i in range(n):
        print(anno_rand())

def anno_rand():
    m = random.randint(1,2)
    if(m==1):
        l= random.randint(20,99)
        return "19"+str(l)

    else:
        l = random.randint(0,19)
        if(len(str(l))==1):
            return "200"+str(l)
        else:
            return "20"+str(l)

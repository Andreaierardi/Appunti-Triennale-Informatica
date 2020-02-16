
#Trovo resto e quoto
def dividi(a,b):
    print("Mi preparo per la divisione...")
    if b==0:
        print("Non posso dividere per zero")
    else:
        print("Quoziente:",a//b)
        print("Resto:", a%b)
    print ("Finito!")

#classe di resto
def classe(a,n):
    for i in range(0,10*n+1):
        if (a-i)%n==0:
            print(i)

#Coppie soluzione equazione diofantea, r = range

def diofantea(a,b,c,r):
    d=mcd(a,b)
    if c%d==0:
        for i in range(-r,r+1):
            for j in range(-r,r+1):
                if (a*i+b*j)==c:
                    print(i,j)
        return "L'equazione ha soluzione"
    return "L'equazione non ha soluzioni"

#numero phi eulero
def phi(n):
    i=1
    conta=0
    while i<n:
        if (mcd_euclide(i,n)==1):
            conta+=1
            i+=1
        else:
            i+=1
    return conta


#trovo il massimo comune divisore tra numeri positivi (MCD)
def mcd(a,b):
    return max([i for i in range(1,a+1) if a%i==0 and b%i==0])

def mcd_euclide(a,b):
    if b==0:
        return a
    r = a%b
    return mcd_euclide(b,r)

#trovo il minimo comune multiplo tra due numeri positivi (mcm)
def mcm(a,b):
    return a*b//mcd(a,b)

#congruenze
def cong(a,b,n):
    return (a-b)%n==0

#soluzione ad un particolare sistema di due congruenze
def solp2(x,a,y,b):
    return [i for i in range(1,(a*b)) if i%a==x and i%b==y]

#soluzione sistema di 3 congruenze
def solp3(x,y,z,a,b,c):
    return [i for i in range(1,a*b*c) if i%a==x and i%b==y and i%c==z]

#FUNZIONE PIU' EFFICENTE PER VERFICARE NUMERO PRIMO

def primo(n):
    if n==2:
        return True
    if (pow(2,n-1,n))==1:
        return True
    if (pow(2,n-1,n))!=1:
        return False
    
#trovo numero primo2
def primo2(n):
    return n>1 and len([i for i in range(2,n) if n%i==0])==0

#funzione numero primo3
def Primo(n):
    if n==1:
        return False
    if n%2==0:
        if n==2:
            return True
        else:
            return False
    for i in range(3,1+n//2,2):
        if n%i==0:
            return False
    return True


#TROVO L'INVERSO MOLTIPLICATIVO DELLA CLASSE [A]MOD N

def inverso(a,n):
    if mcd(a,n)==1:
        return [i for i in range(1,n) if (a*i)%n==1]
    else:
        return "Non esiste un inverso moltiplicativo"

    

#RICAVA N DA UNA CONGRUENZA TIPO: N MOD A =C
def ml(c,a,m):
    lista=[]
    for i in range(1,m):
        if i%a==c:
            lista=lista+[i]
    print(lista)
    print()
    print("ci sono",len(lista),"elementi")

#ELEVAMENTO A POTENZA
def potenza(a,m):
    if m==0:
        return 1
    if m==1:
        return a
    if m%2==0:
        b= potenza(a,m//2)
        return a*b*b
    else:
        b = potenza(a,(m-1)//2)
        return a*b*b

#CACOLO ORDINE ELEMENTO DI Z*n
#SE NON DA RISULTATI L INPUT NON E' INVERTIBILE

def ordine(a,n):
    for i in range (1,n):
        if pow(a,i,n)==1:
            return i
        
#CONDIVISIONE DI SEGRETI
[i for i in range(0,30000) if 15332%33==i] #33 è il modulo
[i for i in range(0,30000) if 15332%31*32==i]  #15332 è la nostra pass
[i for i in range(0,30000) if i%33==20 and i%31*32==452]  #20 e 452 è il resto della congruenza

def condivisione(modulo,modulo2,chiave,r): #range  
    for i in range(0,r):
        if chiave%modulo==i:
            print("Il primo resto è: ",i)
            a=i
    for j in range(0,r):
        if chiave%modulo2==j:
            print("Il secondo resto è: ",j)
            b=j
    for e in range(1,r):
        if (e%modulo==a) and (e%modulo2==b):
            print("La chiave è:",e)
            if e == chiave:
                print("La chiave è corretta")
            else:
                print("La chiave non è corretta")
                break
    return 


        
            
            
            
#trovare c - x0 - y0 in una diofantea
#EUCLIDE ESTESO

def xgcd(b,n):          #ax+by=c
    x0, x1, y0, y1 =1,0,0,1
    while n != 0:
        q,b,n=b//n,n,b%n
        x0,x1=x1,x0-q*x1
        y0,y1=y1,y0-q*y1
    return b,x0,y0
            

#CALCOLA LOGARITMO DISCRETO
def log_disc(a,b,n):
    oa=ordine(a,n)
    if oa==None:
        return None
    for i in range(0,oa):
        if pow(a,i,n)==b:
            return [i,str(oa)+" modulo"]
    return None


#CIFRARIO DI CESARE
#ESEMPIO [CESARE(C) FOR C IN 'DO OR DO NOT.THE IS NO TRY']
def cesare(c):
    return(ord(c)*57+34)%281
#FUNZIONE DI DECODIFICA
def decesare(y):
    return chr((212*y+98)%281)


#MATRICE 2X2
def matrice2(x1,x2,y1,y2):
    determinante=x1*y2-x2*y1
    return determinante
    
#MATRICE 3X3
def matrice3(x1,x2,x3,y1,y2,y3,z1,z2,z3):
    determinante=x1*matrice2(y2,y3,z2,z3)-x2*matrice2(y1,y3,z1,z3)+x3*matrice2(y1,y2,z1,z2)
    return determinante
    
#MATRICE 4X4
def matrice4(x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4,w1,w2,w3,w4):
    determinante=x1*matrice3(y2,y3,y4,z2,z3,z4,w2,w3,w4)-x2*matrice3(y1,
    y3,y4,z1,z3,z4,w1,w3,w4)+x3*matrice3(y1,y2,y4,z1,z2,z4,w1,w2,w4)-x4*matrice3(y1,y2,y3,z1,z2,z3,w1,w2,w3)
    return determinante

#RISOLUZIONE SISTEMA A 3 INCOGNITE(trovare x,y,z)
def sistema(x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4):
    D=matrice3(x1,x2,x3,y1,y2,y3,z1,z2,z3)
    X=matrice3(x4,x2,x3,y4,y2,y3,z4,z2,z3)
    Y=matrice3(x1,x4,x3,y1,y4,y3,z1,z4,z3)
    Z=matrice3(x1,x2,x4,y1,y2,y4,z1,z2,z4)

    print("X e': ",X/D)
    print("Y e': ",Y/D)
    print("Z e': ",Z/D)

#RISOLUZIONE PROTOCOLLO RSA
def rsa(n,e):
    p=[i for i in range(2,int(pow(n,1/2))+1)if n%i==0]
    q=n//p[0]
    phi_n=(p[0]-1)*(q-1)
    d=xgcd(e,phi_n)
    print("p è : ",p[0],"\nq è : ",q,"\nphi n è  : ",phi_n)

    
    if d[1]<0:
        l=pow(d[1],1,phi_n)
        print("d è : ", l)
    if d[1]>0:
        print("d è: ",d[1])

#RADICI DI UN NUMERO IN Zn
def radici(a,n):
    result=0
    count=0
    
    for i in range(n):
        if (pow(i,2,n)==a):
            print(i)
            count= 1
    if (count==0):
            print("NON CI SONO RADICI")

#in input devi inserire un'unica matrice nella forma [[1,2,3],[4,5,6],[7,8,9]]
#se per sempio hai una matrice nella forma 1 2 3
#                                          4 5 6
#                                          7 8 9

def det(l):
    n=len(l)
    if (n>2):
        i=1
        t=0
        sum=0
        while t<=n-1:
            d={}
            t1=1
            while t1<=n-1:
                m=0
                d[t1]=[]
                while m<=n-1:
                    if (m==t):
                        u=0
                    else:
                        d[t1].append(l[t1][m])
                    m+=1
                t1+=1
            l1=[d[x] for x in d]
            sum=sum+i*(l[0][t])*(det(l1))
            i=i*(-1)
            t+=1
        return sum
    else:
        return (l[0][0]*l[1][1]-l[0][1]*l[1][0])

#---------------------------------------
# GAUSSS
def pprint(A):
    n = len(A)
    for i in range(0, n):
        line = ""
        for j in range(0, n+1):
            line += str(A[i][j]) + "\t"
            if j == n-1:
                line += "| "
        print(line)
    print("")


def gauss(A):
    n = len(A)

    for i in range(0, n):
        # Search for maximum in this column
        maxEl = abs(A[i][i])
        maxRow = i
        for k in range(i+1, n):
            if abs(A[k][i]) > maxEl:
                maxEl = abs(A[k][i])
                maxRow = k

        # Swap maximum row with current row (column by column)
        for k in range(i, n+1):
            tmp = A[maxRow][k]
            A[maxRow][k] = A[i][k]
            A[i][k] = tmp

        # Make all rows below this one 0 in current column
        for k in range(i+1, n):
            c = -A[k][i]/A[i][i]
            for j in range(i, n+1):
                if i == j:
                    A[k][j] = 0
                else:
                    A[k][j] += c * A[i][j]

    # Solve equation Ax=b for an upper triangular matrix A
    x = [0 for i in range(n)]
    for i in range(n-1, -1, -1):
        x[i] = A[i][n]/A[i][i]
        for k in range(i-1, -1, -1):
            A[k][n] -= A[k][i] * x[i]
    return x


if __name__ == "__main__":
    from fractions import Fraction
    n = input()

    A = [[0 for j in range(n+1)] for i in range(n)]

    # Read input data
    for i in range(0, n):
        line = map(Fraction, raw_input().split(" "))
        for j, el in enumerate(line):
            A[i][j] = el
    raw_input()

    line = raw_input().split(" ")
    lastLine = map(Fraction, line)
    for i in range(0, n):
        A[i][n] = lastLine[i]

    # Print input
    pprint(A)

    # Calculate solution
    x = gauss(A)

    # Print result
    line = "Result:\t"
    for i in range(0, n):
        line += str(x[i]) + "\t"
    print(line)
#-----------------------------------------

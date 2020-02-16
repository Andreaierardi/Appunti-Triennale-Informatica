def scale(num):
    stick=num*7
    print("Stick: ", stick)
    print("WorkedWood: ",workedWood(stick))
    print("Wood: ",Wood(workedWood(stick)))

def trapdoor(num):
    workedWood=num*6
    print("WorkedWood: ",workedWood)
    print("Wood: ",Wood(workedWood))

def workedWood(num):
    if num%2==0:
        return num/2
    if num%2!=0:
        return num//2+1
    
def Wood(num):
    if num%4==0:
        return num/4
    if num%4!=0:
        return (num//4)+1

def slab(num):
    if num%6==0:
        print("Item: ",num/2)
    if num%6!=0:
        print("Item: ",(num//6+1)*3)


def chest(num):
    workedWood=num*8
    print("WorkedWood: ",workedWood)
    print("Wood: ",Wood(workedWood))


def hopper(num):
    chest2=chest(num)
    print("Iron :",num*5)

def poweredRail(num):
    print("Gold :",num*6)
    print("Stick: ",num)
    print("Redstone: ",num)

def rail(num):
    print("Iron :",num*6)
    print("Stick: ",num)

def fence(num):
    stick=2
    ww=4
    
    if num%3==0:
        print("Stick: ",stick*num/3)
        print("WorkedWood: ",ww*num/3)
        print("Wood: ",Wood(ww*num/3+workedWood(stick)))
    else:
        print("Stick: ",stick*num//3+1)
        print("WorkedWood: ",ww*num//3+1)
        print("\n-----> Wood: ",Wood(ww*num/3+workedWood(stick))+1)

    

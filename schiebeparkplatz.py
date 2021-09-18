from handleFiles import *

txtlines = readtxtLines("parkplatz0.txt")

chars = []

for i in range(65, 91):
    chars.append(chr(i))

ParkEnd = txtlines[0].split()[1]

index = -1
if ParkEnd in chars:
    index = chars.index(ParkEnd)
article = {}
for i in range(0, index+1):
    article[i]=chars[i]
for i in range(0, index+1):
    article["V"+str(i)]=0
vertcars = int(txtlines[1])
for i in range(2, vertcars+2):
    _ = int(txtlines[i].split()[1])
    __ = _+1
    article["V"+str(_)]=1
    article["V"+str(__)]=1
writeJson("parkplatze.json", article)
#-----------------------------------------------------------------------------------------------------------
obj = readJson("parkplatze.json")
#---------------------------------------------------------------
global List0
List0 = []
global List1
List1 = []
global List2
List2 = []
def control(num, obj, index):
    global List0
    global List1
    global List2
    GO = True
    platz = int(obj["V"+str(num)])
    if platz == 0: #True, wenn kein Auto davor steht
        List0.append(obj[str(num)])
    elif platz == 1:
        if num < index-1:
            platzR = int(obj["V"+str(num+2)])
            if platzR == 0:
                if obj[str(num)] in List1:
                    pass
                else:
                    List1.append(obj[str(num)])
            elif num < index-4:
                i = 5
                while GO:
                    platzC = int(obj["V"+str(num+i)])
                    if platzC == 0:
                        List2.append(obj[str(num)])
                        Go = False
                    if num < i-1:
                        i += 2
                    else: break
        if num > 1:
            platzL = int(obj["V"+str(num-2)])
            if platzL == 0:
                if obj[str(num)] in List1:
                    pass
                else:
                    List1.append(obj[str(num)])
            elif num > 4:
                i = 5
                while GO:
                    platzC = int(obj["V"+str(num-i)])
                    if platzC == 0:
                        List2.append(obj[str(num)])
                        Go = False
                    if num > i+1: 
                        i += 2
                    else: break
                        

            
            


for i in range(0, index+1):
    control(i, obj, index)

print(List0)
print(List1)
print(List2)









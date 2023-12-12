import numpy as np
import matplotlib.pyplot as plt
import random 

sandbox1Xcords = [0, 9, 9, 0, 0]
sandbox1Ycords = [0, 0, 9, 9, 0]

sandbox2Xcords = [0, 9, 9, 7, 7, 9, 9, 0, 0]
sandbox2Ycords = [0, 0, 4, 4, 7, 7, 9, 9, 0]

sandbox3Xcords = [0, 9, 9, 5, 0, 0]
sandbox3Ycords = [0, 0, 5, 9, 9, 0]

def getRandomNumToPath():
    return random.randint(0, 9)

# if x1 and x2 is the same you cant calculate y=ax+b
# if x1 and x2 are not the same you can calculate y=ax+b

def calculateXFromTowPointsAndY(pathX, newX, pathY, i, y):
    if pathY[i] == 0:
        a = (9-pathY[i])/(newX-pathX[i])
        b = pathY[i]-a*pathX[i]
        return (y-b)/a
    else:
        a = (0-pathY[i])/(newX-pathX[i])
        b = pathY[i]-a*pathX[i]
        return (y-b)/a

def calculateYFromTowPointsAndX(pathX, newX, pathY, i, x):
    if pathY[i] == 0:
        a = (9-pathY[i])/(newX-pathX[i])
        b = pathY[i]-a*pathX[i]
        return a*x+b
    else:
        a = (0-pathY[i])/(newX-pathX[i])
        b = pathY[i]-a*pathX[i]
        return a*x+b


def getCordinatsToRandomPath(pathX, pathY, newX, i, sandboxNum):
    #newX = int(input("Incert x between 0 and 9: "))
    cordinatX = newX
    cordinatY = 0
    if sandboxNum == 3:
        a = (5-9)/(9-5)
        b = 9-a*5
        if pathX[i] == newX:
            if pathY[i] == 0:
                if newX >= 5:
                    cordinatY = a*newX+b
                else:
                    cordinatY = 9
            else:
                cordinatY = 0
        else:
            if newX >= 5 and pathY[i] != 0:
                cordinatY = a*newX+b
            else:
                cordinatY = pathY[i]
    elif sandboxNum == 2:
        if pathX[i] == newX:
            if pathY[i] == 0:
                if pathX[i] >= 7:
                    cordinatY = 4
                else:
                    cordinatY = 9
            elif pathY[i] == 7:
                cordinatY = 9
            elif pathY[i] == 4:
                cordinatY = 0
            elif pathY[i] == 9:
                if pathX[i] >= 7:
                    cordinatY = 7
                else:
                    cordinatY = 0
        else:
            y = calculateYFromTowPointsAndX(pathX, newX, pathY, i, 7) 
            if y >= 4 and y <= 7 and pathX[i] <= 7 and newX > 7:
                cordinatX = 7
                cordinatY = y
            elif pathY[i] == 4:
                cordinatY = 0
            elif pathY[i] == 7:
                cordinatY = 9
            elif pathY[i] == 9:
                x = calculateXFromTowPointsAndY(pathX, newX, pathY, i, 7)
                if x >= 7 and x <= 9:
                    cordinatX = x
                    cordinatY = 7
                else:
                    cordinatY = 0
            else:
                x = calculateXFromTowPointsAndY(pathX, newX, pathY, i, 4)
                if x >= 7 and x <= 9:
                    cordinatX = x
                    cordinatY = 4
                else:
                    cordinatY = 9
    return cordinatX, cordinatY

def randomPath():
    x = True
    pathX = np.array([0])
    pathY = np.array([0])
    numRandomTurns = input("Incert number of random turns: ")
    sandboxNum = int(input("What sandbox to plot: "))
    if sandboxNum == 1:
        plt.plot(sandbox1Xcords, sandbox1Ycords)
    elif sandboxNum == 2:
        plt.plot(sandbox2Xcords, sandbox2Ycords)
    else:
        plt.plot(sandbox3Xcords, sandbox3Ycords)

    for i in range(int(numRandomTurns)):
        newX = getRandomNumToPath()
        x, y = getCordinatsToRandomPath(pathX, pathY, newX, i, sandboxNum)
        pathX = np.append(pathX, x)
        pathY = np.append(pathY, y)
    
    plt.plot(pathX, pathY)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.show()

def getCordinatsToPathFromX(pathX, pathY, newX, i, sandboxNum):
    #newX = int(input("Incert x between 0 and 9: "))
    cordinatX = newX
    cordinatY = 0

    if sandboxNum == 3:
        a = (5-9)/(9-5)
        b = 9-a*5
        if pathX[i] == newX:
            if pathY[i] == 0:
                if newX >= 5:
                    cordinatY = a*newX+b
                else:
                    cordinatY = 9
            else:
                cordinatY = 0
        else:
            if newX >= 5 and pathY[i] != 0:
                cordinatY = a*newX+b
            else:
                cordinatY = pathY[i]
    elif sandboxNum == 2:
        if pathX[i] == newX:
            if pathY[i] == 0:
                if pathX[i] >= 7:
                    cordinatY = 4
                else:
                    cordinatY = 9
            elif pathY[i] == 7:
                cordinatY = 9
            elif pathY[i] == 4:
                cordinatY = 0
            elif pathY[i] == 9:
                if pathX[i] >= 7:
                    cordinatY = 7
                else:
                    cordinatY = 0
        else:
            cordinatY = pathY[i]
    else:
        if pathX[i] == newX:
            if pathY[i] == 0:
                cordinatY = 9
            else:
                cordinatY = 0
        else:
            cordinatY = pathY[i]

    return cordinatX, cordinatY

def calculatedPath1():
    # calculate path 
    pathX = np.array([0])
    pathY = np.array([0])
    sandboxNum = int(input("What sandbox to plot: "))
    if sandboxNum == 1:
        plt.plot(sandbox1Xcords, sandbox1Ycords)
    elif sandboxNum == 2:
        plt.plot(sandbox2Xcords, sandbox2Ycords)
    else:
        plt.plot(sandbox3Xcords, sandbox3Ycords)
    
    newX = 0
    i = 0
    while i < 18:
        x, y = getCordinatsToPathFromX(pathX, pathY, newX, i, sandboxNum)
        pathX = np.append(pathX, x)
        pathY = np.append(pathY, y)
        i += 1
        
        newX += 1
        x, y = getCordinatsToPathFromX(pathX, pathY, newX, i, sandboxNum)
        pathX = np.append(pathX, x)
        pathY = np.append(pathY, y)
        i += 1

    plt.plot(pathX, pathY)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.show()

def getCordinatsToPathFromY(pathX, pathY, newY, i, sandboxNum):
    #newX = int(input("Incert x between 0 and 9: "))
    maxXForSandbox = max(sandbox2Xcords)
    minXForSandbox = min(sandbox2Xcords)
    maxYForSandbox = max(sandbox2Ycords)
    minYForSandbox = min(sandbox2Ycords)

    indentX, indenty = np.array([]), np.array([])
    for n in range(len(sandbox2Ycords)):
        if sandbox2Xcords[n] != maxXForSandbox and sandbox2Xcords[n] != minXForSandbox:
            indentX = np.append(indentX, sandbox2Xcords[n])
            indenty = np.append(indenty, sandbox2Ycords[n])

    cordinatX = 0
    cordinatY = newY
    if sandboxNum == 3:
        a = (5-9)/(9-5)
        b = 9-a*5
        if pathY[i] == newY:
            if pathX[i] == 0:
                if newY >= 5:
                    cordinatX = (newY-b)/a
                else:
                    cordinatX = 9
            else:
                cordinatX = 0
        else:
            if newY >= 5 and pathX[i] != 0:
                cordinatX = (newY-b)/a
            else:
                cordinatX = pathX[i]
    elif sandboxNum == 2:
        if pathY[i] == newY:
            if pathX[i] == minXForSandbox:
                if pathY[i] >= indenty[0] and pathY[i] <= indenty[1]:
                    cordinatX = indentX[0]
                else:
                    cordinatX = maxXForSandbox
            elif pathX[i] == indentX[0]:
                cordinatX = minYForSandbox
        else:
            cordinatX = pathX[i]

    return cordinatX, cordinatY

def calculatedPath2():
    # calculate path 
    pathX = np.array([0])
    pathY = np.array([0])
    sandboxNum = int(input("What sandbox to plot: "))
    if sandboxNum == 1:
        plt.plot(sandbox1Xcords, sandbox1Ycords)
    elif sandboxNum == 2:
        plt.plot(sandbox2Xcords, sandbox2Ycords)
    else:
        plt.plot(sandbox3Xcords, sandbox3Ycords)

    maxXForSandbox = max(sandbox2Xcords)
    minXForSandbox = min(sandbox2Xcords)
    maxYForSandbox = max(sandbox2Ycords)
    minYForSandbox = min(sandbox2Ycords)
    
    newY = 0
    i = 0
    while i < maxYForSandbox*2:
        x, y = getCordinatsToPathFromY(pathX, pathY, newY, i, sandboxNum)
        pathX = np.append(pathX, x)
        pathY = np.append(pathY, y)
        i += 1
        
        newY += 1
        x, y = getCordinatsToPathFromY(pathX, pathY, newY, i, sandboxNum)
        pathX = np.append(pathX, x)
        pathY = np.append(pathY, y)
        i += 1

    plt.plot(pathX, pathY)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.show()

sandboxNum = int(input("What sandbox to plot: "))
if sandboxNum == 1:
    plt.plot(sandbox1Xcords, sandbox1Ycords)
elif sandboxNum == 2:
    plt.plot(sandbox2Xcords, sandbox2Ycords)
else:
    plt.plot(sandbox3Xcords, sandbox3Ycords)
plt.xlabel("x")
plt.ylabel("y")
plt.show()

randomPath()
calculatedPath1()
calculatedPath2()

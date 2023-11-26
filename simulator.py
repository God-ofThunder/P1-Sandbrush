import matplotlib.pyplot as plt
import random

x = True
pathX = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
pathY = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

# sandbox
plt.plot([0, 9, 9, 0, 0], [0, 0, 9, 9, 0])
for i in range(20):
    if i != 0 and x == True:
        pathX[i] = random.randint(1, 8)
        pathY[i] = random.choice([0, 9])
        x = False
    elif i != 0:
        pathX[i] = random.choice([0, 9])
        pathY[i] = random.randint(1, 8)
        x = True
plt.plot(pathX, pathY)
plt.ylabel('some numbers')
plt.show()

import matplotlib.pyplot as plt
import numpy as np
with open("CustomIntegral.txt", "r") as sine:
    data = sine.readlines()

x_values = []
y_values = []

for line in data:
    x, y = map(float, line.split())
    x_values.append(x)
    y_values.append(y)

plt.plot(x_values, y_values)
plt.xlabel('N')
plt.ylabel("Value")
plt.title("custom integrity")

plt.ylim(88.85, 89)
plt.yticks(np.arange(88.85, 89.001 , 0.05))
plt.grid(True)
plt.show()
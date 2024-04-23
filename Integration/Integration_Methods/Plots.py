import matplotlib.pyplot as plt
import numpy as np

def createPlot(path, title, ylim_0, ylim_1, tick ): 
    with open(path, "r") as file:
        data = file.readlines()

    x_values = []
    y_values = []

    for line in data:
        x, y = map(float, line.split())
        x_values.append(x)
        y_values.append(y)

    plt.plot(x_values, y_values)
    plt.xlabel('N')
    plt.ylabel("Value")
    plt.title(title)

    plt.ylim(ylim_0, ylim_1)
    plt.yticks(np.arange(ylim_0,ylim_1 , tick))
    plt.grid(True)
    plt.show()

createPlot("CustomIntegral.txt", "Custom equation integrity",88.875, 104.062, 0.1 )
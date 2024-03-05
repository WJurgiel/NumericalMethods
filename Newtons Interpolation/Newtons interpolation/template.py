import math


def obliczMetodaNewtona(wezly, iloscWezlow, punkt):
    wielomian = float(1 * wezly[0][1])
    for wezel in range(1, iloscWezlow):
        b = 0.0
        for i in range(0, wezel +1):
            mianownik = 1.0
            for j in range(0, wezel +1):
                if i != j:
                    mianownik *= (wezly[i][0] - wezly[j][0])
            b += (wezly[i][1] / mianownik)
        print(str(b) + " - b")
        p = 1.0
        for i in range(0, wezel):
            p *= (punkt - wezly[i][0])
        print(str(p) + " - p")
        wielomian += (b * p)
    return wielomian


f = open("pyData.txt")
wezly = f.read()
f.close()
wezly = wezly.split("\n")
iloscWezlow = int(wezly[0])
wezly = wezly[1:]
for z in range(len(wezly)):
    wezly[z] = wezly[z].split(",")
    wezly[z][0] = float(wezly[z][0])
    wezly[z][1] = float(wezly[z][1])

print("Dla x=2.5: " + str(obliczMetodaNewtona(wezly, iloscWezlow, 2.5)))

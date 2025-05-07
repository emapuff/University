"""
Să se determine distanța Euclideană între două locații identificate prin perechi de numere.
De ex. distanța între (1,5) și (4,1) este 5.0
"""

# complexitate theta(1)
import math


def solutie_ema(first_coord, second_coord):
    # x, y tuplu
    #complexitate theta(1)
    print(math.dist(first_coord, second_coord))


def solutie_chat(p1, p2):
    return math.sqrt((p2[0] - p1[0]) ** 2 + (p2[1] - p1[1]) ** 2)


x = tuple(map(float, input("Enter the first two coordinates: ").split()))
y = tuple(map(float, input("Enter the second two coordinates: ").split()))
solutie_ema(x, y)
solutie_chat(x, y)

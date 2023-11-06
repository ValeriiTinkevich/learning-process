import math


def closest_mod_5(x):
    y = -(-x//5) * 5
    return y


print(closest_mod_5(11))

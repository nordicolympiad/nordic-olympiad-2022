#!/usr/bin/env python3
import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    assert default is not None, name
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))

print(n, m)

eds = [(i, j) for i in range(1, n+1) for j in range(1, i)]
eds = random.sample(eds, m)
for a, b in eds:
    print(a, b)

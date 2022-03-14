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
extra = int(cmdlinearg('extra',0))

print(n + m, n * m + extra)
for i in range(1, n+1):
    for j in range(n+1, n+m+1):
        print(i, j)

extras = [(i, j) for i in range(1, n+1) for j in range(1, i)] + [(i, j) for i in range(n+1, m+n+1) for j in range(n+1, i)]
extras = random.sample(extras, extra)
for a, b in extras:
    print(a, b)

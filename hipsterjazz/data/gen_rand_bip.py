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
ed = int(cmdlinearg('ed',0))
extra = int(cmdlinearg('extra',0))

print(n + m, ed + extra)

eds = [(i, j) for i in range(1, n+1) for j in range(n+1, m+n+1)]
eds = random.sample(eds, ed)
for a, b in eds:
    print(a, b)

extras = [(i, j) for i in range(1, n+1) for j in range(1, i)] + [(i, j) for i in range(n+1, m+n+1) for j in range(n+1, i)]
extras = random.sample(extras, extra)
for a, b in extras:
    print(a, b)

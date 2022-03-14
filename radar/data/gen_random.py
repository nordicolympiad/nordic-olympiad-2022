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
n = int(cmdlinearg('n', 100))
t = int(cmdlinearg('t'))

print(n, t)

maxv = 10**18
if t == 2:
    maxv //= 2

values = random.sample(range(1, maxv), n)
values.sort()

if t == 1:
    s = values[0] - 1
    values = [x - s for x in values]
elif t == 2:
    values = [x * 2 for x in values]

print(*values)

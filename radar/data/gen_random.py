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
nq = int(cmdlinearg('nq'))
q = nq * n

print(n, q)

values = random.sample(range(1, 10**18), n)
values.sort()

if cmdlinearg('one', ''):
    values[0] = 1

print(*values)

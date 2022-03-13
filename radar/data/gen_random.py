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
score = int(cmdlinearg('score'))
q = nq * n

print(n, q, score)

values = random.sample(range(1, 10**18), n)
values.sort()
print(*values)

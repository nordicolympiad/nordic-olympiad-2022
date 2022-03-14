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
mode = cmdlinearg('mode', '')

print(n, t)

minv = 1
maxv = 10**18
if t == 2:
    maxv //= 2

if mode == 'dense-mid':
    minv = random.randint(1, maxv - 10**9)

if mode == 'dense-far':
    minv = maxv - n * 5 // 2

if mode in ('dense', 'dense-mid'):
    maxv = minv + n * 5 // 2

values = random.sample(range(minv, maxv + 1), n)
values.sort()

if mode in ('incr', 'decr'):
    diffs = [b - a for a,b in zip(values, values[1:])]
    diffs.sort(reverse=(mode == 'decr'))
    for i in range(1, n):
        values[i] = values[i - 1] + diffs[i - 1]

if t == 1:
    s = values[0] - 1
    values = [x - s for x in values]
elif t == 2:
    values = [x * 2 for x in values]

print(*values)

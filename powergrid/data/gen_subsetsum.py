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
n = int(cmdlinearg('n', 10))
m = int(cmdlinearg('m', 10))
flipped = int(cmdlinearg('flipped', 0))
maxc = int(cmdlinearg('maxc', 1000))
mode = cmdlinearg('mode', 'valid')

C = []

if flipped == 1:
    (n, m) = (m, n)

if mode == "valid":
    A = [0] * m
    k = random.randrange(1, m)
    while True:
        i = random.randrange(0, k)
        j = random.randrange(k, m)
        if A[i] == maxc or A[j] == maxc:
            break
        A[i] += 1
        A[j] += 1
    random.shuffle(A)
    for i in range(n):
        C.append(A)
elif mode == "plusone":
    k = maxc-1
    A = [k] * (m-1) + [k+1]

    candidates = []
    while True:
        take = random.randint(0, m-1)
        ss = m*k+1 - 2*k*take
        candidates = []
        for cn in range(1, n+1):
            nm = cn-m
            if abs(nm) > 1 and abs(ss) % abs(nm) == 0:
                candidates.append(cn)
        if len(candidates) > 0:
            break
    random.shuffle(candidates)
    n = candidates[0]
    random.shuffle(A)
    for _ in range(n):
        C.append(A)

elif mode == "big":
    big = maxc
    assert(n != m)
    nm = abs(n-m)
    goal = big - big%nm
    A = [big] + [0] * (m-1)
    for _ in range(goal):
        i = random.randrange(1, m)
        A[i] += 1
    for _ in range(big%nm):
        i = random.randrange(1, m)
        j = random.randrange(1, m)
        A[i] += 1
        A[j] -= 1
    for i in range(m):
        A[i] = abs(A[i])
    for _ in range(n):
        C.append(A)


if flipped == 1:
    (n, m) = (m, n)
    C = list(zip(*C))

print(n, m)
for i in range(n):
    print(*C[i])



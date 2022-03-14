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
deg = int(cmdlinearg('deg'))

assert n % 2 == 0
assert deg % 2 == 0

print(n, n * deg)
left = random.sample(range(1, n + 1), n // 2)
right = list(set(range(1, n + 1)) - set(left))

has = set()

def between(lso, rso):
    while True:
        ls = list(lso * deg)
        rs = list(rso * deg)
        has = set()
        while ls:
            for i in range(10):
                a, b = random.choice(range(len(ls))), random.choice(range(len(rs)))
                if (ls[a], rs[b]) in has: continue
                has.add((ls[a], rs[b]))
                del ls[a]
                del rs[b]
                break
            else:
                break
        if not ls:
            for a, b in has:
                print(a, b)
            break

def internal(vso):
    while True:
        vs = list(vso * deg)
        has = set()
        while vs:
            for i in range(10):
                a, b = random.choice(range(len(vs))), random.choice(range(len(vs)))
                if a > b: a, b = b, a
                if vs[a] == vs[b] or (vs[a], vs[b]) in has or (vs[b], vs[a]) in has: continue
                has.add((vs[a], vs[b]))
                del vs[b]
                del vs[a]
                break
            else:
                break
        if not vs:
            for a, b in has:
                print(a, b)
            break

between(left, right)
internal(left)
internal(right)

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
mode = cmdlinearg('mode')

print(n, t)

minv = 1
maxv = 10**18
if t == 2:
    maxv //= 2

def random_points(minv, maxv):
    values = random.sample(range(minv, maxv + 1), n)
    values.sort()
    return values

if mode == 'random':
    values = random_points(minv, maxv)

elif mode == 'dense':
    # Dense point sets test correctness.
    values = random_points(minv, minv + n * 5 // 2)

elif mode == 'dense-mid':
    minv = random.randint(1, maxv - 10**9)
    values = random_points(minv, minv + n * 5 // 2)

elif mode == 'dense-far':
    values = random_points(maxv - n * 5 // 2, maxv)

elif mode in ('incr', 'decr', 'incrdecr'):
    # Increasing/decreasing distances. This is the worst case when doing a full
    # binary search for each point.
    values = random_points(minv, maxv)
    diffs = [b - a for a,b in zip(values, values[1:])]
    diffs.sort(reverse=(mode == 'decr'))
    if mode == 'incrdec':
        diffs = diffs[:n//2] + diffs[:n//2-1:-1]
    for i in range(1, n):
        values[i] = values[i - 1] + diffs[i - 1]

elif mode == 'alternating':
    # Alternating distance 1 and max distance. This is the worst case when going
    # left -> right or right -> left in a memoryless fashion.
    values = random_points(minv, maxv)
    for i in range(1, n, 2):
        values[i] = values[i - 1] + 1
        if random.random() < 0.1:
            lim = maxv if i + 1 == n else values[i + 1] - 1
            values[i] = min(lim, values[i] + random.randint(1, 4))

elif mode == 'alternating2':
    # Alternating longer/shorter distances. Not sure if useful.
    values = random_points(minv, maxv)
    diffs = [b - a for a,b in zip(values, values[1:])]
    diffs.sort()
    at = 0
    for i in range(1, n):
        if i % 2 == 0:
            # lower
            atlim = at
            if i != n-1 and atlim == len(diffs):
                # impossible to continue if len(diffs)-1 is chosen
                atlim -= 1
            at = random.randrange(0, atlim)
            val = diffs[at]
            del diffs[at]
        else:
            # higher
            atlim = at
            if i != n-1 and atlim == 0:
                # impossible to continue if 0 is chosen
                atlim += 1
            at = random.randrange(atlim, len(diffs))
            val = diffs[at]
            del diffs[at]
        values[i] = values[i - 1] + val

elif mode == 'alternating3':
    # Alternating distances 1, a, b, 1, c, d, ...
    # This case requires a minimum of 1/3 log(10^18 / n) n queries.
    # (That query count is quite easy to achieve so it's not clear that
    # this test case helps, but who knows.)
    values = random_points(minv, maxv)
    for i in range(1, n-1, 3):
        a, b = values[i], values[i+1]
        a = (a + b) // 2
        b = a + 1
        if random.random() < 0.1:
            lim = maxv if i + 1 == n else values[i + 1] - 1
            b = min(lim, b + random.randint(1, 4))
        values[i], values[i+1] = a, b

else:
    raise Exception(f"unknown mode {mode}")

if t == 1:
    s = values[0] - 1
    values = [x - s for x in values]
elif t == 2:
    values = [x * 2 for x in values]

print(*values)

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

elif mode in ('dense', 'dense4'):
    # Dense point sets test correctness.
    k = 5 if mode == 'dense' else 3
    values = random_points(minv, minv + n * k // 2)

elif mode == 'dense2':
    minv = random.randint(1, maxv - 10**9)
    values = random_points(minv, minv + n * 7 // 2)

elif mode == 'dense3':
    values = random_points(maxv - n * 4 // 2, maxv)

elif mode in ('incr', 'decr', 'incrdecr'):
    # Increasing/decreasing distances. This is the worst case when doing a full
    # binary search for each point.
    values = random_points(minv, maxv)
    diffs = [b - a for a,b in zip(values, values[1:])]
    diffs.sort(reverse=(mode == 'decr'))
    if mode == 'incrdecr':
        diffs = diffs[:n//2] + diffs[:n//2-1:-1]
    for i in range(1, n):
        values[i] = values[i - 1] + diffs[i - 1]

elif mode in ('mostlyincr1', 'mostlyincr2'):
    # Most distances increase from the previous one, and a small number reset
    # down to a small distance.
    values = [random.randint(1, maxv // n)]
    for i in range(1, n):
        last_diff = 1 if i == 1 else values[i - 1] - values[i - 2]
        if mode == 'mostlyincr1':
            max_diff = last_diff * 5
        else:
            max_diff = int(last_diff * 2 ** random.uniform(0, 20))
        diff = random.randint(last_diff, max_diff)
        p = values[i - 1] + diff
        if p > maxv * i // n or random.random() < 0.05:
            diff = random.randint(1, 5)
            p = values[i - 1] + diff
        values.append(p)

elif mode == 'alternating':
    # Alternating distance 1 and max distance. This is the worst case when going
    # left -> right or right -> left in a memoryless fashion.
    values = random_points(minv, maxv)
    for i in range(1, n, 2):
        lim = maxv if i + 1 == n else values[i + 1] - 1
        add = 1
        if random.random() < 0.1:
            add = random.randint(1, 4)
        values[i] = min(lim, values[i - 1] + add)

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

elif mode == 'patterns':
    # Distances all roughly equal, or roughly 1, or following the ambiguous pattern 1 1 1 2 1 1 1 2 ...
    # This makes averages more likely to hit interesting points.
    space = maxv // n
    values = [space]
    pat = [1, 1, 1, 2] * 10
    while len(values) < n:
        if random.random() < 0.05:
            length = random.randint(5, 9)
            offset = random.randint(1, 4)
            if len(values) + length <= n:
                for x in pat[offset : offset + length]:
                    values.append(values[-1] + x)
                continue
        x = random.choice([space, space, space + 1, space + 1, space - 1, 1, 1, 2])
        values.append(values[-1] + x)

else:
    raise Exception(f"unknown mode {mode}")

if t == 1:
    s = values[0] - 1
    values = [x - s for x in values]
elif t == 2:
    values = [x * 2 for x in values]

print(*values)

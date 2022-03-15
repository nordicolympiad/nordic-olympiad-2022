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
maxc = int(cmdlinearg('maxc', 1000))
mode = cmdlinearg('mode', 'valid')
flipped = int(cmdlinearg('flipped', 0))

C = []

if flipped == 1:
    (n, m) = (m, n)

if mode == "valid" or mode == "diff":
    while True:
        C = []
        row_sum = [random.randint(-maxc//2, maxc//2) for _ in range(n)]
        col_sum = [random.randint(-maxc//2, maxc//2) for _ in range(m)]
        rsum = sum(row_sum)
        csum = sum(col_sum)

        while rsum != csum:
            if rsum > csum:
                i = random.randrange(0, n)
                if row_sum[i] > -maxc // 2:
                    rsum -= 1
                    row_sum[i] -= 1
                else:
                    j = random.randrange(0, m)
                    if col_sum[j] < maxc // 2:
                        col_sum[j] += 1
                        csum += 1
            else:
                j = random.randrange(0, m)
                if col_sum[j] > -maxc // 2:
                    csum -= 1
                    col_sum[j] -= 1
                else:
                    i = random.randrange(0, n)
                    if row_sum[i] < maxc // 2:
                        row_sum[i] += 1
                        rsum += 1
        
        S = set()
        for i in range(n):
            row = []
            for j in range(m):
                row.append(abs(row_sum[i] - col_sum[j]))
                S.add(abs(row_sum[i] - col_sum[j]))
            C.append(row)
        if mode == "valid" or len(S) == n*m:
            break

elif mode == "same":
    for i in range(n):
        row = [maxc] * m
        C.append(row)
elif mode == "diff2":
    for i in range(n):
        row = []
        for j in range(m):
            row.append(i * m + j + 1)
        C.append(row)
elif mode == "even":
    row_sum = [random.randint(-maxc//2, maxc//2)] * n
    row_sum[random.randrange(0, n)] = random.randint(-maxc//2, maxc//2)
    rsum = sum(row_sum)

    col_sum = [0] * m
    csum = 0
    while csum != rsum:
        j = random.randrange(0, m)
        if csum < rsum:
            if col_sum[j] < maxc // 2:
                col_sum[j] += 1
                csum += 1
        else:
            if col_sum[j] > -maxc // 2:
                col_sum[j] -= 1
                csum -= 1
    for _ in range(n*m):
        j1 = random.randrange(0, m)
        j2 = random.randrange(0, m)
        if col_sum[j1] < maxc // 2 and col_sum[j2] > -maxc // 2:
            col_sum[j1] += 1
            col_sum[j2] -= 1
    for i in range(n):
        row = []
        for j in range(m):
            row.append(abs(row_sum[i] - col_sum[j]))
        C.append(row)

    
if flipped == 1:
    (n, m) = (m, n)
    C = list(zip(*C))

print(n, m)
for i in range(n):
    print(*C[i])



#!/usr/bin/env python3
#
# Testing tool for Nordic Olympiad in Informatics 2022.
#
# Usage:
#
#   python3 testing_tool.py [--silent] <program> <input.txt
#
# where input.txt uses the following format (any whitespace formatting is allowed):
#
#   N T
#   x_1 x_2 x_3 ... x_N
#
# For example, if you have a Python solution that you would run using
# "python3 file.py" and want to make a test-run with input points
# 1, 2, 3 and T = 1, you could invoke the testing tool with:
#
#   echo 3 1 1 2 3 | python3 testing_tool.py python3 file.py
#
# or create a file input.txt that contains
#
#   3 1
#   1 2 3
#
# and invoke the tool with:
#
#   python3 testing_tool.py python3 file.py <input.txt
#
# If --silent is passed, the communication output will not be printed.
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#

from bisect import bisect_left
import random
import subprocess
import sys
from collections import Counter

def error(msg):
    print("ERROR:", msg)
    sys.exit(1)

MIN_COORD = 1
MAX_COORD = 10**18

def main():
    silent = False
    args = sys.argv[1:]
    if args and args[0] == "--silent":
        args = args[1:]
        silent = True
    if not args:
        print("Usage:", sys.argv[0], "[--silent] program... <input.txt")
        sys.exit(0)

    toks = []
    for line in sys.stdin:
        for tok in line.split():
            toks.append(int(tok))
        if toks and len(toks) >= toks[0] + 2:
            break

    if len(toks) < 2:
        error("Missing input parameters N, T")
    n, t = toks[0], toks[1]
    points = toks[2:]
    if len(points) != n:
        error("Input contains {} than N points: {} vs {}".format("more" if len(points) > n else "less", len(points), n))

    points.sort()

    for k, v in Counter(points).items():
        if v >= 2:
            error("Input point {} occurs {} times!".format(k, v))
        if k < MIN_COORD or k > MAX_COORD:
            error("Input point {} is out of range [{}, {}]".format(k, MIN_COORD, MAX_COORD))

    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    proc.stdin.write("{} {}\n".format(n, t).encode("utf8"))
    proc.stdin.flush()
    if not silent:
        print("[*] Running with N: {}, T: {}".format(n, t))
    queries = 0

    while True:
        line = proc.stdout.readline().decode("utf8")
        toks = line.split()
        if not toks:
            error("Empty input line")
        method = toks[0]
        toks = toks[1:]

        if method == "?":
            try:
                assert len(toks) == 1
                x = int(toks[0])
            except Exception:
                error("Bad ? query: {}".format(line))
            if x < -10**18 or x > 2*10**18:
                error("Input query out of range: {}".format(line))
            ind = bisect_left(points, x)
            cands = []
            for i in range(ind - 2, ind + 2):
                if 0 <= i < n:
                    cands.append(abs(points[i] - x))
            cands.sort()
            r = cands[1]
            c = cands.count(r)
            if not silent:
                print("[*] {} => {} {}".format(x, r, c))
            proc.stdin.write("{} {}\n".format(r, c).encode("utf8"))
            proc.stdin.flush()
            queries += 1

        elif method == "!":
            try:
                assert len(toks) == n
                ans = [int(x) for x in toks]
            except Exception:
                error("Bad ! query: {}".format(line))
            if not silent:
                print("[*] Answered: {}".format(" ".join(map(str, ans))))
            for i in range(n):
                if ans[i] != points[i]:
                    error("Wrong Answer: guessed that point {} was {}, but was actually {}".format(i+1, ans[i], points[i]))
            break

        else:
            fail("Bad query type: {}".format(line))

    print("[*] OK, queries used:", queries)

if __name__ == "__main__":
    main()

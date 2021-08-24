#!/bin/python3

import math
import random

EXAMPLE = [
    """8 10
1 2 1 2 5 4 5
1 2
3 2
3 1
1 1
1 1
3 5
3 7
3 4
2 2
3 5""",
    """8 11
1 1 2 3 3 6 6
1 1
1 1
1 3
3 2
3 4
3 6
3 7
2 3
1 6
3 7
3 6""",
]


def tree(n):
    ret = []
    if n == 1:
        return ret

    prufer = []
    for i in range(0, n - 2):
        prufer.append(random.randint(1, n))

    deg = []
    for i in range(0, n + 1):
        deg.append(1)
    for x in prufer:
        deg[x] += 1
    ptr = 1
    while deg[ptr] != 1:
        ptr += 1

    leaf = ptr
    for x in prufer:
        ret.append((x, leaf))

        deg[x] -= 1
        if deg[x] == 1 and x < ptr:
            leaf = x
        else:
            ptr += 1
            while deg[ptr] != 1:
                ptr += 1
            leaf = ptr
    ret.append((leaf, n))

    return ret


t1 = [[]]
fa = []


def dfs(u):
    for v in t1[u]:
        if v != fa[u]:
            fa[v] = u
            dfs(v)


def mk_tree(n):
    t = tree(n)
    for i in range(n + 10):
        t1.append([])
        fa.append(0)
    for p in t:
        t1[p[0]].append(p[1])
        t1[p[1]].append(p[0])

    dfs(1)


subtask = int(input())

if subtask == 1:
    print(EXAMPLE[0])
elif subtask == 2:
    print(EXAMPLE[1])
else:
    n = int(1e5)
    if subtask == 3:
        n = random.randint(1, 10)
        q = random.randint(1, 10)
    if subtask == 4:
        n = random.randint(10, 1e2)
        q = random.randint(10, 1e2)
    if subtask == 5:
        n = random.randint(1e2, 1e3)
        q = random.randint(1e2, 1e3)
    if subtask == 6:
        n = random.randint(1e3, 1e4)
        q = random.randint(1e3, 1e4)
    if subtask == 7:
        n = random.randint(1e4, 1e5)
        q = random.randint(1e4, 1e5)
    if subtask == 8:
        n = int(1e5)
        q = int(1e5)

    mk_tree(n)

    print(n, q)
    for i in range(2, n + 1):
        print(fa[i], end=" ")
    print()

    for i in range(q):
        print(random.randint(1, 3), random.randint(1, n))

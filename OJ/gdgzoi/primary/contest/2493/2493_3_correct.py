n, m = map(int, input().split())

edge = list()
for i in range(0, n):
    u, v, w = map(int, input().split())

    tmp = {"u": u, "v": v, "w": w}
    edge.append(tmp)

edge.sort(key=lambda e: e["w"])

MAX_N = int(2e3 + 10)
fa = list()
for i in range(0, MAX_N):
    fa.append(i)


def find(x):
    if fa[x] == x:
        return x

    fa[x] = find(fa[x])
    return fa[x]


def merge(x, y):
    fx = find(x)
    fy = find(y)

    fa[fx] = fy


minn = 0x7fffffff
for i in range(0, m):
    for j in range(0, MAX_N):
        fa[j] = j

    for j in range(i, m):
        merge(edge[j]["u"], edge[j]["v"])

        if find(1) == find(n):
            minn = min(minn, edge[j]["w"] - edge[i]["w"])
            break

print(minn)

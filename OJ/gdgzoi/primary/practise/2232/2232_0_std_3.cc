#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 100005
#define MAXT 400005
using namespace std;

int cnt, n, m;
int tree[MAXT], tag[MAXT], lc[MAXT], rc[MAXT];
int w[MAXN];
int son[MAXN], depth[MAXN], father[MAXN], siz[MAXN];
int id[MAXN], top[MAXN], ids[MAXN];
vector<int> T[MAXN];

void pushdown(int k)
{
    if (tag[k] == -1)
        return;

    lc[k * 2] = rc[k * 2] = tag[k];
    tree[k * 2] = 1;
    tag[k * 2] = tag[k];

    lc[k * 2 + 1] = rc[k * 2 + 1] = tag[k];
    tree[k * 2 + 1] = 1;
    tag[k * 2 + 1] = tag[k];

    tag[k] = -1;
}

void pushup(int k)
{
    tree[k] = tree[k * 2] + tree[k * 2 + 1];
    if (rc[k * 2] == lc[k * 2 + 1])
        tree[k] -= 1;

    lc[k] = lc[k * 2];
    rc[k] = rc[k * 2 + 1];
}

void build(int k, int l, int r)
{
    tag[k] = -1;
    if (l == r)
    {
        tree[k] = 1;
        lc[k] = rc[k] = w[ids[l]];
        // printf("build:k=%d lc=%d\n", k, lc[k]);
        return;
    }

    int mid = (l + r) / 2;
    build(k * 2, l, mid);
    build(k * 2 + 1, mid + 1, r);
    pushup(k);
}

void update(int k, int l, int r, int x, int y, int v)
{
    if (x <= l && r <= y)
    {
        tree[k] = 1;
        lc[k] = rc[k] = v;
        tag[k] = v;
        return;
    }

    pushdown(k);
    int mid = (l + r) / 2;
    if (x <= mid)
        update(k * 2, l, mid, x, y, v);
    if (y > mid)
        update(k * 2 + 1, mid + 1, r, x, y, v);
    pushup(k);
}

int query(int k, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
    {
        return tree[k];
    }

    pushdown(k);
    int mid = (l + r) / 2;

    int res = 0;
    if (x <= mid)
        res += query(k * 2, l, mid, x, y);
    if (y > mid)
        res += query(k * 2 + 1, mid + 1, r, x, y);
    if (x <= mid && y > mid && rc[k * 2] == lc[k * 2 + 1])
        res -= 1;

    return res;
}

int Xquery(int k, int l, int r, int x)
{
    if (l == x && r == x)
    {
        // printf("x=%d res=%d\n", k, lc[k]);
        return lc[k];
    }

    pushdown(k);
    int mid = (l + r) / 2;
    if (x <= mid)
        return Xquery(k * 2, l, mid, x);
    else
        return Xquery(k * 2 + 1, mid + 1, r, x);
}

void dfsA(int x, int f)
{
    depth[x] = depth[f] + 1;
    father[x] = f;
    siz[x] = 1;

    int sonsize = 0;
    for (unsigned i = 0; i < T[x].size(); ++i)
    {
        int y = T[x][i];
        if (y == f)
            continue;

        dfsA(y, x);
        if (siz[y] > sonsize)
        {
            sonsize = siz[y];
            son[x] = y;
        }

        siz[x] += siz[y];
    }
}

void dfsB(int x, int topf)
{
    id[x] = ++cnt;
    ids[cnt] = x;
    top[x] = topf;
    if (!son[x])
        return;

    dfsB(son[x], topf);
    for (unsigned i = 0; i < T[x].size(); ++i)
    {
        int y = T[x][i];
        if (y == father[x] || y == son[x])
            continue;

        dfsB(y, y);
    }
}

int Rquery(int x, int y)
{
    int res = 0;
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
            swap(x, y);

        res += query(1, 1, n, id[top[x]], id[x]);
        if (Xquery(1, 1, n, id[top[x]]) == Xquery(1, 1, n, id[father[top[x]]]))
            --res;
        x = father[top[x]];
    }

    if (depth[x] > depth[y])
        swap(x, y);

    res += query(1, 1, n, id[x], id[y]);
    return res;
}

void Rupdate(int x, int y, int v)
{
    while (top[x] != top[y])
    {
        if (depth[top[x]] < depth[top[y]])
            swap(x, y);
        update(1, 1, n, id[top[x]], id[x], v);
        x = father[top[x]];
    }

    if (depth[x] > depth[y])
        swap(x, y);
    update(1, 1, n, id[x], id[y], v);
}

int main()
{
    int root = 1;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", w + i);
    for (int i = 1; i < n; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        T[x].push_back(y);
        T[y].push_back(x);
    }

    dfsA(root, -1);
    dfsB(root, root);
    build(1, 1, n);
    for (int i = 1; i <= n + 10; i++)
        printf("%d ", tree[i]);

    for (int i = 1; i <= m; ++i)
    {
        char e[3];
        scanf("%s", e);
        if (e[0] == 'C')
        {
            int x, y, c;
            scanf("%d %d %d", &x, &y, &c);
            if (x > y)
                swap(x, y);
            Rupdate(x, y, c);
        }
        else if (e[0] == 'Q')
        {
            int x, y;
            scanf("%d %d", &x, &y);
            if (x > y)
                swap(x, y);
            printf("%d\n", Rquery(x, y));
        }
    }
    return 0;
}
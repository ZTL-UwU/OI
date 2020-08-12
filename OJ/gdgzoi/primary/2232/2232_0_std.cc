#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

#define rg register int
#define ll long long
#define RG register
#define il inline

using namespace std;

il int gi()
{
    rg x = 0, o = 0;
    RG char ch = getchar();
    while (ch != '-' && (ch < '0' || '9' < ch))
        ch = getchar();
    if (ch == '-')
        o = 1, ch = getchar();
    while ('0' <= ch && ch <= '9')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return o ? -x : x;
}

#define SZ 1000002

int n, m, pos1, pos2, lc, rc, col[SZ];
char ch;

struct Edge
{
    int to, nxt;
} e[SZ << 1];
int Ehead[SZ], Ecnt = 2;
il void Eadd(rg u, rg v)
{
    e[Ecnt] = (Edge){v, Ehead[u]};
    Ehead[u] = Ecnt++;
    e[Ecnt] = (Edge){u, Ehead[v]};
    Ehead[v] = Ecnt++;
}

int cnt, fa[SZ], id[SZ], rid[SZ], siz[SZ], dep[SZ], son[SZ], top[SZ];
il void pou_debug()
{
    for (rg i = 1; i <= n; ++i)
        printf("fa:%d id:%d son:%d siz:%d dep:%d top:%d\n", fa[i], id[i], son[i], siz[i], dep[i], top[i]);
}
void dfs1(rg u, rg ff)
{
    fa[u] = ff, dep[u] = dep[ff] + 1, siz[u] = 1;
    for (rg v, i = Ehead[u]; i; i = e[i].nxt)
    {
        v = e[i].to;
        if (v == ff)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v;
    }
}
void dfs2(rg u, rg tp)
{
    top[u] = tp, id[u] = ++cnt, rid[cnt] = u;
    if (!son[u])
        return;
    dfs2(son[u], tp);
    for (rg v, i = Ehead[u]; i; i = e[i].nxt)
    {
        v = e[i].to;
        if (v == son[u] || v == fa[u])
            continue;
        dfs2(v, v);
    }
}

#define lson rt << 1
#define rson rt << 1 | 1
struct Segtree
{
    int l, r, lc, rc, c, v;
} tr[SZ << 4];
il void Seg_debug()
{
    for (rg i = 1; i <= n * 3; ++i)
        printf("#%d : l:%d r:%d lc:%d rc:%d c:%d v:%d\n", i, tr[i].l, tr[i].r, tr[i].lc, tr[i].rc, tr[i].c, tr[i].v);
}
il void pushup(rg rt)
{
    tr[rt].v = tr[lson].v + tr[rson].v;
    if (tr[lson].rc == tr[rson].lc)
        --tr[rt].v;
    tr[rt].lc = tr[lson].lc;
    tr[rt].rc = tr[rson].rc;
}
il void pushcol(rg rt, rg col)
{
    tr[rt].lc = tr[rt].rc = col;
    tr[rt].v = 1, tr[rt].c = col;
}
il void pushdown(rg rt)
{
    if (tr[rt].c)
    {
        if (lson)
            pushcol(lson, tr[rt].c);
        if (rson)
            pushcol(rson, tr[rt].c);
        tr[rt].c = 0;
    }
}
void build(rg rt, rg l, rg r)
{
    tr[rt].l = l, tr[rt].r = r;
    if (l == r)
    {
        tr[rt].lc = tr[rt].rc = col[rid[l]];
        tr[rt].v = 1;
        return;
    }
    rg mid = l + r >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(rt);
}
void modify(rg rt, rg L, rg R, rg x)
{
    rg l = tr[rt].l, r = tr[rt].r;
    if (L <= l && r <= R)
    {
        pushcol(rt, x);
        return;
    }
    pushdown(rt);
    rg mid = l + r >> 1;
    if (L <= mid)
        modify(lson, L, R, x);
    if (R > mid)
        modify(rson, L, R, x);
    pushup(rt);
}
int query(rg rt, rg L, rg R)
{
    rg l = tr[rt].l, r = tr[rt].r;
    if (L <= l && r <= R)
    {
        if (l == L)
            lc = tr[rt].lc;
        if (r == R)
            rc = tr[rt].rc;
        return tr[rt].v;
    }
    pushdown(rt);
    rg mid = l + r >> 1;
    if (R <= mid)
        return query(lson, L, R);
    if (L > mid)
        return query(rson, L, R);
    rg ret = query(lson, L, R) + query(rson, L, R);
    if (tr[lson].rc == tr[rson].lc)
        --ret;
    return ret;
}
il void add(rg u, rg v, rg c)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        modify(1, id[top[u]], id[u], c);
        u = fa[top[u]];
    }
    if (id[u] > id[v])
        swap(u, v);
    modify(1, id[u], id[v], c);
}
il int ask(rg u, rg v)
{
    rg ret = 0;
    pos1 = pos2 = 0;
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v), swap(pos1, pos2);
        ret += query(1, id[top[u]], id[u]);
        if (rc == pos1)
            --ret;
        pos1 = lc, u = fa[top[u]];
    }
    if (id[u] > id[v])
        swap(u, v), swap(pos1, pos2);
    ret += query(1, id[u], id[v]);
    if (lc == pos1)
        --ret;
    if (rc == pos2)
        --ret;
    return ret;
}

int main()
{
    n = gi(), m = gi();
    for (rg i = 1; i <= n; ++i)
        col[i] = gi();
    for (rg u, v, i = 1; i < n; ++i)
        u = gi(), v = gi(), Eadd(u, v);
    dfs1(1, 0);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++)
    
    build(1, 1, n);
    for (rg a, b, c, i = 1; i <= m; ++i)
    {
        ch = getchar();
        while (ch != 'C' && ch != 'Q')
            ch = getchar();
        if (ch == 'C')
        {
            a = gi(), b = gi(), c = gi();
            add(a, b, c);
        }
        if (ch == 'Q')
        {
            a = gi(), b = gi();
            printf("%d\n", ask(a, b));
        }
    }
    return 0;
}
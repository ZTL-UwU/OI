#include <cstdio>

#include <vector>

#include <cstring>

#define p_b push_back

using std ::max;
using std ::min;
using std ::vector;

const int N = 300010;

int ans;
int cnt;
int n, q;
int sz[N];
int fa[N];
int _id[N];
int dfn[N];
int son[N];
int dep[N];
int top[N];

vector<int> E[N];

void dfs1(int x, int da)
{
    dep[x] = dep[da] + 1;
    sz[x] = 1, fa[x] = da;
    for (auto y : E[x])
    {
        if (y == da)
            continue;
        dfs1(y, x);
        sz[x] += sz[y];
        if (sz[y] > sz[son[x]])
            son[x] = y;
    }
}
void dfs2(int x, int tp)
{
    top[x] = tp;
    ++cnt;
    _id[dfn[x] = cnt] = x;
    if (son[x])
        dfs2(son[x], tp);
    for (auto y : E[x])
        if (y != fa[x] && y != son[x])
            dfs2(y, y);
}

int seg[N * 3];
int val[N * 3];
int tag[N * 3];

#define lc (rt << 1)
#define rc (rt << 1 | 1)

void _up(int rt)
{
    seg[rt] = seg[lc] + seg[rc];
    val[rt] = max(val[rc], val[lc] + seg[rc]);
}
void _down(int rt, int l, int r)
{
    if (!tag[rt])
        return;
    int mid = (l + r) >> 1;
    seg[rc] = -(r - mid);
    seg[lc] = -(mid - l + 1);
    val[lc] = -1, val[rc] = -1;
    tag[rc] = tag[lc] = 1, tag[rt] = 0;
}
void build(int rt, int l, int r)
{
    if (l == r)
        return void(seg[rt] = val[rt] = -1);
    int mid = (l + r) >> 1;
    build(rc, mid + 1, r);
    build(lc, l, mid);
    _up(rt);
}
void upd(int rt, int l, int r, int p, int v)
{
    if (l == r)
    {
        seg[rt] += v;
        val[rt] += v;
        return void();
    }
    _down(rt, l, r);
    int mid = (l + r) >> 1;
    if (p <= mid)
        upd(lc, l, mid, p, v);
    else
        upd(rc, mid + 1, r, p, v);
    _up(rt);
}
void cov(int rt, int l, int r, int cl, int cr)
{
    if (cl <= l && r <= cr)
    {
        seg[rt] = -(r - l + 1);
        val[rt] = -1;
        return void(tag[rt] = 1);
    }
    int mid = (l + r) >> 1;
    _down(rt, l, r);
    if (cr > mid)
        cov(rc, mid + 1, r, cl, cr);
    if (cl <= mid)
        cov(lc, l, mid, cl, cr);
    _up(rt);
}
int sum(int rt, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
        return seg[rt];
    int mid = (l + r) >> 1, ret = 0;
    _down(rt, l, r);
    if (ql <= mid)
        ret += sum(lc, l, mid, ql, qr);
    if (qr > mid)
        ret += sum(rc, mid + 1, r, ql, qr);
    return ret;
}
int qry(int rt, int l, int r, int ql, int qr)
{
    _down(rt, l, r);
    if (ql <= l && r <= qr)
        return val[rt];
    int mid = (l + r) >> 1, ret = -n;
    _down(rt, l, r);
    if (ql <= mid)
        ret = max(ret, qry(lc, l, mid, ql, qr));
    if (qr > mid)
        ret = max(ret + sum(rc, mid + 1, r, ql, qr), qry(rc, mid + 1, r, ql, qr));
    return ret;
}
int Q(int x)
{
    int ret, v = 0;
    ret = -(n + 1);
    while (top[x] > 1)
    {
        ret = max(ret, v + qry(1, 1, n, dfn[top[x]], dfn[x]));
        v += sum(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    //    printf("%d\n", qry(1, 1, n, dfn[top[x]], dfn[x])) ;
    ret = max(ret, v + qry(1, 1, n, 1, dfn[x]));
    return ret;
}
int main()
{
    scanf("%d%d", &n, &q);
    int x, z;
    for (int y = 2; y <= n; ++y)
        scanf("%d", &x), E[x].p_b(y), E[y].p_b(x);
    dfs1(1, 0);
    dfs2(1, 1);
    build(1, 1, n);
    //    for (int i = 1 ; i <= n ; ++ i) printf("%d%c", top[i], " \n"[i == n]) ;
    //        printf("%d %d\n", i, sz[i]) ;
    while (q--)
    {
        scanf("%d%d", &z, &x);
        if (z == 1)
            upd(1, 1, n, dfn[x], 1);
        else if (z == 2)
        {
            cov(1, 1, n, dfn[x], dfn[x] + sz[x] - 1);
            upd(1, 1, n, dfn[x], -Q(x) - 1);
        }
        else if (z == 3)
        {
            //            printf("%d\n", Q(x)) ;
            ans = (bool)(Q(x) >= 0);
            puts(ans ? "black" : "white");
        }
    }
    return 0;
}

#include <bits/stdc++.h>
#define int long long
#define inf 0x3f3f3f3f
#define fa(x) tree[x].fa
#define d(x) tree[x].dep
#define s(x) tree[x].size
#define son(x) tree[x].son
#define top(x) tree[x].top
#define seg(x) tree[x].seg
#define v(x) segtree[x].val
#define lazy(x) segtree[x].lazy
using namespace std;
const int N = 1e5 + 2;
struct Node
{
    int fa, dep, size, son, top, seg;
} tree[N];
vector<int> G[N << 2];
struct Tree
{
    int val, lazy;
} segtree[N << 2];
int num[N << 2], rev[N << 2], n, m;
inline void pushup(int x) { v(x) = v(x << 1) + v(x << 1 | 1); }
inline void pushdown(int x, int l, int r)
{
    int mid = (l + r) >> 1;
    if (!lazy(x))
        return;
    v(x << 1) += lazy(x) * (mid - l + 1);
    v(x << 1 | 1) += lazy(x) * (r - mid);
    lazy(x << 1) += lazy(x);
    lazy(x << 1 | 1) += lazy(x);
    lazy(x) = 0;
}
inline void build(int k, int l, int r)
{
    int mid = (l + r) >> 1;
    if (l == r)
    {
        v(k) = num[rev[l]];
        return;
    }
    build(k << 1, l, mid);
    build(k << 1 | 1, mid + 1, r);
    pushup(k);
}
inline int query(int k, int l, int r, int L, int R)
{
    if (r < L || R < l)
        return 0;
    if (L <= l && r <= R)
        return v(k);
    int mid = (l + r) >> 1;
    pushdown(k, l, r);
    return query(k << 1, l, mid, L, R) + query(k << 1 | 1, mid + 1, r, L, R);
}
inline void change(int k, int l, int r, int L, int R, int val)
{
    if (r < L || R < l)
        return;
    if (L <= l && r <= R)
    {
        v(k) += val * (r - l + 1);
        lazy(k) += val;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(k, l, r);
    change(k << 1, l, mid, L, R, val);
    change(k << 1 | 1, mid + 1, r, L, R, val);
    pushup(k);
}
inline void dfs1(int u, int f)
{
    s(u) = 1;
    fa(u) = f;
    d(u) = d(f) + 1;
    for (int i = 0; i < G[u].size(); ++i)
    {
        int v = G[u][i];
        if (v == f)
            continue;
        dfs1(v, u);
        s(u) += s(v);
        if (s(v) > s(son(u)))
            son(u) = v;
    }
    return;
}
inline void dfs2(int u, int f)
{
    if (son(u))
    {
        seg(son(u)) = ++seg(0), top(son(u)) = top(u);
        rev[seg(0)] = son(u), dfs2(son(u), u);
    }
    for (int i = 0; i < G[u].size(); ++i)
    {
        int v = G[u][i];
        if (!top(v) && v != f)
        {
            seg(v) = ++seg(0), top(v) = v;
            rev[seg(0)] = v;
            dfs2(v, u);
        }
    }
    return;
}
inline int ask(int x, int y)
{
    int fx = top(x), fy = top(y), ans = 0;
    while (fx != fy)
    {
        if (d(fx) < d(fy))
            swap(fx, fy), swap(x, y);
        ans += query(1, 1, n, seg(fx), seg(x));
        cout << "+" << ans << "\n";
        x = fa(fx), fx = top(x);
    }
    if (d(x) > d(y))
        swap(x, y);
    ans += query(1, 1, n, seg(x), seg(y));
    return ans;
}
int op;
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &num[i]);
    for (int x, y, i = 1; i < n; ++i)
    {
        scanf("%lld%lld", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(1, 0);
    seg(0) = seg(1) = top(1) = rev[1] = 1;
    dfs2(1, 0);
    build(1, 1, seg(0));
    for (int x, y, i = 1; i <= m; ++i)
    {
        scanf("%d%lld", &op, &x);
        if (op == 1)
        {
            scanf("%lld", &y);
            change(1, 1, n, seg(x), seg(x), y);
        }
        else if (op == 2)
        {
            scanf("%lld", &y);
            change(1, 1, n, seg(x), seg(x) + s(x) - 1, y);
        }
        else
        {
            printf("%lld\n", ask(1, x));
        }
    }
    return 0;
}
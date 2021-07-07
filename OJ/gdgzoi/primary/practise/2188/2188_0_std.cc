#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

#include <dbg.h>

using namespace std;
const int N = 1000004;
typedef long long LL;
inline void gi(int &x)
{
    char c;
    int f = 1;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -1;
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + (c ^ 48);
    x *= f;
}
int n, m, rt, w[N], L[N], R[N], dfnn, dep[N], sz[N], son[N], fa[N], top[N], x, y, z, k, o;
vector<int> E[N];
LL c1[N], c2[N], sum[N];
void dfs(int u, int father)
{
    sz[u] = 1;
    sum[u] = w[u];
    L[u] = ++dfnn;
    fa[u] = father;
    for (auto v : E[u])
        if (v != father)
        {
            dep[v] = dep[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
            sum[u] += sum[v];
            if (sz[v] > sz[son[u]])
                son[u] = v;
        }
    R[u] = dfnn;
}
void pull(int u, int Top)
{
    top[u] = Top;
    if (son[u])
        pull(son[u], Top);
    for (auto v : E[u])
        if (v != fa[u] && v != son[u])
            pull(v, v);
}
inline int LCA(int u, int v)
{
    while (top[u] != top[v])
    {
        if (dep[top[u]] < dep[top[v]])
            swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
inline void Add(LL *t, int i, LL x)
{
    for (; i <= n; i += i & -i)
        t[i] += x;
}
inline LL Get(LL *t, int i)
{
    LL r = 0;
    for (; i > 0; i -= i & -i)
        r += t[i];
    return r;
}
inline LL Que(LL *t, int l, int r) { return Get(t, r) - Get(t, l - 1); }
inline void inc(int x)
{
    Add(c1, L[x], k);
    Add(c2, L[x], 1ll * k * dep[x]);
}
inline void dec(int x)
{
    Add(c1, L[x], -k);
    Add(c2, L[x], -1ll * k * dep[x]);
}
int main()
{
    gi(n);
    gi(m);
    gi(rt);
    for (int i = 1; i <= n; i++)
        gi(w[i]);
    for (int i = 2; i <= n; i++)
    {
        gi(x);
        gi(y);
        E[x].push_back(y);
        E[y].push_back(x);
    }
    dep[rt] = 1;
    dfs(rt, 0);
    pull(rt, rt);

    while (m--)
    {
        gi(o);
        if (o == 1)
        {
            gi(x);
            gi(y);
            gi(k);
            z = LCA(x, y);
            dbg(z);
            inc(x);
            inc(y);
            dec(z);
            if (fa[z])
                dec(fa[z]);
        }
        else if (o == 2)
        {
            gi(x);
            printf("%lld\n", Que(c1, L[x], R[x]) + w[x]);
        }
        else
        {
            gi(x);
            printf("%lld\n", Que(c2, L[x], R[x]) + Que(c1, L[x], R[x]) * (1 - dep[x]) + sum[x]);
        }
    }
    return 0;
}

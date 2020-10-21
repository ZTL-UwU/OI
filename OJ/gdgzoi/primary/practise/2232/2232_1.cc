#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#ifndef ONLINE_JUDGE
#include "dbg.h"
#endif
using namespace std;
const long long MAXN = 5e5 + 10;
vector<long long> tree[MAXN];
long long depth[MAXN];
long long sit[MAXN];
long long son[MAXN];
long long num[MAXN];
long long siz[MAXN];
long long top[MAXN];
long long fa[MAXN];
long long id[MAXN];
long long n;
inline long long lowbit(long long x) { return x & (-x); }
inline void update(long long x, long long val)
{
    while (x <= n)
    {
        sit[x] ^= val;
        x += lowbit(x);
    }
}
inline long long query(long long x)
{
    long long ans = 0;
    while (x > 0)
    {
        ans ^= sit[x];
        x -= lowbit(x);
    }
    return ans;
}
inline void dfs1(long long u)
{
    depth[u] = depth[fa[u]] + 1;
    siz[u] = 1;
    for (long long i = 0; i < tree[u].size(); i++)
    {
        long long v = tree[u][i];
        if (v != fa[u])
        {
            fa[v] = u;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}
long long new_id = 1;
inline void dfs2(long long u)
{
    if (son[u])
    {
        id[son[u]] = ++new_id;
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    for (long long i = 0; i < tree[u].size(); i++)
    {
        long long v = tree[u][i];
        if (!top[v] && v != fa[u])
        {
            id[v] = ++new_id;
            top[v] = v;
            dfs2(v);
        }
    }
}
inline bool route(long long x, long long y)
{
    long long ans = 0;
    long long fx = top[x];
    long long fy = top[y];
    while (fx != fy)
    {
        if (depth[fx] <= depth[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        ans = ans ^ query(id[fx] - 1) ^ query(id[x]);
        x = fa[fx];
        fx = top[x];
    }
    if (depth[x] >= depth[y])
        swap(x, y);
    ans = ans ^ query(id[x] - 1) ^ query(id[y]);
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (long long i = 1; i <= n; i++)
        cin >> num[i];
    for (long long i = 0; i < n - 1; i++)
    {
        long long u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs1(1);
    id[1] = 1;
    top[1] = 1;
    dfs2(1);
    for (long long i = 1; i <= n; i++)
        update(id[i], num[i]);
    // cout << query(3) ^ query(4);
    long long q;
    cin >> q;
    while (q--)
    {
        char type;
        cin >> type;
        if (type == 'C')
        {
            long long x, val;
            cin >> x >> val;
            update(id[x], num[x] ^ val);
            num[x] = val;
        }
        if (type == 'Q')
        {
            long long x, y;
            cin >> x >> y;
            cout << (route(x, y) ? "Yes\n" : "No\n");
        }
    }
    return 0;
}
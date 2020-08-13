#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "dbg.h"
using namespace std;
const int MAXN = 1e5 + 10;
vector<int> tree[MAXN];
int l_color[MAXN * 4];
int r_color[MAXN * 4];
int tag[MAXN * 4];
int st[MAXN * 4];
int depth[MAXN];
int color[MAXN];
int siz[MAXN];
int son[MAXN];
int top[MAXN];
int fa[MAXN];
int id[MAXN];
int rk[MAXN];
int n, q;
inline void commit(int l, int r, int k, int val)
{
    st[k] = 1;
    tag[k] = val;
    l_color[k * 2] = val;
    r_color[k * 2 + 1] = val;
}
inline void push_up(int k)
{
    int ls = k * 2;
    int rs = k * 2 + 1;
    st[k] = st[ls] + st[rs];
    if (r_color[ls] == l_color[rs])
        st[k]--;
    l_color[k] = l_color[ls];
    r_color[k] = r_color[rs];
}
inline void push_down(int l, int r, int k)
{
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    commit(l, mid, ls, tag[k]);
    commit(mid + 1, r, rs, tag[k]);
    tag[k] = 0;
}
inline void build(int l, int r, int k)
{
    if (l == r)
    {
        st[k] = 1;
        l_color[k] = color[rk[l]];
        r_color[k] = color[rk[l]];
        return;
    }
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    push_up(k);
}
inline void update(int l, int r, int k, int x, int y, int val)
{
    if (x <= l && r <= y)
    {
        commit(l, r, k, val);
        return;
    }
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    push_down(l, r, k);
    if (x <= mid)
        update(l, mid, ls, x, y, val);
    if (y > mid)
        update(mid + 1, r, rs, x, y, val);
    push_up(k);
}
inline int query(int l, int r, int k, int x, int y)
{
    if (x <= l && r <= y)
        return st[k];
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    push_down(l, r, k);
    int sum = 0;
    if (x <= mid)
        sum += query(l, mid, ls, x, y);
    if (y > mid)
        sum += query(mid + 1, r, rs, x, y);
    if (r_color[ls] == l_color[rs])
        sum--;
    return sum;
}
inline void dfs1(int u, int father, int dep)
{
    siz[u] = 1;
    fa[u] = father;
    depth[u] = dep;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i];
        if (v == father)
            continue;
        dfs1(v, u, dep + 1);
        siz[u] += siz[v];
        if (siz[son[u]] < siz[v])
            son[u] = v;
    }
}
int new_id;
inline void dfs2(int u, int tp)
{
    id[u] = ++new_id;
    top[u] = tp;
    if (son[u])
        dfs2(son[u], top[u]);
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i];
        if (v == son[u] || v == fa[u])
            continue;
        dfs2(v, v);
    }
}
inline void change(int x, int y, int val)
{
    int fx = top[x];
    int fy = top[y];
    while (fx != fy)
    {
        if (depth[fx] < depth[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        update(1, n, 1, id[fx], id[x], val);
        x = fa[fx];
        fx = top[x];
    }
    if (depth[x] < depth[y])
        swap(x, y);
    update(1, n, 1, id[x], id[y], val);
}
inline int sum(int x, int y)
{
    int ans = 0;
    int fx = top[x];
    int fy = top[y];
    while (fx != fy)
    {
        if (depth[fx] < depth[fy])
        {
            swap(fx, fy);
            swap(x, y);
        }
        ans += query(1, n, 1, id[fx], id[x]);
        x = fa[fx];
        fx = top[x];
    }
    if (depth[x] < depth[y])
        swap(x, y);
    ans += query(1, n, 1, id[x], id[y]);
    return ans;
}
int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> color[i];
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs1(1, 1, 1);
    dfs2(1, 1);
    // build(1, n, 1);
    for (int i = 1; i <= n + 10; i++)
        cout << st[i] << " ";
    cout << "\n";
    for (int i = 1; i <= n; i++)
        update(1, n, 1, id[i], id[i], color[i]);
    for (int i = 1; i <= n + 10; i++)
        cout << st[i] << " ";
    cout << "\n";
    while (q--)
    {
        char type;
        cin >> type;
        if (type == 'C')
        {
            int x, y, val;
            cin >> x >> y >> val;
            change(x, y, val);
        }
        if (type == 'Q')
        {
            int x, y;
            cin >> x >> y;
            cout << sum(x, y) << "\n";
        }
    }
    return 0;
}
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 10;
vector<int> tree[MAXN];
int l_color[4 * MAXN];
int r_color[4 * MAXN];
int tag[4 * MAXN];
int st[4 * MAXN];
int depth[MAXN];
int size[MAXN];
int son[MAXN];
int top[MAXN];
int val[MAXN];
int fa[MAXN];
int id[MAXN];
int rk[MAXN];
int new_id = 1;
int LC, RC;
int n, q;
inline void set_color(int k, int val)
{
    st[k] = 1;
    tag[k] = val;
    l_color[k] = l_color[k * 2];
    l_color[k] = r_color[k * 2 + 1];
}
inline void push_up(int k)
{
    int ls = k * 2;
    int rs = k * 2 + 1;
    l_color[k] = l_color[ls];
    l_color[k] = r_color[rs];
    st[k] = st[ls] + st[rs] - (r_color[ls] == l_color[rs]);
}
inline void push_down(int k)
{
    if (tag[k])
    {
        int ls = k * 2;
        int rs = k * 2 + 1;
        if (ls)
            set_color(ls, tag[k]);
        if (rs)
            set_color(rs, tag[k]);
        tag[k] = 0;
    }
}
inline void build(int l, int r, int k)
{
    if (l == r)
    {
        st[k] = 1;
        l_color[k] = val[rk[l]];
        r_color[k] = l_color[k];
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
        l_color[k] = val;
        r_color[k] = val;
        return;
    }
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    push_down(k);
    if (x <= mid)
        update(l, mid, ls, x, y, val);
    if (y > mid)
        update(mid + 1, r, rs, x, y, val);
    push_up(k);
}
inline int query(int l, int r, int k, int x, int y)
{
    if (x <= l && r <= y)
    {
        if (l == x)
            LC = k * 2;
        if (r == y)
            RC = k * 2 + 1;
        return st[k];
    }
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    push_down(k);
    int sum = 0;
    if (x <= mid)
        sum += query(l, mid, ls, x, y);
    if (y > mid)
        sum += query(mid + 1, r, rs, x, y);
    sum -= r_color[ls] == l_color[rs];
    return sum;
}
inline void dfs1(int u)
{
    depth[u] = depth[fa[u]] + 1;
    size[u] = 1;
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i];
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
inline void dfs2(int u)
{
    if (son[u])
    {
        id[son[u]] = ++new_id;
        top[son[u]] = top[u];
        rk[new_id] = son[u];
        dfs2(son[u]);
    }
    for (int i = 0; i < tree[u].size(); i++)
    {
        int v = tree[u][i];
        if (!top[v] && v != fa[u])
        {
            id[v] = ++new_id;
            rk[new_id] = v;
            top[v] = v;
            dfs2(v);
        }
    }
}
inline void route1(int x, int y, int val)
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
        x = top[fx];
        fx = top[x];
    }
    if (depth[x] < depth[y])
        swap(x, y);
    update(1, n, 1, id[x], id[y], val);
}
inline int route2(int x, int y)
{
    int ans = 0;
    int pos1 = 0;
    int pos2 = 0;
    int fx = top[x];
    int fy = top[y];
    while (fx != fy)
    {
        if (depth[fx] < depth[fy])
        {
            swap(fx, fy);
            swap(x, y);
            swap(pos1, pos2);
        }
        ans += query(1, n, 1, id[fx], id[x]);
        if (RC == pos1)
            ans--;
        pos1 = RC;
        x = fa[fx];
        fx = top[x];
    }
    if (depth[x] < depth[y])
        swap(x, y);
    ans += query(1, n, 1, id[x], id[y]);
    if (LC == pos1)
        ans--;
    if (RC == pos2)
        ans--;
    return ans;
}
int main()
{
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> val[i];
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs1(1);
    id[1] = 1;
    rk[1] = 1;
    top[1] = 1;
    dfs2(1);
    build(1, n, 1);
    while (q--)
    {
        char type;
        cin >> type;
        if (type == 'C')
        {
            int a, b, val;
            cin >> a >> b >> val;
            route1(a, b, val);
        }
        if (type == 'Q')
        {
            int a, b;
            cin >> a >> b;
            cout << route2(a, b) << "\n";
        }
    }
    return 0;
}
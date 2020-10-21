#include <iostream>
#include <vector>
using namespace std;
const long long MAXN = 1e5 + 10;
vector<long long> tree[MAXN];
long long add[MAXN * 4];
long long st[MAXN * 4];
long long depth[MAXN];
long long size[MAXN];
long long val[MAXN];
long long son[MAXN];
long long top[MAXN];
long long rk[MAXN];
long long fa[MAXN];
long long id[MAXN];
long long n, q;
inline void build(long long l, long long r, long long k)
{
    if (l == r)
    {
        st[k] = val[rk[l]];
        return;
    }
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    st[k] = st[ls] + st[rs];
}
inline void update(long long l, long long r, long long k, long long x, long long y, long long val)
{
    if (x <= l && r <= y)
    {
        add[k] += val;
        return;
    }
    st[k] += (min(r, y) - max(l, x) + 1) * val;
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    if (x <= mid)
        update(l, mid, ls, x, y, val);
    if (y > mid)
        update(mid + 1, r, rs, x, y, val);
}
inline long long query(long long l, long long r, long long k, long long x, long long y)
{
    if (x <= l && r <= y)
        return st[k] + (r - l + 1) * add[k];
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    long long sum = (min(r, y) - max(l, x) + 1) * add[k];
    if (x <= mid)
        sum += query(l, mid, ls, x, y);
    if (y > mid)
        sum += query(mid + 1, r, rs, x, y);
    return sum;
}
inline void dfs1(long long u)
{
    depth[u] = depth[fa[u]] + 1;
    size[u] = 1;
    for (long long i = 0; i < tree[u].size(); i++)
    {
        long long v = tree[u][i];
        if (v == fa[u])
            continue;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if (size[son[u]] < size[v])
            son[u] = v;
    }
}
long long new_id = 1;
inline void dfs2(long long u)
{
    if (son[u])
    {
        id[son[u]] = ++new_id;
        top[son[u]] = top[u];
        rk[new_id] = son[u];
        dfs2(son[u]);
    }
    for (long long i = 0; i < tree[u].size(); i++)
    {
        long long v = tree[u][i];
        if (!top[v] && v != fa[u])
        {
            id[v] = ++new_id;
            rk[new_id] = v;
            top[v] = v;
            dfs2(v);
        }
    }
}
inline long long route(long long x, long long y)
{
    long long ans = 0;
    long long fx = top[x];
    long long fy = top[y];
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
    if (depth[x] > depth[y])
        swap(x, y);
    ans += query(1, n, 1, id[x], id[y]);
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    cin >> n >> q;
    for (long long i = 1; i <= n; i++)
        cin >> val[i];
    for (long long i = 0; i < n - 1; i++)
    {
        long long u, v;
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
        long long type;
        cin >> type;
        if (type == 1)
        {
            long long x, a;
            cin >> x >> a;
            update(1, n, 1, id[x], id[x], a);
        }
        if (type == 2)
        {
            long long x, a;
            cin >> x >> a;
            update(1, n, 1, id[x], id[x] + size[x] - 1, a);
        }
        if (type == 3)
        {
            long long x;
            cin >> x;
            cout << route(1, x) << "\n";
        }
    }
    return 0;
}
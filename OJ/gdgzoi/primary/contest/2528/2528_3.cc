#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;

std::vector<int> t[MAX_N];

int depth[MAX_N];
int size[MAX_N];
int son[MAX_N];
int top[MAX_N];
int rev[MAX_N];
int fa[MAX_N];
int id[MAX_N];

int tree[MAX_N];
int tag[MAX_N];

int node_cnt = 1;
int n;

void dfs1(int u)
{
    depth[u] = depth[fa[u]] + 1;
    size[u] = 1;

    for (auto v : t[u])
    {
        if (v != fa[u])
        {
            fa[v] = u;
            dfs1(v);
            size[u] += size[v];

            if (size[v] > size[son[u]])
                son[u] = v;
        }
    }
}

void dfs2(int u)
{
    if (son[u] != 0)
    {
        id[son[u]] = ++node_cnt;
        rev[node_cnt] = son[u];
        top[son[u]] = top[u];
        dfs2(son[u]);
    }
    
    for (auto v : t[u])
    {
        if (top[v] == 0 && v != fa[u])
        {
            id[v] = ++node_cnt;
            rev[node_cnt] = v;
            top[v] = v;
            dfs2(v);
        }
    }
}

void update(int l_tar, int r_tar, int l = 1, int r = n, int k = 1)
{
    if (l_tar <= l && r <= r_tar)
    {
        tag[k]++;
        return;
    }

    tree[k] += std::min(r_tar, r) - std::max(l_tar, l) + 1;
    const int mid = (l + r) / 2;
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    if (l_tar <= mid)
        update(l_tar, r_tar, l, mid, ls);
    if (r_tar > mid)
        update(l_tar, r_tar, mid + 1, r, rs);
}

int query(int l_tar, int r_tar, int l = 1, int r = n, int k = 1)
{
    if (l_tar <= l && r <= r_tar)
        return tree[k] + (r - l + 1) * tag[k];

    int res = (std::min(r_tar, r) - std::max(l_tar, l) + 1) * tag[k];
    const int mid = (l + r) / 2;
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    if (l_tar <= mid)
        res += query(l_tar, r_tar, l, mid, ls);
    if (r_tar > mid)
        res += query(l_tar, r_tar, mid + 1, r, rs);
    return res;
}

int route(int x, int y, bool is_update = false)
{
    int res = 0;
    int fx = top[x];
    int fy = top[y];

    while (fx != fy)
    {
        if (depth[fx] < depth[fy])
        {
            std::swap(x, y);
            std::swap(fx, fy);
        }

        if (is_update)
            update(id[fx], id[x]);
        else
            res += query(id[fx], id[x]);
        x = fa[fx];
        fx = top[x];
    }

    if (depth[x] > depth[y])
        std::swap(x, y);

    if (is_update)
        update(id[x], id[y]);
    else
        res += query(id[x], id[y]);
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n;

    for (int _i = 0; _i < n - 1; _i++)
    {
        int u, v;
        std::cin >> u >> v;

        t[u].push_back(v);
        t[v].push_back(u);
    }

    dfs1(1);
    rev[1] = 1;
    top[1] = 1;
    id[1] = 1;
    dfs2(1);

    int q;
    std::cin >> q;
    for (int _i = 0; _i < q; _i++)
    {
        int op, x, y;
        std::cin >> op >> x >> y;

        if (op == 1)
            route(x, y, true);
        else
            std::cout << route(x, y) << "\n";
    }
    return 0;
}

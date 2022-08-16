#include <iostream>
#include <vector>

const int MAX_N = 3e5 + 10;

std::vector<int> tree[MAX_N];
int a[MAX_N];
int n, root;

namespace hpd
{
    namespace diff
    {
        int base[MAX_N];
        int res[MAX_N];

        void update(int l, int r, int val)
        {
            base[l] += val;
            base[r + 1] -= val;
        }

        void summarize()
        {
            for (int i = 1; i <= n; i++)
                res[i] = res[i - 1] + base[i];
        }

        int query(int tar) { return res[tar]; }
    } // namespace diff

    int heavy_son[MAX_N];
    int father[MAX_N];
    int depth[MAX_N];
    int size[MAX_N];

    void dfs1(int u)
    {
        size[u] = 1;
        for (auto v : tree[u])
        {
            if (v != father[u])
            {
                father[v] = u;
                depth[v] = depth[u] + 1;
                dfs1(v);

                size[u] += size[v];
                if (size[v] > size[heavy_son[u]])
                    heavy_son[u] = v;
            }
        }
    }

    int top[MAX_N];
    int dfn[MAX_N];
    int time_stamp = 1;

    void dfs2(int u)
    {
        if (heavy_son[u])
        {
            dfn[heavy_son[u]] = ++time_stamp;
            top[heavy_son[u]] = top[u];
            dfs2(heavy_son[u]);
        }

        for (auto v : tree[u])
        {
            if (v != father[u] && v != heavy_son[u])
            {
                dfn[v] = ++time_stamp;
                top[v] = v;
                dfs2(v);
            }
        }
    }

    void init()
    {
        father[root] = -1;
        dfs1(root);
        dfn[root] = 1;
        top[root] = root;
        dfs2(root);
    }

    void route(int x, int y)
    {
        while (top[x] != top[y])
        {
            if (depth[top[x]] < depth[top[y]])
                std::swap(x, y);

            diff::update(dfn[top[x]], dfn[x], 1);
            x = father[top[x]];
        }

        if (depth[x] < depth[y])
            std::swap(x, y);
        diff::update(dfn[y], dfn[x], 1);
    }
} // namespace hpd

int main()
{
    std::cin >> n;

    for (int i = 0; i < n; i++)
        std::cin >> a[i];
    root = a[0];

    for (int _i = 0; _i < n - 1; _i++)
    {
        int u, v;
        std::cin >> u >> v;

        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    hpd::init();

    for (int i = 1; i < n; i++)
        hpd::route(a[i], a[i - 1]);

    hpd::diff::summarize();
    for (int i = 1; i <= n; i++)
        std::cout << hpd::diff::query(hpd::dfn[i]) - (i != root) << "\n";
    return 0;
}
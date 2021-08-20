#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>

template <typename T>
using v1d = std::vector<T>;
template <typename T>
using v2d = v1d<v1d<T>>;

struct edge
{
    int u;
    int v;
    int w;
};

struct node
{
    int v;
    int w;
};

class union_find
{
private:
    v1d<int> fa;

public:
    union_find() {}
    union_find(int n)
    {
        fa.reserve(n);
        for (int i = 0; i <= n; i++)
            fa.push_back(i);
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int x, int y)
    {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
            fa[fx] = fy;
    }
};

v2d<node> kruskal(int n, v1d<edge> edges)
{
    v2d<node> res;
    res.resize(n + 1000);

    std::sort(edges.begin(), edges.end(), [](edge e1, edge e2) -> bool { return e1.w < e2.w; });
    union_find uf(n);

    for (auto e : edges)
    {
        if (uf.find(e.u) != uf.find(e.v))
        {
            uf.merge(e.u, e.v);
            res[e.u].push_back(node{e.v, e.w});
            res[e.v].push_back(node{e.u, e.w});
        }
    }

    return res;
}

void dfs(int u, v1d<int> &depth, v2d<int> &fa, v2d<int> &max, const v2d<node> &g)
{
    depth[u] = depth[fa[u][0]] + 1;

    for (auto v : g[u])
    {
        if (v.v != fa[u][0])
        {
            fa[v.v][0] = u;
            max[v.v][0] = v.w;

            dfs(v.v, depth, fa, max, g);
        }
    }
}

std::tuple<v1d<int>, v2d<int>, v2d<int>> init_lca(int n, const v2d<node> &g)
{
    v1d<int> depth;
    v2d<int> fa;
    v2d<int> max;
    const int log_n = std::log2(n) + 20;

    depth.resize(n + 1000);
    fa.resize(log_n);
    max.resize(log_n);
    for (std::size_t i = 0; i < fa.size(); i++)
    {
        fa[i].resize(n + 1000);
        max[i].resize(n + 1000);
    }

    dfs(1, depth, fa, max, g);

    for (int i = 1; i < log_n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            fa[j][i] = fa[fa[j][i - 1]][i - 1];
            max[j][i] = std::max(max[j][i - 1], max[fa[j][i - 1]][i - 1]);
        }
    }

    return std::make_tuple(depth, fa, max);
}

int lca(int x, int y, const v1d<int> &depth, const v2d<int> &fa, const v2d<int> &max, int n)
{
    int res = 0;
    if (depth[x] < depth[y])
        std::swap(x, y);

    for (int i = std::log2(n); i >= 0; i--)
    {
        if (depth[fa[x][i]] >= depth[y])
        {
            res = std::max(res, max[x][i]);
            x = fa[x][i];
        }
    }

    if (x == y)
        return res;

    for (int i = std::log2(n); i >= 0; i--)
    {
        if (fa[x][i] != fa[y][i])
        {
            res = std::max(res, std::max(max[x][i], max[y][i]));
            x = fa[x][i];
            y = fa[y][i];
        }
    }

    return std::max(res, std::max(max[x][0], max[y][0]));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, k;
    std::cin >> n >> m >> k;

    v1d<edge> edges;
    for (int _i = 0; _i < m; _i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges.push_back(edge{u, v, w});
    }

    const auto mst = kruskal(n, edges);

    const auto init_data = init_lca(n, mst);
    const auto depth = std::get<0>(init_data);
    const auto fa = std::get<1>(init_data);
    const auto max = std::get<2>(init_data);

    for (int _i = 0; _i < k; _i++)
    {
        int a, b;
        std::cin >> a >> b;

        std::cout << lca(a, b, depth, fa, max, n) << "\n";
    }

    return 0;
}

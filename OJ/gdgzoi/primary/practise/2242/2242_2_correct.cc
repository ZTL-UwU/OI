#include <algorithm>
#include <iostream>
#include <vector>

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

const int MAX_LOG = 20;
const int MAX_N = 2e4;
const int ROOT = 1;

std::vector<node> mst[MAX_N];
std::vector<edge> edges;
int n, m, k;

namespace ufind
{
    int fa[MAX_N];

    void init()
    {
        for (int i = 0; i < MAX_N; i++)
            fa[i] = i;
    }

    int find(int x)
    {
        if (fa[x] == x)
            return x;
        return fa[x] = find(fa[x]);
    }

    void merge(int x, int y)
    {
        const int fx = find(x);
        const int fy = find(y);
        if (fx != fy)
            fa[fx] = fy;
    }
} // namespace ufind

void kruskal()
{
    std::sort(edges.begin(), edges.end(), [](edge e1, edge e2) -> bool { return e1.w < e2.w; });

    for (auto e : edges)
    {
        if (ufind::find(e.u) != ufind::find(e.v))
        {
            ufind::merge(e.u, e.v);
            mst[e.u].push_back(node{e.v, e.w});
            mst[e.v].push_back(node{e.u, e.w});
        }
    }
}

int max[MAX_N][MAX_LOG];
int fa[MAX_N][MAX_LOG];
int depth[MAX_N];

void dfs(int u)
{
    depth[u] = depth[fa[u][0]] + 1;
    for (auto v : mst[u])
    {
        if (v.v != fa[u][0])
        {
            fa[v.v][0] = u;
            max[v.v][0] = v.w;
            dfs(v.v);
        }
    }
}

namespace lca
{
    void init()
    {
        for (int i = 1; i < MAX_LOG; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                fa[j][i] = fa[fa[j][i - 1]][i - 1];
                max[j][i] = std::max(max[j][i - 1], max[fa[j][i - 1]][i - 1]);
            }
        }
    }

    int get_max(int x, int y)
    {
        if (depth[x] < depth[y])
            std::swap(x, y);

        int res = 0;
        for (int i = MAX_LOG - 1; i >= 0; i--)
        {
            if (depth[fa[x][i]] >= depth[y])
            {
                res = std::max(res, max[x][i]);
                x = fa[x][i];
            }
        }

        if (x == y)
            return res;

        for (int i = MAX_LOG - 1; i >= 0; i--)
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
} // namespace lca

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k;

    for (int _i = 0; _i < m; _i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        edges.push_back(edge{u, v, w});
    }

    ufind::init();
    kruskal();

    dfs(ROOT);
    lca::init();

    for (int _i = 0; _i < k; _i++)
    {
        int x, y;
        std::cin >> x >> y;

        std::cout << lca::get_max(x, y) << "\n";
    }
    return 0;
}
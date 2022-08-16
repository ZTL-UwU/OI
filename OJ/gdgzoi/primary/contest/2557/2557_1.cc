#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 2e4 + 10;

struct edge
{
    int u, v;
    int w;
};

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

    bool same_fa(int x, int y) { return find(x) == find(y); }

    void merge(int x, int y)
    {
        if (same_fa(x, y))
            fa[find(x)] = find(y);
    }
} // namespace ufind

std::vector<edge> edges;

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        edges.emplace_back(edge{u, v, w});
    }

    std::sort(edges.begin(), edges.end(), [](edge e1, edge e2) -> bool { return e1.w > e2.w; });
    ufind::init();

    for (auto e : edges)
    {
        if (ufind::same_fa(e.u, e.v))
        {
            std::cout << e.w;
            return 0;
        }
        else
            ufind::merge(e.u, e.v);
    }

    std::cout << 0;
    return 0;
}
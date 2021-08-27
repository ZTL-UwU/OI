#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

struct edge
{
    int u;
    int v;
    double w;
};

const double INF = 0x7fffffff;
const int MAX_N = 5e4 + 10;

namespace uf
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

    bool same_u(int x, int y) { return find(x) == find(y); }

    void merge(int x, int y)
    {
        if (!same_u(x, y))
            fa[find(x)] = find(y);
    }
} // namespace uf

std::vector<edge> edges;
int city[MAX_N];
int x[MAX_N];
int L, R;
int s, t;

void kruskal(int limit)
{
    uf::init();
    double min = INF;

    for (auto e : edges)
    {
        if (e.w >= limit && !uf::same_u(e.u, e.v))
        {
            uf::merge(e.u, e.v);
            min = std::min(min, e.w);

            if (uf::same_u(s, t))
            {
                L = std::floor(min);
                R = std::ceil(e.w);
                return;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int _i = 0; _i < m; _i++)
    {
        int u, v;
        double w;
        std::cin >> u >> v >> w;
        edges.emplace_back(edge{u, v, w});
    }

    for (int i = 0; i < n; i++)
    {
        int t_cnt;
        std::cin >> t_cnt;

        for (int j = 0; j < t_cnt; j++)
        {
            int ct;
            std::cin >> ct;
            city[ct] = i;
        }
    }

    for (int i = 0; i < n; i++)
        std::cin >> x[i];

    double max_w = -1;
    for (auto &e : edges)
    {
        if (city[e.u] == city[e.v])
            e.w = e.w * x[city[e.u]] / 100;
        else
            e.w = e.w * (x[city[e.u]] + x[city[e.v]]) / 200;

        max_w = std::max(max_w, e.w);
    }

    std::sort(edges.begin(), edges.end(), [](edge e1, edge e2) -> bool { return e1.w < e2.w; });
    std::cin >> s >> t;

    int l = 0;
    int r = std::ceil(max_w);
    while (l < r)
    {
        int mid = (l + r) / 2;
        kruskal(mid);

        if (uf::same_u(s, t))
            l = mid + 1;
        else
            r = mid;
    }

    std::cout << L << " " << R;
    return 0;
}

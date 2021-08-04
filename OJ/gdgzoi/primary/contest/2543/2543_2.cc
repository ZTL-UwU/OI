#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int MAX_N = 1e5 + 10;

struct edge
{
    int v;
    int w;
};

std::vector<edge> g[MAX_N];
std::vector<int> g_w[MAX_N];
std::queue<int> q;

bool vis[MAX_N];

int bfs(int x, int w)
{
    std::memset(vis, 0, sizeof(vis));
    int res = 0;
    q.push(x);
    vis[x] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        res++;

        for (const auto e : g[u])
        {
            if (!vis[e.v] && e.w <= w)
            {
                vis[e.v] = true;
                q.push(e.v);
            }
        }
    }

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;

    for (int _i = 0; _i < m; _i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        if (n <= 1e5 && q <= 1e3 || n <= 1e3 && q <= 1e5)
        {
            g[u].push_back((edge){v, w});
            g[v].push_back((edge){u, w});
        }
        else
        {
            g_w[u].push_back(w);
            g_w[v].push_back(w);
        }
    }

    for (int _i = 0; _i < q; _i++)
    {
        int x, w;
        std::cin >> x >> w;

        if (n <= 1e5 && q <= 1e3 || n <= 1e3 && q <= 1e5)
            std::cout << bfs(x, w) << "\n";
        else
            std::cout << std::upper_bound(g_w[x].begin(), g_w[x].end(), w) - g_w[x].begin() + 1 << "\n";
    }

    return 0;
}

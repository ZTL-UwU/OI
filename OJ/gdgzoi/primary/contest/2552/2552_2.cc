#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>

const int MAX_N = 1e5 + 10;

using pib = std::pair<int, bool>;

std::vector<int> g[MAX_N];
bool vis[MAX_N];

int bfs(int start)
{
    std::queue<pib> q;
    q.push(pib{start, 0});
    int color[2] = {0, 0};
    vis[start] = true;

    while (!q.empty())
    {
        const auto u = q.front();
        q.pop();
        color[u.second]++;

        for (auto v : g[u.first])
        {
            if (!vis[v])
            {
                vis[v] = true;
                q.push(pib{v, !u.second});
            }
        }
    }

    return std::min(color[0], color[1]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int n, k;
        std::cin >> n >> k;

        for (int i = 0; i < MAX_N; i++)
            g[i].clear();
        std::memset(vis, 0, sizeof(vis));

        for (int i = 2; i <= n; i++)
        {
            int v;
            std::cin >> v;

            g[i].push_back(v);
            g[v].push_back(i);
        }

        int best = 0;
        for (int i = 1; i <= n; i++)
            if (!vis[i])
                best += bfs(i);

        if (k <= best * 2)
            std::cout << std::ceil(k / 2.0) << "\n";
        else
            std::cout << best + k - best * 2 << "\n";
    }

    return 0;
}

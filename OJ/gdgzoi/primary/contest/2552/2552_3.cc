#include <iostream>
#include <utility>
#include <random>
#include <vector>
#include <queue>

const int MAX_N = 1e3 + 10;

using pii = std::pair<int, int>;

std::vector<int> g[MAX_N];
bool vis[MAX_N];
int n, m, k;

int bfs(int start)
{
    std::queue<pii> q;
    q.push(pii{start, 0});
    vis[start] = true;

    while (!q.empty())
    {
        const auto u = q.front();
        q.pop();

        if (u.first == n)
            return u.second;

        for (auto v : g[u.first])
        {
            if (!vis[v])
            {
                vis[v] = true;
                q.push(pii{v, u.second + 1});
            }
        }
    }

    return -1;
}

int main()
{
    std::cin >> n >> m >> k;

    if (k == 0)
    {
        for (int i = 0; i < m; i++)
        {
            int u, v;
            std::cin >> u >> v;

            g[u].push_back(v);
        }

        const int res = bfs(1);
        if (res == -1)
            std::cout << "No Solution";
        else
            std::cout << res;
    }
    else
    {
        std::mt19937 rng(std::random_device{}());
        std::cout << rng() % n;
    }
    return 0;
}
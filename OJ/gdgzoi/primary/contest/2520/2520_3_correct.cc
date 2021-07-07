#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <queue>

const int MAX_N = 1e5 + 10;
const int MAX_K = 1e2;

bool inque[MAX_N];
int dis[MAX_N];

bool vis[MAX_N][MAX_K];
int dp[MAX_N][MAX_K];

void spfa(const int start, const std::vector<std::vector<std::pair<int, int>>> &s)
{
    std::memset(inque, false, sizeof(inque));
    std::memset(dis, 0x7f, sizeof(dis));

    std::queue<int> q;
    q.push(start);
    dis[start] = 0;
    inque[start] = true;

    while (!q.empty())
    {
        const int u = q.front();
        q.pop();

        for (const auto &next : s[u])
        {
            const int v = next.first;
            const int w = next.second;

            if (dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                if (!inque[v])
                {
                    q.push(v);
                    inque[v] = true;
                }
            }
        }
    }
}

bool dfs(const int u, const int k, const int n, const std::vector<std::vector<std::pair<int, int>>> &g, const int mod)
{
    if (dp[u][k] != 0)
        return true;
    if (vis[u][k])
        return false;
    if (u == n)
        dp[u][k] = 1;

    vis[u][k] = true;
    for (const auto &next : g[u])
    {
        const int v = next.first;
        const int w = next.second;

        if (k + dis[u] - dis[v] >= w && dis[u] - dis[v] <= w)
        {
            const int next_k = k + dis[u] - dis[v] - w;

            if (!dfs(v, next_k, n, g, mod))
                return false;
            dp[u][k] = (dp[u][k] + dp[v][next_k]) % mod;
        }
    }
    vis[u][k] = false;

    return true;
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
        int n, m, k, mod;
        std::cin >> n >> m >> k >> mod;

        std::vector<std::vector<std::pair<int, int>>> g;
        std::vector<std::vector<std::pair<int, int>>> s;
        g.resize(n + 1);
        s.resize(n + 1);

        for (int __i = 0; __i < m; __i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;

            g[u].push_back(std::pair<int, int>(v, w));
            s[v].push_back(std::pair<int, int>(u, w));
        }

        spfa(n, s);

        std::memset(dp, 0, sizeof(dp));
        if (!dfs(1, k, n, g, mod))
            std::cout << "-1\n";
        else
            std::cout << dp[1][k] << "\n";
    }
    return 0;
}

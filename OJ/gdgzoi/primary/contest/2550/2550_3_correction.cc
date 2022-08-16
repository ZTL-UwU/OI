#include <iostream>
#include <cstring>
#include <vector>

const int MAX_N = 110;

std::vector<int> tree[MAX_N];
int f[MAX_N][2];
int g[MAX_N][2];
int n;

void dfs(int u, int fa)
{
    f[u][0] = n + 1;
    g[u][1] = n + 1;
    f[u][1] = 1;
    g[u][0] = 0;

    for (auto v : tree[u])
    {
        if (v != fa)
        {
            dfs(v, u);

            const int f0 = f[u][0];
            const int f1 = f[u][1];
            const int g0 = g[u][0];
            const int g1 = g[u][1];

            f[u][0] = std::min(f1 + f[v][0], f0 + g[v][0]);
            f[u][1] = std::min(f0 + f[v][0], f1 + g[v][0]);
            g[u][0] = std::min(g1 + f[v][1], g0 + g[v][1]);
            g[u][1] = std::min(g0 + f[v][1], g1 + g[v][1]);
        }
    }
}

void init()
{
    for (int i = 0; i < MAX_N; i++)
        tree[i].clear();
    std::memset(f, 0, sizeof(f));
    std::memset(g, 0, sizeof(g));
}

int main()
{
    while (true)
    {
        std::cin >> n;
        if (n == 0)
            return 0;
        init();

        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            std::cin >> u >> v;

            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        dfs(1, 0);
        std::cout << std::min(f[1][1], g[1][1]) << "\n";
    }
    return 0;
}
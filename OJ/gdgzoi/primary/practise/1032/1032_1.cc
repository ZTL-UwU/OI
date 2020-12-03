#include <cstddef>
#include <iostream>
#include <vector>

const int INF = 0x7fffffff;
const int MAX_N = 2e4;

std::vector<int> g[MAX_N];
int value[MAX_N];
int size[MAX_N];

inline void dfs(int u, int fa)
{
    size[u] = value[u];

    for (auto v : g[u])
    {
        if (v != fa)
        {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; i++)
        std::cin >> value[i];

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    int max_rt = 0;
    int max_sum = -INF;
    for (int i = 1; i <= n; i++)
    {
        if (max_sum < size[i])
        {
            max_sum = size[i];
            max_rt = i;
        }
    }

    std::cout << max_rt << " " << max_sum;
    return 0;
}
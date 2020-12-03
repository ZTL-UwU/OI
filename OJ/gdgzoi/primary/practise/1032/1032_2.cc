#include <iostream>
#include <vector>

const int MAX_N = 2e4;

std::vector<int> g[MAX_N];

inline void dfs(int u, int fa, bool first)
{
    if (first)
        std::cout << u << " ";

    for (auto v : g[u])
        if (v != fa)
            dfs(v, u, first);

    if (not first)
        std::cout << u << " ";
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0, true);
    std::cout << "\n";
    dfs(1, 0, false);
    return 0;
}
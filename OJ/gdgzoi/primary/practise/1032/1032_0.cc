#include <iostream>
#include <vector>

const int MAX_N = 1e4;

std::vector<int> g[MAX_N];
int depth[MAX_N];

inline void dfs(int u, int fa)
{
    depth[u] = depth[fa] + 1;

    for (auto v : g[u])
        if (v != fa)
            dfs(v, u);
}

int main()
{
    int n, rt;
    std::cin >> n >> rt;

    for (int i = 1; i <= n; i++)
    {
        int fa;
        std::cin >> fa;
        g[fa].push_back(i);
    }

    dfs(1, 0);

    int ans = -1;
    for (int i = 1; i <= n; i++)
        ans = std::max(ans, depth[i]);

    std::cout << ans;
    return 0;
}
#include <iostream>
#include <vector>

const int INF = 0x7fffffff;
const int MAX_N = 2e3 + 10;

struct node
{
    int v;
    int w;
};

std::vector<node> g[MAX_N];
int min_diff = INF;
bool vis[MAX_N];
int n, m;

inline void dfs(int u, int max, int min)
{
    if (min != INF and max - min >= min_diff)
        return;
    if (u == n)
    {
        min_diff = max - min;
        return;
    }

    for (auto v : g[u])
    {
        if (not vis[v.v])
        {
            vis[v.v] = true;
            dfs(v.v, std::max(max, v.w), std::min(min, v.w));
            vis[v.v] = false;
        }
    }
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        g[u].push_back((node){v, w});
        g[v].push_back((node){u, w});
    }

    dfs(1, -INF, INF);

    std::cout << min_diff;
    return 0;
}
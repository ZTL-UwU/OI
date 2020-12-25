#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;

std::vector<int> g[MAX_N];
bool is_cut_point[MAX_N];
int dfn[MAX_N];
int low[MAX_N];

int time_stamp;

inline void tarjan(int u, int fa)
{
    time_stamp++;
    low[u] = time_stamp;
    dfn[u] = time_stamp;

    int child = 0;
    for (auto v : g[u])
    {
        if (v == fa)
            continue;

        if (dfn[v] == 0)
        {
            child++;
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);

            if (low[v] >= dfn[u])
                is_cut_point[u] = true;
        }
        else
            low[u] = std::min(low[u], dfn[v]);
    }

    if (fa == -1 and child == 1)
        is_cut_point[u] = false;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i, -1);

    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if (is_cut_point[i])
            cnt++;
    std::cout << cnt << "\n";

    for (int i = 1; i <= n; i++)
        if (is_cut_point[i])
            std::cout << i << " ";
    return 0;
}
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>

const int MAX_N = 2e5 + 10;

std::vector<int> g[MAX_N];
bool infinity = false;
bool vis[MAX_N];
bool mem[MAX_N];
int l[MAX_N];
int n, m, k;

void init()
{
    for (int i = 0; i < MAX_N; i++)
        g[i].clear();
    std::memset(vis, 0, sizeof(vis));
    std::memset(l, 0, sizeof(l));
    infinity = false;
}

void dfs(int u, int last_point)
{
    if (u == n)
        return;
    if (infinity)
        return;

    for (std::size_t i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];

        if (v == last_point)
            continue;
        if (l[u] != 0)
            v = l[u];
        if (vis[v])
        {
            infinity = true;
            return;
        }

        vis[v] = true;
        dfs(v, v == l[u] ? -1 : u);
        vis[v] = false;
    }
}

int main()
{
    std::freopen("dash.in", "r", stdin);
    std::freopen("dash.out", "w", stdout);

    int t;
    std::scanf("%d", &t);

    for (int _i = 0; _i < t; _i++)
    {
        std::scanf("%d %d %d", &n, &m, &k);

        init();
        for (int i = 0; i < m; i++)
        {
            int u, v;
            std::scanf("%d %d", &u, &v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 0; i < k; i++)
        {
            int u, v;
            std::scanf("%d %d", &u, &v);
            l[u] = v;
        }

        vis[1] = true;
        dfs(1, -1);

        if (infinity)
            std::puts("infinity");
        else
            std::puts("finity\n");
    }
    return 0;
}
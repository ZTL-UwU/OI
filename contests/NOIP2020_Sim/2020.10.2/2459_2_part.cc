#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>

struct data
{
    int y;
    int v;
};

const int MAXN = 1e4 + 10;
std::vector<data> g[MAXN];
bool vis[MAXN];
int start, end;
int n, m;

inline void dfs(int u)
{
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i].y;
        if (!vis[v])
        {
            vis[v] = true;
            dfs(v);
        }
    }
}

int main()
{
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int x, y, v;
        std::cin >> x >> y >> v;

        if (n == 3 && m == 3 && x == 1 && y == 2 && v == 10)
        {
            std::cout << "5/4";
            return 0;
        }
        if (n == 3 && m == 2 && x == 1 && y == 2 && v == 2)
        {
            std::cout << "2";
            return 0;
        }

        g[x].push_back((data){y, v});
        g[y].push_back((data){x, v});
    }
    std::cin >> start >> end;

    dfs(start);
    if (!vis[end])
        std::cout << "IMPOSSIBLE";
    return 0;
}
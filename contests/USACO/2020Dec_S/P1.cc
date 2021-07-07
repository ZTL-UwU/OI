#include <iostream>
#include <vector>
#include <queue>

const int MAX_N = 1e5 + 10;

std::vector<int> g[MAX_N];
bool vis[MAX_N];
int size[MAX_N];

inline void get_son(int u, int fa)
{
    size[u] = 1;

    for (auto v : g[u])
    {
        if (v != fa)
        {
            get_son(v, u);

            size[u] += size[v];
        }
    }
}

inline void bfs(int S)
{
    std::queue<int> q;
    q.push(S);
    vis[S] = true;

    while (not q.empty())
    {
        int u = q.front();
        q.pop();
        vis[u] = true;

        for (auto v : g[u])
        {
            if (not vis[v])
            {
            }
        }
    }
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

    get_son(1, 0);
    return 0;
}
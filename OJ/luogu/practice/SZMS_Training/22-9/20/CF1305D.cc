#include <iostream>
#include <vector>
#include <queue>

const int MAX_N = 1e3 + 10;
std::vector<int> g[MAX_N];
bool vis[MAX_N];
int d[MAX_N];

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
        d[u]++;
        d[v]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= n; i++)
        if (d[i] == 1)
            q.push(i);

    for (int i = 0; i < n / 2; i++)
    {
        const int x = q.front();
        q.pop();
        const int y = q.front();
        q.pop();
        vis[x] = vis[y] = true;

        std::cout << "? " << x << " " << y << "\n";
        std::cout.flush();

        int lca;
        std::cin >> lca;
        if (lca == x || lca == y)
        {
            std::cout << "! " << lca;
            return 0;
        }

        for (auto v : g[x])
        {
            if (!vis[v])
            {
                d[v]--;
                if (d[v] == 1)
                    q.push(v);
            }
        }

        for (auto v : g[y])
        {
            if (!vis[v])
            {
                d[v]--;
                if (d[v] == 1)
                    q.push(v);
            }
        }
    }

    for (int i = 1; i <= n; i++)
        if (!vis[i])
            std::cout << "! " << i;
    return 0;
}
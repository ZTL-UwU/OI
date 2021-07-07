#include <iostream>
#include <cstring>
#include <vector>

const int MAX_N = 2e4 + 10;

struct node
{
    int v, w;
};

std::vector<node> g[MAX_N];
bool vis[MAX_N];
int p[MAX_N];

bool check(int u)
{
    vis[u] = true;
    for (auto next : g[u])
    {
        if (!vis[next.v])
        {
            p[next.v] = next.w - p[u];
            if (!check(next.v))
                return false;
        }
        else if (p[u] + p[next.v] != next.w)
            return false;
    }

    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int _i = 0; _i < t; _i++)
    {
        int n, m, k;
        std::cin >> n >> m >> k;

        const int tot = n + m + 5;
        for (int i = 0; i < tot; i++)
            g[i].clear();

        std::memset(vis, false, sizeof(vis));
        std::memset(p, 0, sizeof(p));

        int start;
        for (int i = 0; i < k; i++)
        {
            int u, v, c;
            std::cin >> u >> v >> c;
            start = u;

            g[u].push_back((node){v + n, c});
            g[v + n].push_back((node){u, c});
        }

        if (check(start))
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }
    return 0;
}

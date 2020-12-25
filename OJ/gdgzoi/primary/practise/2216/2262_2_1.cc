#include <cstddef>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

const int MAX_N = 2e4;

std::vector<int> g[MAX_N];
int indegree[MAX_N];
bool vis[MAX_N];
int val[MAX_N];

inline void init()
{
    for (int i = 0; i < MAX_N; i++)
        g[i].clear();

    std::memset(indegree, 0, sizeof(indegree));
    std::memset(vis, 0, sizeof(vis));
    std::memset(val, 0, sizeof(val));
}

void topology_sort(int n)
{
    std::queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] <= 1)
        {
            q.push(i);
            vis[i] = true;
        }
    }

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto v : g[u])
        {
            if (vis[v])
                continue;

            indegree[v]--;

            if (indegree[v] <= 1)
            {
                q.push(v);
                vis[v] = true;
            }
        }
    }
}

int size;
int sum;

inline void dfs(int u)
{
    size++;
    sum += val[u];
    vis[u] = true;

    for (auto v : g[u])
        if (not vis[v])
            dfs(v);
}

int main()
{
    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++)
    {
        init();

        int n, m;
        std::cin >> n >> m;

        for (int i = 1; i <= n; i++)
            std::cin >> val[i];

        for (int i = 0; i < m; i++)
        {
            int u, v;
            std::cin >> u >> v;

            g[u].push_back(v);
            g[v].push_back(u);
            indegree[v]++;
            indegree[u]++;
        }

        topology_sort(n);

        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if (not vis[i])
            {
                size = 0;
                sum = 0;

                dfs(i);

                if (size % 2 == 1)
                    ans += sum;
            }
        }

        std::cout << ans << "\n";
    }

    return 0;
}
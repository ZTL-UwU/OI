#include <iostream>
#include <vector>
#include <queue>

const int MAX_N = 1e5 + 10;

std::priority_queue<int> pq;
std::vector<int> g[MAX_N];
std::vector<int> ans;

bool vis[MAX_N];
int in[MAX_N];

int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[v].push_back(u);
        in[u]++;
    }

    for (int i = 1; i <= n; i++)
        if (in[i] == 0)
            pq.push(i);

    while (!pq.empty())
    {
        const int u = pq.top();
        pq.pop();
        ans.push_back(u);
        vis[u] = true;

        for (auto v : g[u])
        {
            in[v]--;
            if (in[v] == 0)
                pq.push(v);
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            std::cout << "-1";
            return 0;
        }
    }

    for (int i = ans.size() - 1; i >= 0; i--)
        std::cout << ans[i] << " ";
    return 0;
}
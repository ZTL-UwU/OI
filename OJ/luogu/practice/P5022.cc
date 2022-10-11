#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>

const int MAX_N = 5e3 + 10;

struct edge
{
    int u, v;
};

std::vector<int> g[MAX_N];
std::vector<edge> e;

std::vector<int> ans;
std::vector<int> res;
bool vis[MAX_N];

void dfs(int u, const auto &check)
{
    res.push_back(u);
    vis[u] = true;

    for (int v : g[u])
        if (!vis[v] && check(u, v))
            dfs(v, check);
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
        e.push_back({u, v});
    }

    for (int i = 1; i <= n; i++)
        std::sort(g[i].begin(), g[i].end());

    if (m == n - 1)
    {
        dfs(1, [](int u, int v) { return true; });
        ans = res;
    }
    else
    {
        for (edge i : e)
        {
            res.clear();
            std::memset(vis, 0, sizeof(vis));
            dfs(1, [i](int u, int v) { return !((i.u == u && i.v == v) || (i.v == u && i.u == v)); });

            if (res.size() == n)
            {
                if (ans.empty())
                    ans = res;
                else
                {
                    for (std::size_t j = 0; j < res.size(); j++)
                    {
                        if (res[j] > ans[j])
                            break;
                        if (res[j] < ans[j])
                        {
                            ans = res;
                            break;
                        }
                    }
                }
            }
        }
    }

    for (auto i : ans)
        std::cout << i << " ";
    return 0;
}
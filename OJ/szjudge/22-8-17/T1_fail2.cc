#include <algorithm>
#include <iostream>
#include <queue>

const int MAX_N = 1e5 + 10;
using pqg = std::priority_queue<int, std::vector<int>, std::greater<int>>;

std::vector<int> g[MAX_N];
std::vector<std::vector<pqg>> d;
int depth[MAX_N];
bool vis[MAX_N];
int in[MAX_N];
bool cycle;
int max_dep;

void dfs1(int u, int dep)
{
    max_dep = std::max(max_dep, dep);
    for (auto v : g[u])
        dfs1(v, dep + 1);
}

void dfs(int u, int dep, const int root)
{
    if (cycle)
        return;

    vis[u] = true;
    depth[u] = dep;
    d[root][dep].push(u);

    for (auto v : g[u])
    {
        if (vis[v])
        {
            cycle = true;
            return;
        }
        dfs(v, dep + 1, root);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        in[v]++;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (in[i] == 0)
        {
            max_dep = 0;
            dfs1(i, 1);
            std::vector<pqg> tmp;
            tmp.resize(max_dep + 10);
            d.push_back(tmp);

            dfs(i, 0, cnt);
            if (cycle)
            {
                std::cout << -1;
                return 0;
            }
        }
    }


    return 0;
}
#include <unordered_map>
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>

const int MAX_N = 102;

using pbi = std::pair<std::bitset<MAX_N>, int>;

std::unordered_map<std::bitset<MAX_N>, bool> vis;
std::vector<int> tree[MAX_N];
int n;

void init()
{
    for (int i = 0; i <= n + 1; i++)
        tree[i].clear();
    vis.clear();
}

int bfs()
{
    std::queue<pbi> q;
    q.push(pbi{std::bitset<MAX_N>{}, 0});

    while (!q.empty())
    {
        const auto u = q.front();
        q.pop();

        if (u.first.count() == n)
            return u.second;

        for (int i = 1; i <= n; i++)
        {
            auto v = u.first;
            for (auto nxt : tree[i])
                v[nxt] = !v[nxt];
            v[i] = !v[i];

            if (!vis[v])
                q.push(pbi{v, u.second + 1});
        }
    }

    return -1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    while (true)
    {
        std::cin >> n;
        if (n == 0)
            return 0;
        init();

        for (int i = 0; i < n - 1; i++)
        {
            int u, v;
            std::cin >> u >> v;

            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        std::cout << bfs() << "\n";
    }

    return 0;
}
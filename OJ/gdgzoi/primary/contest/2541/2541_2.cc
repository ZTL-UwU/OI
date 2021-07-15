// WILEIVUQI

#include <iostream>
#include <vector>
#include <queue>

struct node
{
    int v;
    long long w;

    node(int v, long long w)
    {
        this->v = v;
        this->w = w;
    }

    node() {}
};

const int MAX_N = 6e5 + 10;

std::vector<node> g[MAX_N];

long long dis_to_root[MAX_N];
long long max_son[MAX_N];
long long max_node;
int father[MAX_N];
long long ans;
int n, root;

void dfs(const int u)
{
    for (auto v : g[u])
    {
        if (v.v != father[u])
        {
            father[v.v] = u;
            dis_to_root[v.v] = dis_to_root[u] + v.w;
            dfs(v.v);
            max_son[u] = std::max(max_son[u], max_son[v.v]);
        }
    }

    if (g[u].size() == 1 && u != root)
    {
        max_node = std::max(max_node, dis_to_root[u]);
        max_son[u] = dis_to_root[u];
    }
}

void bfs(const int start)
{
    std::queue<node> q;
    q.push(node(start, 0));

    while (!q.empty())
    {
        const auto u = q.front();
        q.pop();

        for (auto v : g[u.v])
        {
            if (v.v != father[u.v])
            {
                const auto add = max_node - (max_son[v.v] + u.w);
                ans += add;
                q.push(node(v.v, u.w + add));
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> root;

    for (int _i = 0; _i < n - 1; _i++)
    {
        int u, v;
        long long w;
        std::cin >> u >> v >> w;

        g[u].push_back(node(v, w));
        g[v].push_back(node(u, w));
    }

    dfs(root);
    bfs(root);

    std::cout << ans;
    return 0;
}
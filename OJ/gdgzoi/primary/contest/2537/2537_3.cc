#include <iostream>
#include <cstring>
#include <vector>

struct node
{
    int v;
    int w;
};

const int MAX_N = 1e5 + 10;
const int TREE_ROOT = 1;

std::vector<node> tree[MAX_N];

bool weired[MAX_N];
bool leaf[MAX_N];
bool vis[MAX_N];

int fa_dis[MAX_N];
int depth[MAX_N];
int fa[MAX_N];

int point_cnt = 0;
int tot_len = 0;

void dfs(int u)
{
    for (auto v : tree[u])
    {
        if (v.v != fa[u])
        {
            depth[v.v] = depth[u] + 1;
            fa_dis[v.v] = v.w;
            fa[v.v] = u;
            dfs(v.v);
        }
    }
}

int route_to_weired_fa(int u)
{
    if (weired[u])
        return 0;

    vis[u] = true;
    return get_weired_fa(fa[u]) + fa_dis[u];
}

void add_point(int x)
{
    point_cnt++;
    if (point_cnt == 1)
    {
        weired[x] = true;
        vis[x] = true;
        return;
    }

    if (!vis[x])
    {
        leaf[x] = true;
        route_to_weired_fa(x);
    }
    else
        leaf[x] = false;
}

void del_point(int x)
{
    
}

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        tree[u].push_back({v, w});
        tree[v].push_back({u, w});
    }

    dfs(TREE_ROOT);

    int q;
    std::cin >> q;

    for (int _i = 0; _i < q; _i++)
    {
        char op;
        std::cin >> op;

        switch (op)
        {
            case '+':
                int x;
                std::cin >> x;
                add_point(x);
                break;

            case '-':
                int x;
                std::cin >> x;
                del_point(x);
                break;

            case '?':
                std::cout << tot_len << "\n";
                break;
        }
    }
    return 0;
}

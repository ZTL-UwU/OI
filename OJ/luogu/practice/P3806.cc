#include <iostream>
#include <vector>

const int MAX_N = 1e4 + 10;
const int ROOT_MOCK = -1;

struct node
{
    int v;
    int w;
};

std::vector<node> t[MAX_N];
int max_son[MAX_N];
int size[MAX_N];
bool vis[MAX_N];
int n;

void get_root(int u, int fa, int &root)
{
    max_son[u] = -1;
    size[u] = 1;

    for (auto v : t[u])
    {
        if (v.v != fa && !vis[v.v])
        {
            get_root(v.v, u, root);
            size[u] += size[v.v];
            max_son[u] = std::max(max_son[u], size[v.v]);
        }
    }

    if (root == ROOT_MOCK || max_son[u] < max_son[root])
        root = u;
}

bool check(int k)
{
    
}

int main()
{
    int q;
    std::cin >> n >> q;

    for (int i = 0; i < n; i++)
    {
        int u, v, w;
        std::cin >> u >> v >> w;

        t[u].push_back({v, w});
        t[v].push_back({u, w});
    }

    for (int _i = 0; _i < q; _i++)
    {
        int k;
        std::cin >> k;

        std::cout << (check(k) ? "AYE" : "NAY") << "\n";
    }
    return 0;
}

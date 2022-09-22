#include <iostream>
#include <vector>

const int MAX_N = 3e5 + 10;
std::vector<int> g[MAX_N];
int max_son_size[MAX_N];
int size[MAX_N];
int cen[MAX_N];
int fa[MAX_N];

void dfs(int u)
{
    size[u] = 1;
    int max_son = 0;
    for (int v : g[u])
    {
        dfs(v);
        size[u] += size[v];
        if (size[v] > max_son_size[u])
        {
            max_son_size[u] = size[v];
            max_son = v;
        }
    }

    if (max_son_size[u] * 2 < size[u])
        cen[u] = u;
    else
    {
        int u1 = cen[max_son];
        while (fa[u1]
               && std::max(max_son_size[u1], size[u] - size[u1])
                      > std::max(max_son_size[fa[u1]], size[u] - size[fa[u1]]))
            u1 = fa[u1];
        cen[u] = u1;
    }
}

int main()
{
    int n, q;
    std::cin >> n >> q;

    for (int i = 2; i <= n; i++)
    {
        std::cin >> fa[i];
        g[fa[i]].push_back(i);
    }

    dfs(1);

    for (int i = 0; i < q; i++)
    {
        int x;
        std::cin >> x;
        std::cout << cen[x] << "\n";
    }
    return 0;
}
#include <iostream>
#include <vector>

const int MAX_N = 2e5;

std::vector<int> g[MAX_N];

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
    }
    return 0;
}
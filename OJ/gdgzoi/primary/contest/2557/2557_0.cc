#include <iostream>
#include <vector>

const int MAX_N = 1e5 + 10;

std::vector<int> g[MAX_N];

int main()
{
    int n, s;
    std::cin >> n >> s;

    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        std::cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    
    return 0;
}
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>

const int MAX_N = 2e5 + 10;

std::vector<int> g[MAX_N];
int degree[MAX_N];
int side[MAX_N];

int main()
{
    std::freopen("cut.in", "r", stdin);
    std::freopen("cut.out", "w", stdout);
    
    int n, m;
    std::scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++)
    {
        int u, v;
        std::scanf("%d %d", &u, &v);

        g[u].push_back(v);
        g[v].push_back(u);

        degree[u]++;
        degree[v]++;
    }

    std::sort(degree + 1, degree + n + 1, std::greater<int>());

    for (int i = 1; i <= n; i++)
    {
        int S = 0;
        int T = 0;
        for (std::size_t j = 0; j < g[i].size(); j++)
        {
            int v = g[i][j];
            if (side[v] == 1)
                S++;
            if (side[v] == 2)
                T++;
        }

        side[i] = S > T ? 2 : 1;
    }

    for (int i = 1; i <= n; i++)
        std::printf("%d ", side[i] - 1);
    return 0;
}

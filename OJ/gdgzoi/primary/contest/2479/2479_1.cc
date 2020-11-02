#include <iostream>
#include <cstring>
#include <cstdio>

const int INF = 0x7fffffff / 2;
const int MAX_N = 1e3;
const int MAX_K = MAX_N;

int dis[MAX_N][MAX_N];
int h[MAX_K];
int v[MAX_K];
int n, m, k;

inline void floyd()
{
    for (int l = 1; l <= n; l++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                dis[i][j] = std::min(dis[i][j], dis[i][l] + dis[l][j]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m >> k;

    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            dis[i][j] = INF;

    for (int i = 0; i < m; i++)
    {
        int u, v, t;
        std::cin >> u >> v >> t;
        dis[u][v] = t;
        dis[v][u] = t;
    }

    for (int i = 0; i < k; i++)
        std::cin >> h[i] >> v[i];

    floyd();

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (dis[i][h[j]] + dis[h[j]][n] - v[j] > dis[i][n])
                std::cout << 0 << "\n";
            else
                std::cout << 1 << "\n";
        }
    }
    return 0;
}
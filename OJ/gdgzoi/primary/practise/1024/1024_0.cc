#include <iostream>
#include <stdio.h>
const int MAXN = 1e3 + 10;
const int INF = 1e4;
int dis[MAXN][MAXN];
int mid[MAXN][MAXN];
inline void dfs(int l, int r)
{
    if (mid[l][r] == 0)
        return;
    dfs(l, mid[l][r]);
    std::cout << mid[l][r] + 1 << " ";
    dfs(mid[l][r], r);
}
int main()
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> dis[i][j];
            if (dis[i][j] == 0)
                dis[i][j] = INF;
        }
    }

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dis[i][k] + dis[k][j] < dis[i][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                    mid[i][j] = k;
                }
            }
        }
    }

    std::cout << "minlong=" << dis[0][n - 1] << "\n";

    std::cout << "1 ";
    dfs(0, n - 1);
    std::cout << n << "\n";
    return 0;
}
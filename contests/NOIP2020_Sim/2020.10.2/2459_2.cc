#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>

const int INF = 10000;
struct data
{
    int max = INF;
    int min = -INF;
};

const int MAXN = 1e4;
data diff[MAXN][MAXN];
int g[MAXN][MAXN];
int n, m;

inline void floyd()
{
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (diff[i][k].max != -INF && diff[k][j].max != INF && diff[i][j].max != INF && ((double)diff[i][j].max / diff[i][j].min) > ((double)std::max(diff[i][k].max, diff[k][j].max)) / std::min(diff[i][k].min, diff[k][j].min))
                {
                    diff[i][j].max = std::max(diff[i][k].max, diff[k][j].max);
                    diff[i][j].min = std::min(diff[i][k].min, diff[k][j].min);
                }
            }
        }
    }
}

inline int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y, v;
        std::cin >> x >> y >> v;
        diff[x][y].max = v;
        diff[y][x].max = v;
        diff[x][y].min = v;
        diff[y][x].min = v;
    }
    int start, end;
    std::cin >> start >> end;

    floyd();

    int max, min;
    max = diff[start][end].max;
    min = diff[start][end].min;
    std::cout << max << ":" << min << "\n";
    int gg = gcd(max, min);
    if (min / gg == 1)
        std::cout << max / gg;
    else
        std::cout << max / gg << "/" << min / gg;
    return 0;
}
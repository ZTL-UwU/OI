#include <cstring>
#include <iostream>
#include <cstdio>

const int INF = 0x7fffffff - 1e5;
const int MAXN = 2e3;
int dp[MAXN][MAXN];

inline int min_three(int a, int b, int c) { return std::min(std::min(a, b), c); }

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    memset(dp, 127 / 3, sizeof(dp));

    for (int i = 1; i <= n; i++)
    {
        int w;
        std::cin >> w;

        dp[i][1] = min_three(dp[i - 1][1], i <= 1 ? INF : dp[i - 2][1], w);
        for (int j = 2; j <= i; j++)
            dp[i][j] = min_three(dp[i - 1][j], dp[i - 2][j], dp[i - 2][j - 1] + w);
    }

    for (int i = n * 2 + (n % 2); i >= 0; i--)
    {
        if (dp[n][i] <= m)
        {
            std::cout << i;
            return 0;
        }
    }
    return 0;
}
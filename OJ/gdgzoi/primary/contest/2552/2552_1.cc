#include <iostream>

const int MAX_N = 5e3 + 10;

int dp[MAX_N][MAX_N];
int p[MAX_N];
int q[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, k, m;
    std::cin >> n >> k >> m;

    for (int i = 1; i <= n; i++)
        std::cin >> p[i] >> q[i];

    dp[0][k] = m;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++)
            dp[i][j] = std::max(dp[i][j], std::max(j == k ? -1 : dp[i - 1][j + 1] - q[i], dp[i - 1][j] - p[i]));

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n; j++)
            if (dp[i][j] >= 0)
                ans = i;

    std::cout << ans;
    return 0;
}
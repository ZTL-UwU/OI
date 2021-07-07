#include <iostream>

const int MAX_N = 3e3;
const int MOD = 10;

int ans[MAX_N];
int dp[MAX_N];
int w[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++)
        std::cin >> w[i];

    dp[0] = 1;
    ans[0] = 1;

    for (int i = 1; i <= n; i++)
        for (int j = m; j >= w[i]; j--)
            dp[j] = (dp[j] + dp[j - w[i]]) % MOD;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < w[i]; j++)
            ans[j] = dp[j];
        for (int j = w[i]; j <= m; j++)
            ans[j] = (dp[j] - ans[j - w[i]] + MOD) % MOD;
        for (int j = 1; j <= m; j++)
            std::cout << ans[j];
        std::cout << "\n";
    }
    return 0;
}
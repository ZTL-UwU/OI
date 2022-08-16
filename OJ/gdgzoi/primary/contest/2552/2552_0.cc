#include <iostream>

const int MAX_N = 1e3 + 10;
const int MOD = 12345;

int dp[MAX_N][MAX_N];

int main()
{
    int n;
    std::cin >> n;

    if (n == 1)
    {
        std::cout << 9;
        return 0;
    }

    dp[1][0] = 9;
    dp[1][1] = 1;

    for (int i = 2; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = ((j != 0 ? dp[i - 1][j - 1] : 0) % MOD + (dp[i - 1][j] * (9 - (i == n))) % MOD) % MOD;

    long long ans = 0;
    for (int i = 0; i <= n; i += 2)
        ans = (ans + dp[n][i]) % MOD;
    std::cout << ans;
    return 0;
}
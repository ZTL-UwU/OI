#include <iostream>

const int MAX_SUM = 5e4 + 10;
const int MAX_MOD = 5e2 + 10;
const int MOD = 1e9 + 7;

int dp[MAX_SUM][MAX_MOD];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int sum, mod;
    std::cin >> sum >> mod;

    dp[0][0] = 1;
    for (int i = 0; i <= sum; i++)
        for (int j = 0; j < mod; j++)
            for (int k = 1; k <= 9; k++)
                dp[i + k][(j * 10 + k) % mod] = (dp[i + k][(j * 10 + k) % mod] + dp[i][j]) % MOD;

    std::cout << dp[sum][0];
    return 0;
}

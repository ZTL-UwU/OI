#include <iostream>
#include <iomanip>

const unsigned long long int QUICK_HUGE_INT = 1e18;
const int MAX_NUM_LEN = 4e3;
const int MAX_N = 5e3 + 10;

unsigned long long int dp[MAX_N][MAX_NUM_LEN];
int num_len = 1;

inline void add(int u)
{
    for (int i = 1; i <= num_len; i++)
        dp[u][i] = dp[u - 1][i] + dp[u][i];

    for (int i = 1; i <= num_len; i++)
    {
        dp[u][i + 1] += dp[u][i] / QUICK_HUGE_INT;
        dp[u][i] %= QUICK_HUGE_INT;
    }

    if (dp[u][num_len + 1] != 0)
        num_len++;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    dp[1][1] = 1;
    for (int i = 2; i <= n + 1; i++)
        for (int j = 1; j <= std::min(i, m + 1); j++)
            add(j);

    std::cout << dp[m + 1][num_len];
    for (int i = num_len - 1; i >= 1; i--)
        std::cout << std::setfill('0') << std::setw(18) << dp[m + 1][i];
    return 0;
}
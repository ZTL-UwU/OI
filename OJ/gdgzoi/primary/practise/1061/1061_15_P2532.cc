#include <iostream>

const int MAX_N = 600;

int dp[MAX_N][MAX_N];
int num_len = 1;

inline void add(int u)
{
    for (int i = 1; i <= num_len; i++)
        dp[u][i] = dp[u - 1][i] + dp[u][i];

    for (int i = 1; i <= num_len; i++)
    {
        dp[u][i + 1] += dp[u][i] / 10;
        dp[u][i] %= 10;
    }

    if (dp[u][num_len + 1] != 0)
        num_len++;
}

int main()
{
    int n;
    std::cin >> n;

    dp[1][1] = 1;
    for (int i = 2; i <= n + 1; i++)
        for (int j = 1; j <= i; j++)
            add(j);

    for (int i = num_len; i >= 1; i--)
        std::cout << dp[n][i];
    return 0;
}
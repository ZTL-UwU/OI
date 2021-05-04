#include <iostream>

const int MAX_N = 1e2;

int dp[MAX_N][MAX_N];
int a[MAX_N];
int b[MAX_N];
int n;

int dfs(int step, int sum_a, int sum_b)
{
    const int diff = std::abs(sum_a - sum_b);

    if (step == n)
        return diff;
    if (dp[step][diff] != -1)
        return dp[step][diff];

    dp[step][diff] =
        std::min(dfs(step + 1, sum_a + a[step], sum_b + b[step]), dfs(step + 1, sum_a + b[step], sum_b + a[step]));
    return dp[step][diff];
}

int main()
{
    std::cin >> n;

    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            dp[i][j] = -1;

    for (int i = 0; i < n; i++)
        std::cin >> a[i] >> b[i];

    std::cout << dfs(0, 0, 0);
    return 0;
}
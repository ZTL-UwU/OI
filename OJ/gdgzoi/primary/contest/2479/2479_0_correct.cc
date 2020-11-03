#include <iostream>

const int MAX_N = 2e4;

int skill[MAX_N];
int dp[MAX_N];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, k;
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
        std::cin >> skill[i];

    for (int i = 1; i <= n; i++)
    {
        int max = -1;
        for (int j = i; j <= std::min(i + k - 1, n); j++)
        {
            max = std::max(max, skill[j]);
            dp[j] = std::max(dp[j], dp[i - 1] + (j - i + 1) * max);
        }
    }

    std::cout << dp[n];
    return 0;
}
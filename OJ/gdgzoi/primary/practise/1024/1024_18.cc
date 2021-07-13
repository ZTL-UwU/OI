#include <iostream>

const int MAX_N = 1e3 + 10;

int dp[MAX_N];
int c[MAX_N];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::cin >> c[i];
        dp[i] = 1;
    }

    for (int i = 1; i < n; i++)
        for (int j = i - 1; j >= 0; j--)
            if (std::abs(c[i] - c[j]) != 1)
                dp[i] = std::max(dp[i], dp[j] + 1);

    std::cout << n - dp[n - 1];
    return 0;
}
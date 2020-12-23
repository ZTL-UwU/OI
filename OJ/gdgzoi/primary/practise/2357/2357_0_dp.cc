#include <cstdint>
#include <iostream>

const int MAX_N = 600;

long long int dp[MAX_N + 10];

inline void get_dp()
{
    dp[0] = 1;

    for (int i = 1; i <= 17; i++)
        for (int j = i * i; j <= MAX_N; j++)
            dp[j] += dp[j - i * i];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    get_dp();

    int n;
    while (std::cin >> n)
    {
        if (n == 0)
            break;

        std::cout << dp[n] << "\n";
    }
    return 0;
}
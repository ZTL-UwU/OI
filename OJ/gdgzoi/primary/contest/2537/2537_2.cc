#include <iostream>
#include <limits.h>

const unsigned long long int INF = ULLONG_MAX;
const int MAX_N = 2e4 + 20;
const int MAX_LOG = 25;

unsigned long long int min[MAX_N][MAX_LOG];
unsigned long long int max[MAX_N][MAX_LOG];
unsigned long long int dp[MAX_N];
int lg[MAX_N];

unsigned long long int get_min(int l, int r)
{
    int k = lg[r - l + 1];
    return std::min(min[l][k], min[r - (1 << k) + 1][k]);
}

unsigned long long int get_max(int l, int r)
{
    int k = lg[r - l + 1];
    return std::max(max[l][k], max[r - (1 << k) + 1][k]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    unsigned long long int k;
    std::cin >> n >> m >> k;

    lg[0] = -1;
    for (int i = 1; i < MAX_N; i++)
        lg[i] = lg[i / 2] + 1;

    for (int i = 1; i <= n; i++)
    {
        unsigned long long int num;
        std::cin >> num;
        min[i][0] = num;
        max[i][0] = num;
    }

    for (int i = 1; i <= MAX_LOG; i++)
    {
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
        {
            min[j][i] = std::min(min[j][i - 1], min[j + (1 << (i - 1))][i - 1]);
            max[j][i] = std::max(max[j][i - 1], max[j + (1 << (i - 1))][i - 1]);
        }
    }

    for (int i = 0; i < MAX_N; i++)
        dp[i] = INF;
    dp[0] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = i - 1; j >= std::max(0, i - m); j--)
            dp[i] = std::min(dp[i], dp[j] + k + (i - j) * (get_max(j + 1, i) - get_min(j + 1, i)));
    std::cout << dp[n];

    return 0;
}

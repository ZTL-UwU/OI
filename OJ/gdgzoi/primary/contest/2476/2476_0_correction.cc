#include <algorithm>
#include <iostream>
#include <climits>

const int MAX_N = 2e3 + 10;

struct vec2
{
    int x;
    int y;
};

long long dp[MAX_N][MAX_N];
vec2 a[MAX_N];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; i++)
        std::cin >> a[i].x >> a[i].y;
    std::sort(a + 1, a + n + 1, [](vec2 a, vec2 b) -> bool { return a.x > b.x; });

    for (int i = 0; i < MAX_N; i++)
        for (int j = 0; j < MAX_N; j++)
            dp[i][j] = -INT_MAX + MAX_N;
    dp[0][1] = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][std::max(j - a[i].x, 0) + 1] + a[i].y);

    long long ans = 0;
    for (int i = 0; i <= n; i++)
        ans = std::max(ans, dp[n][i]);
    std::cout << ans;
    return 0;
}

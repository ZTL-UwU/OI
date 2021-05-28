#include <iostream>
#include <stdio.h>
const int MAXN = 1e3 + 10;
int height[MAXN];
int dp[MAXN];

inline int max_three(int a, int b, int c) { return std::max(a, std::max(b, c)); }

int main()
{
    int c, r;
    std::cin >> c >> r;
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int x, y;
        std::cin >> x >> y;
        height[x] = std::max(height[x], y);
    }

    dp[0] = height[1];
    dp[1] = std::max(height[1], height[2]);
    dp[2] = max_three(height[1], height[2], height[3]);

    for (int i = 3; i <= c; i++)
        dp[i] = std::min(dp[i - 3] + max_three(height[i - 1], height[i], height[i + 1]), dp[i - 1] + height[i + 1]);

    std::cout << dp[c] << "\n";
    return 0;
}
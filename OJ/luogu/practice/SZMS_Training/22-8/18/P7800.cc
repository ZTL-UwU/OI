#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_PAIR = 1e3;
const int MAX_N = 25;
const int MOD = 1e9;

struct segment
{
    int l, r;
};

std::vector<segment> s;
int dp[MAX_PAIR][MAX_N];

int main()
{
    int n;
    std::cin >> n;

    for (int i = 1; i < n; i++)
        for (int j = i + 1; j <= n; j++)
            if (std::__gcd(i, j) == 1)
                s.push_back({i, j});

    std::sort(s.begin(), s.end(), [](segment s1, segment s2) -> bool { return s1.r < s2.r; });

    dp[0][1] = 1;
    for (std::size_t i = 0; i < s.size(); i++)
    {
        for (int j = 1; j <= n; j++)
        {
            const int dp_i = i + 1;
            dp[dp_i][j] = (dp[dp_i][j] + dp[dp_i - 1][j]) % MOD;
            if (s[i].l <= j)
                dp[dp_i][s[i].r] = (dp[dp_i][s[i].r] + dp[dp_i - 1][j]) % MOD;
            else
                dp[dp_i][j] = (dp[dp_i][j] + dp[dp_i - 1][j]) % MOD;
        }
    }

    std::cout << dp[s.size()][n];
    return 0;
}
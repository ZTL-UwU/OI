#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>

const int MAX_N = 4e2;

double p[MAX_N];
int d[MAX_N];

double dp[MAX_N][MAX_N];
double f[MAX_N];

double Pw[MAX_N][MAX_N];

int main()
{
    int T;
    std::cin >> T;

    for (int t = 0; t < T; t++)
    {
        std::memset(dp, 0, sizeof(dp));
        std::memset(f, 0, sizeof(f));

        int n, r;
        std::cin >> n >> r;

        for (int i = 1; i <= n; i++)
            std::cin >> p[i] >> d[i];

        dp[1][0] = std::pow(1 - p[1], r);
        dp[1][1] = 1 - dp[1][0];
        f[1] = dp[1][1];

        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j <= std::min(i, r); j++)
            {
                if (j > 0)
                    // f[i][j] = f[i - 1][j - 1] * (1 - (1 - p[i]) ^ (r - j + 1))  (j != 0) ==> do damage from i
                    dp[i][j] += dp[i - 1][j - 1] * (1 - std::pow(1 - p[i], r - j + 1));
                if (i != j)
                    // f[i][j] = f[i - 1][j] * (1 - p[i]) ^ (r - j)  (i != j) ==> no damage from i
                    dp[i][j] += dp[i - 1][j] * std::pow(1 - p[i], r - j);
            }
        }

        for (int i = 2; i <= n; i++)
            for (int j = 0; j <= std::min(i - 1, r); j++)
                f[i] += dp[i - 1][j] * (1 - std::pow(1 - p[i], r - j));

        double ans = 0;
        for (int i = 1; i <= n; i++)
            ans += f[i] * d[i];

        std::cout << std::fixed << std::setprecision(10) << ans << "\n";
    }

    return 0;
}
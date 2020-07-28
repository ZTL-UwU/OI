#include <iostream>
#include <string.h>
using namespace std;
long long dp[15][15];
inline void bit_dp()
{
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    for (int i = 1; i <= 12; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (j != 4)
            {
                if (j == 6)
                {
                    for (int k = 0; k <= 9; k++)
                        if (k != 2)
                            dp[i][j] += dp[i - 1][k];
                }
                else
                {
                    for (int k = 0; k <= 9; k++)
                        dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }
}
int bit[15];
inline long long solve(int num)
{
    memset(bit, 0, sizeof(bit));
    long long ans = 0;
    int len = 0;
    while (num)
    {
        bit[len++] = num % 10;
        num /= 10;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        for (int j = 0; j < bit[i]; j++)
        {
            if (j == 4 || (bit[i + 1] == 6 && j == 2))
                continue;
            ans += dp[i + 1][j];
        }
        if (bit[i] == 4)
            break;
        if (bit[i] == 2 && bit[i + 1] == 6)
            break;
    }
    return ans;
}
int main()
{
    bit_dp();
    int l, r;
    while (1)
    {
        cin >> l >> r;
        if (!l && !r)
            return 0;
        if (r < l)
            swap(l, r);
        cout << solve(r + 1) - solve(l) << "\n";
    }
    return 0;
}
#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 40;
int dp[MAXN][MAXN];
inline void get_dp()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 35; i++)
    {
        dp[i][0] = dp[i - 1][0];
        for (int j = 1; j <= i; j++)
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
    }
}
int bit[MAXN];
inline long long solve(int num, int k, int b)
{
    long long ans = 0;
    int len = 1;
    while (num)
    {
        bit[len++] = num % b;
        num /= b;
    }
    len--;
    while (len)
    {
        if (bit[len] > 1)
        {
            ans += dp[len - 1][k] + dp[len - 1][k - 1];
            break;
        }
        if (bit[len] == 1)
        {
            ans += dp[len - 1][k];
            k--;
        }
        if (k < 0)
            break;
        len--;
    }
    return ans;
}
int main()
{
    int x, y, k, b;
    cin >> x >> y >> k >> b;
    get_dp();
    cout << solve(y + 1, k, b) - solve(x, k, b) << "\n";
    return 0;
}
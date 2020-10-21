#include <iostream>
#include <string.h>
#include <iomanip>
#include <math.h>
using namespace std;
long long dp[20][20];
inline void get_dp()
{
    for (int i = 0; i <= 9; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= 15; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (abs(k - j) >= 2)
                    dp[i][j] += dp[i - 1][k];
}
int bit[20];
inline long long solve(int num)
{
    int len = 0;
    long long ans = 0;
    while (num)
    {
        bit[len++] = num % 10;
        num /= 10;
    }
    for (int i = 0; i <= len - 2; i++)
        for (int j = 1; j <= 9; j++)
            ans += dp[i + 1][j];
    for (int i = 1; i < bit[len - 1]; i++)
        ans += dp[len][i];
    for (int i = len - 2; i >= 0; i--)
    {
        for (int j = 0; j < bit[i]; j++)
            if (abs(j - bit[i + 1]) >= 2)
                ans += dp[i + 1][j];
        if (abs(bit[i] - bit[i + 1]) < 2)
            break;
        if (!i)
            ans++;
    }
    return ans;
}
int main()
{
    get_dp();
    int l, r;
    cin >> l >> r;
    if (l > r)
        swap(l, r);
    cout << solve(r) - solve(l - 1) << "\n";
    return 0;
}
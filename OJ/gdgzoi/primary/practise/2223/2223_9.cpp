#include <iostream>
#include <string.h>
using namespace std;
int dp[30][20][200];
inline int MOD(int a, int mod)
{
    a %= mod;
    return a < 0 ? a + mod : a;
}
inline void get_dp(int mod)
{
    for (int i = 0; i <= 9; i++)
        dp[1][i][i % mod] = 1;
    for (int i = 2; i <= 20; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k < mod; k++)
                for (int l = 0; l <= 9; l++)
                    dp[i][j][k] += dp[i - 1][l][MOD(k - j, mod)];
}
int bit[30];
inline void solve(int num)
{
    int len = 0;
    while (num)
    {
        bit[len++] = num % 10;
        num /= 10;
    }
    for (int i = 0; i <)
}
int main()
{
    int l, r, mod;
    while (cin >> l >> r >> mod)
    {
        get_dp(mod);
        cout << solve(r + 1) - solve(l);
    }
    return 0;
}
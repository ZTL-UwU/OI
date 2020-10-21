#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;
long long dp[20][20];
void get_dp()
{
    for (int i = 0; i <= 9; i++)
        dp[1][i] = 1;
    for (int i = 2; i <= 15; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = j; k <= 9; k++)
                dp[i][j] += dp[i - 1][k];
}
long long bit[15];
long long solve(int num)
{
    if (!num)
        return 1;
    memset(bit, 0, sizeof(bit));
    int ans = 0;
    int len = 0;
    while (num)
    {
        bit[len++] = num % 10;
        num /= 10;
    }
    int last = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (last > bit[i])
            break;
        for (int j = last; j < bit[i]; j++)
            ans += dp[i + 1][j];
        last = bit[i];
        if (!i)
            ans++;
    }
    return ans;
}
int main()
{
    get_dp();
    int l, r;
    while (cin >> l >> r)
    {
        if (r < l)
            swap(r, l);
        cout << solve(r) - solve(l - 1) << "\n";
    }
    return 0;
}
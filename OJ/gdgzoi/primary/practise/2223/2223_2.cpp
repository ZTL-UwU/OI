#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
long long dp[25][15];
inline void get_dp()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 20; i++)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (j == 4)
                for (int k = 0; k < 9; k++)
                    dp[i][j] += dp[i - 1][k];
            else
                for (int k = 0; k <= 9; k++)
                    dp[i][j] += dp[i - 1][k];
        }
    }
}
int bit[25];
inline long long solve(int num)
{
    memset(bit, 0, sizeof(bit));
    int len = 0;
    long long ans = 0;
    while (num)
    {
        bit[len++] = num % 10;
        num /= 10;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        for (int j = 0; j < bit[i]; j++)
        {
            if (bit[i + 1] == 4 && j == 9)
                continue;
            ans += dp[i + 1][j];
        }
        if (bit[i] == 9 && bit[i + 1] == 4)
            break;
    }
    return ans;
}
int main()
{
    get_dp();
    int t;
    cin >> t;
    while (t--)
    {
        int r;
        cin >> r;
        cout << r - solve(r + 1) + 1 << "\n";
    }
    return 0;
}
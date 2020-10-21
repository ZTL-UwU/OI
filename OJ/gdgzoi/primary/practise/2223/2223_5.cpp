#include <iostream>
#include <string.h>
using namespace std;
int dp[30][30][30];
/*     ^   ^   ^
 *     len|fir|mod
 *     gth|st |13
 */
int dp2[30][30];
inline void get_dp()
{
    for (int i = 0; i <= 12; i++)
        dp[0][0][i] = 1;
    for (int i = 1; i <= 15; i++)
        for (int j = 1; j <= 9; j++)
            for (int k = 0; k <= 12; k++)
                for (int l = 0; l <= 9; l++)
                    for (int m = 0; m <= 12; m++)
                        if (10 * m % 13 == k - l)
                            dp[i][j][k] += dp[i - 1][j][m];
}
int bit[30];
inline int solve(int num)
{
    memset(bit, 0, sizeof(bit));
    int len = 0;
    while (num)
    {
        bit[len++] = num % 10;
        num /= 10;
    }

}
int main()
{
    get_dp();
    int n;
    while (cin >> n)
        cout << solve(n + 1);
    return 0;
}
#include <iostream>
using namespace std;
const int MAXN = 5e2;
int dp[MAXN][MAXN];
int num[MAXN];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
        num[i + n] = num[i];
    }
    int ans = -1;
    for (int i = 1; i < n * 2; i++)
    {
        for (int j = i - 1; i - j < n && j >= 1; j--)
        {
            for (int k = j; k < i; k++)
            {
                dp[j][i] = max(dp[j][i], dp[j][k] + dp[k + 1][i] + num[j] * num[k + 1] * num[i + 1]);
                ans = max(ans, dp[j][i]);
            }
        }
    }
    cout << ans;
    return 0;
}
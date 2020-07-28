#include <iostream>
#include <string.h>
using namespace std;
const int MAXN = 1e3;
int dp[MAXN][MAXN];
int num[MAXN];
int main()
{
    int n;
    cin >> n;
    int nn = n;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        num[i + n] = num[i];
        num[i + n * 2] = num[i];
    }
    n *= 3;
    for (int l = 2; l <= n; l++)
        for (int i = 0; i < n - l; i++)
            for (int j = i + 1; j < i + l - 1; j++)
                dp[i][i + l - 1] = max(dp[i][i + l - 1], dp[i][j] + dp[j][i + l - 1] + (i + 2) * (j + 2) * (i + l));
    cout << dp[nn][nn * 2 - 1];
    return 0;
}
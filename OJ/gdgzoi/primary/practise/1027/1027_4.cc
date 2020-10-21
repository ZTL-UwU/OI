#include <iostream>
#include <string.h>
using namespace std;
const int MAXN = 1e3;
int dp[MAXN][MAXN];
int main()
{
    int n;
    cin >> n;
    int max_page = 0;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        if (y < x)
            swap(x, y);
        max_page = max(max_page, y);
        dp[x][y] = 1;
    }
    int max_len = -1;
    int max_num = -1;
    for (int l = 1; l < max_page; l++)
    {
        for (int i = 1; i <= max_page; i++)
        {
            for (int k = i + 1; k < i + l; k++)
            {
                if (dp[i][k] && dp[k][i + l])
                {
                    dp[i][i + l] = max(dp[i][i + l], dp[i][k] + dp[k][i + l]);
                    if (l + 1 > max_len)
                    {
                        max_len = l + 1;
                        max_num = dp[i][i + l];
                    }
                    else if (l + 1 == max_len)
                        max_num = max(max_num, dp[i][i + l]);
                }
            }
        }
    }
    cout << max_len << " " << max_num;
    return 0;
}
#include <iostream>
#include <string.h>
using namespace std;
int dp[2500][50];
int dis[50][50];
int n;
inline void floyd()
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
}
inline void get_dp()
{
    memset(dp, 127, sizeof(dp));
    dp[1][0] = 0;
    for (int i = 1; i <= (1 << n) - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                if (i == (1 << j))
                    dp[i][j] = dis[0][j];
                else
                {
                    for (int k = 0; k < n; k++)
                        if (i & (1 << k) && j != k)
                            dp[i][j] = min(dp[i][j], dp[i ^ (1 << j)][k] + dis[k][j]);
                }
            }
        }
    }
}
int main()
{
    while (cin >> n)
    {
        memset(dis, 0, sizeof(dis));
        if (!n)
            return 0;
        n++;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> dis[i][j];
        floyd();
        get_dp();
        cout << dp[(1 << n) - 1][0] << "\n";
    }
    return 0;
}
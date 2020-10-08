#include <bits/stdc++.h>
using namespace std;
int n, m, cnt;
int siz;
long long dp[22][1010][410], ans;
int ff[1025], ee[2010];
int cal(int x)
{
    int res = 0;
    while (x)
        res += (x & 1), x >>= 1;
    return res;
}
void init()
{
    for (int i = 0; i <= siz; i++)
        if (!(i & (i << 1)))
        {
            ff[++cnt] = i;
            dp[1][cnt][ee[cnt] = cal(i)] = 1;
        }
}
int main()
{
    scanf("%d%d", &n, &m);
    siz = (1 << n) - 1;
    init();
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= cnt; j++)
        {
            int x = ff[j];
            for (int k = 1; k <= cnt; k++)
            {
                int y = ff[k];
                if (!(x & y) && !(x & (y >> 1)) && !(x & (y << 1)))
                    for (int l = 0; l <= m; l++)
                        dp[i][j][ee[j] + l] += dp[i - 1][k][l];
            }
        }
    }
    for (int i = 1; i <= cnt; i++)
        ans += dp[n][i][m];
    printf("%lld", ans);
    return 0;
}
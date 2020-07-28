#include <iostream>
#include <stdio.h>
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 260;
int f1[MAXN][MAXN][20];
int f2[MAXN][MAXN][20];
int lg[MAXN];
int main()
{
    int n, b, q;
    scanf("%d %d %d", &n, &b, &q);
    for (int i = 1; i <= n; i ++)
    {
        for (int j = 1; j <= n; j ++)
        {
            int tmp;
            scanf("%d", &tmp);
            f1[i][j][0] = tmp;
            f2[i][j][0] = tmp;
        }
    }
    lg[0] = -1;
    for (int i = 1; i < MAXN; i ++) lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= 15; i ++)
    {
        for (int j = 1; j <= n; j ++)
        {
            for (int k = 1; k + (1 << i) - 1 <= n; k ++)
            {
                f1[j][k][i] = max(f1[j][k][i - 1], f1[j][k + (1 << (i - 1))][i - 1]);
                f2[j][k][i] = min(f2[j][k][i - 1], f2[j][k + (1 << (i - 1))][i - 1]);
            }
        }
    }
    for (int i = 0; i < q; i ++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        int minn = INF;
        int maxn = -INF;
        for (int j = 0; j < b; j ++)
        {
            int k = lg[b];
            minn = min(minn, min(f2[x + j][y][k], f2[x + j][y + b - 1 - (1 << k) + 1][k]));
            maxn = max(maxn, max(f1[x + j][y][k], f1[x + j][y + b - 1 - (1 << k) + 1][k]));
        }
        printf("%d\n", maxn - minn);
    }
    return 0;
}
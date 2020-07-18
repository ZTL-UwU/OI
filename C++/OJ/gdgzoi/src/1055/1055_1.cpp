#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 100010;
int f1[MAXN][30];
int f2[MAXN][30];
int lg[MAXN];
int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i ++)
    {
        int tmp;
        scanf("%d", &tmp);
        f1[i][0] = tmp;
        f2[i][0] = tmp;
    }
    lg[0] = -1;
    for (int i = 1; i < MAXN; i ++) lg[i] = lg[i / 2] + 1;
    for (int i = 1; i < 25; i ++)
    {
        for (int j = 1; j + (1 << i) - 1 <= n; j ++)
        {
            f1[j][i] = min(f1[j][i - 1], f1[j + (1 << (i - 1))][i - 1]);
            f2[j][i] = max(f2[j][i - 1], f2[j + (1 << (i - 1))][i - 1]);
        }
    }
    for (int i = 1; i <= n - k + 1; i ++)
    {
        int l = i, r = i + k - 1;
        int tmp = lg[r - l + 1];
        int res1 = min(f1[l][tmp], f1[r - (1 << tmp) + 1][tmp]);
        int res2 = max(f2[l][tmp], f2[r - (1 << tmp) + 1][tmp]);
        printf("%d %d\n", res2, res1);
    }
    return 0;
}
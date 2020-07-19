#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 600000;
int f1[MAXN][30];
int f2[MAXN][30];
int lg[MAXN];
int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i ++)
    {
        int tmp;
        scanf("%d", &tmp);
        f1[i][0] = tmp;
        f2[i][0] = tmp;
    }
    lg[0] = -1;
    for (int i = 1; i <= MAXN; i ++) lg[i] = lg[i / 2] + 1;
    for (int i = 1; i < 25; i ++)
    {
        for (int j = 1; j + (1 << i) - 1 <= n; j ++)
        {
            f1[j][i] = max(f1[j][i - 1], f1[j + (1 << (i - 1))][i - 1]);
            f2[j][i] = min(f2[j][i - 1], f2[j + (1 << (i - 1))][i - 1]);
        }
    }
    for (int i = 0; i < q; i ++)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        int k = lg[r - l + 1];
        int res = max(f1[l][k], f1[r - (1 << k) + 1][k]) - min(f2[l][k], f2[r - (1 << k) + 1][k]);
        printf("%d\n", res);
    }
    return 0;
}
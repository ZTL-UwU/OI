#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 100100;
int lg[MAXN];
int f[MAXN][21];
int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    lg[0] = -1;
    for (int i = 1; i <= MAXN; i ++) lg[i] = lg[i / 2] + 1;
    for (int i = 1; i <= n; i ++)
    {
        int tmp;
        scanf("%d", &tmp);
        f[i][0] = tmp;
    }
    for (int i = 1; i <= 20; i ++)
        for (int j = 1; j + (1 << i) - 1 <= n; j ++)
            f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
    for (int i = 0; i < q; i ++)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        int k = lg[r - l + 1];
        int res = max(f[l][k], f[r - (1 << k) + 1][k]);
        printf("%d\n", res);
    }
    return 0;
}
#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 200100;
int f[MAXN][30];
int lg[MAXN];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        f[i][0] = tmp;
    }
    lg[0] = -1;
    for (int i = 1; i < MAXN; i++)
        lg[i] = lg[i / 2] + 1;
    for (int i = 1; i < 25; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        int k = lg[y - x + 1];
        int res = max(f[x][k], f[y - (1 << k) + 1][k]);
        printf("%d\n", res);
    }
    return 0;
}
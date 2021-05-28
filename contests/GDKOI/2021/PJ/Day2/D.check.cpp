#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000;
int a[maxn + 5][maxn + 5];
int b[maxn + 5][maxn + 5];
int d[maxn + 5][maxn + 5];
long long r[maxn + 5], c[maxn + 5];
int main()
{
    freopen("matrix.in", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            r[i] += a[i][j];
            c[i] += a[j][i];
        }
    }
    freopen("matrix.out", "r", stdin);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &b[i][j]);
            if (b[i][j] < 0 || b[i][j] > a[i][j])
            {
                printf("WA1\n");
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            r[i] -= 2ll * b[i][j];
            c[i] -= 2ll * b[j][i];
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (r[i] != 0 || c[i] != 0)
        {
            printf("WA2\n");
            return 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &d[i][j]);
            if (b[i][j] + d[i][j] != a[i][j])
            {
                printf("WA3\n");
                return 0;
            }
        }
    }
    printf("AC\n");
}
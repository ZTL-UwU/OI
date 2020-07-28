#include <cstdio>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn = 550, INF = 1e9 + 1;
int a[maxn][maxn], d[maxn];
//d[i]表示到i的最长路
int main()
{
    int n, i, j, end = 0, ans1 = 0, ans2, path[maxn];
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        a[x][y] = y - x + 1;
        end = max(end, y);
    }
    memset(d, 0, sizeof(d));
    memset(path, 0, sizeof(path));
    for (i = 0; i <= end; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (a[j][i])
            {
                if (d[j] != 0)
                {
                    if (d[i] < d[j] + a[j][i])
                    {
                        d[i] = d[j] + a[j][i] - 1;
                        path[i] = j;
                    }
                }
                else
                {
                    d[i] = max(d[i], a[j][i]);
                }
            }
        }
    }
    //求最长路
    int a, b;
    ans2 = 1;
    for (i = 0; i <= end; i++)
    {
        if (d[i] > ans1)
            ans1 = d[i];
    }
    //同长的情况下求最长页段
    for (i = 0; i <= end; i++)
    {
        if (d[i] == ans1)
        {
            b = 1, a = i;
            while (path[a] != 0)
            {
                b++;
                a = path[a];
            }
            ans2 = max(ans2, b);
        }
    }
    printf("%d %d\n", ans1, ans2);
    return 0;
}
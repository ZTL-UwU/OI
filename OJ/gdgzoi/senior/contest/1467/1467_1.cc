#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;
int mp[501][501];
int s[250010];
int main()
{
    int n, q, i, j, ii, x1, y1, x2, y2, k, num;
    scanf("%d%d", &n, &q);
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &mp[i][j]);
    for (ii = 0; ii < q; ++ii)
    {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &k);
        for (i = x1 - 1; i <= x2 - 1; ++i)
            for (j = y1 - 1; j <= y2 - 1; ++j)
                s[num++] = mp[i][j];
        sort(s, s + num);
        printf("%d\n", s[k - 1]);
        num = 0;
    }
    return 0;
}
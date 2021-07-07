#include <iostream>
#include <queue>
#include <stdio.h>
using namespace std;
int a[300001];
int f[300001];
int _time[300001];
int r = 0;
int m = 0;
int main()
{
    int t;
    scanf("%d", &t);
    int ans = 0;
    for (int i = 0; i < t; i++)
    {
        int t, k;
        scanf("%d %d", &t, &k);
        for (int j = 0; j < k; j++)
        {
            _time[++m] = t;
            scanf("%d", &a[m]);
            if (!f[a[m]])
                ans++;
            f[a[m]]++;
        }
        while (t - _time[r] >= 86400)
        {
            if (!--f[a[r]])
                ans--;
            r++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
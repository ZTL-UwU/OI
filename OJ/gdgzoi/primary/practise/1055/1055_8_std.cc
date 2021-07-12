#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n, m, cnt = 0;
int num[500000], l[500000], r[500000], val[500000];
int f[20][500000];
void Clear()
{
    cnt = 0;
    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));
    memset(f, 0, sizeof(f));
    memset(num, 0, sizeof(num));
    memset(val, 0, sizeof(val));
}
int main()
{
    while (1)
    {
        Clear();
        scanf("%d", &n);
        if (!n)
            break;
        scanf("%d", &m);
        int tmp = -1123645162; //这是乱打的，只要保证第一个x不等于tmp就行。。
        for (int i = 1; i <= n; i++)
        {
            int x;
            scanf("%d", &x);
            if (x != tmp)
                r[cnt] = i - 1, l[++cnt] = i, tmp = x;
            num[i] = cnt; //处理各个数组
        }
        for (int i = 1; i <= cnt; i++)
            f[0][i] = r[i] - l[i] + 1; //预处理f数组
        for (int i = 1; (1 << i) <= cnt; i++)
            for (int j = 1; j <= n - (1 << i) + 1; j++)
                f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
        // ST表求RMQ
        for (int i = 1; i <= m; i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (x > y)
                swap(x, y);
            if (num[x] == num[y])
                printf("%d\n", y - x + 1); //如果刚好在一段里，那么直接减一下输出
            else
            {
                int ans = 0;
                if (num[x] + 1 <= num[y] - 1)
                {
                    int L = num[x] + 1, R = num[y] - 1;
                    int k = 0;
                    while ((1 << (k + 1)) <= R - L + 1)
                        k++;
                    ans = max(f[k][L], f[k][R - (1 << k) + 1]);
                }
                ans = max(ans, max(r[num[x]] - x + 1, y - l[num[y]] + 1));
                //在三段中取最大
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}
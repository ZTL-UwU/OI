#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;
const int MAXN = 2e6 + 2;
vector<int> v[5371];
int rmq[MAXN][22];
int main()
{
    int n, k, p;
    scanf("%d %d %d", &n, &k, &p);
    for (int i = 1; i <= n; i ++)
    {
        int col, money;
        scanf("%d %d", &col, &money);
        v[col].push_back(i);
        rmq[i][0] = money;
    }
    int tmp = log2(n);
    for (int i = 1; i < tmp; i ++)
        for (int j = 1; j + (1 << i) - 1 <= n; j ++)
            rmq[j][i] = min(rmq[j][i - 1], rmq[j + (1 << (i - 1))][i - 1]);
    int ans = 0;
    for (int i = 0; i < k; i ++)
    {
        for (int j = 0; j < v[i].size() - 1; j ++)
        {
            int l = v[i][j];
            for (int x = j + 1; x < v[i].size(); x ++)
            {
                int r = v[i][x];
                int k = log2(r - l + 1);
                int res = min(rmq[l][k], rmq[r - (1 << k) + 1][k]);
                if (res <= p)
                {
                    ans += v[i].size() - x;
                    break;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
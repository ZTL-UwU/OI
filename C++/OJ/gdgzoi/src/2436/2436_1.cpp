#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
const int INF = 0x7fffffff;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
unsigned long long ans = 0;
unsigned long long maxn_num = -INF;
int n;
void dfs(int k, int last, unsigned long long fac, unsigned long long num)
{
    if (fac > n) return;
    if (num > maxn_num) maxn_num = num;
    if (k == 10)
    {
        if (num == maxn_num) ans = min(ans, fac);
        if (num > maxn_num) ans = fac;
        return;
    }
    for (int i = 0; i <= i; i ++) dfs(k + 1, i, fac *= prime[k], num * (i + 1));
}
int main()
{
    cin >> n;
    dfs(0, 31, 1, 1);
    cout << ans;
    return 0;
}
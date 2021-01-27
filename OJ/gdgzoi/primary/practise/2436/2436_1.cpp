#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
const int INF = 0x7fffffff;
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
unsigned long long ans = INF;
unsigned long long maxn_num;
int n;
void dfs(int k, int last, unsigned long long fac, unsigned long long num)
{
    if (fac > n)
        return;
    if (k == 10)
    {
        if (num == maxn_num)
            ans = min(ans, fac);
        if (num > maxn_num)
            ans = fac, maxn_num = num;
        return;
    }
    int tmp = 1;
    for (int i = 0; i <= last; i++)
        dfs(k + 1, i, fac * tmp, num * (i + 1)), tmp *= prime[k];
}
int main()
{
    cin >> n;
    dfs(0, 31, 1, 1);
    cout << ans << "\n";
    return 0;
}
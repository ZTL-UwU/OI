#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 10000;
int dp[MAXN];
int f[MAXN];
int get_sum(int k)
{
    int res = 0;
    for (int i = 1; i < k; i ++)
        if (k % i == 0) res += i;
    return res;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i ++)
        for (int j = n; j >= i; j --)
            dp[j] = max(dp[j], dp[j - i] + get_sum(i));
    cout << dp[n];
    return 0;
}
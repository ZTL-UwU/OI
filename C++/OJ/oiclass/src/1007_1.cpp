#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 10000;
int w[MAXN];
int v[MAXN];
int dp[MAXN];
int main()
{
    int val, n;
    cin >> val >> n;
    for (int i = 0; i < n; i ++)
    {
        cin >> w[i] >> v[i];
        v[i] *= w[i];
    }
    for (int i = 0; i < n; i ++)
        for (int j = val; j >= w[i]; j --)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    cout << dp[val];
    return 0;
}
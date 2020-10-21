#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 20000;
int v[MAXN];
int w[MAXN];
int dp[MAXN];
int main()
{
    int val, n;
    cin >> val >> n;
    for (int i = 0; i < n; i ++) cin >> v[i] >> w[i];
    for (int i = 0; i < n; i ++)
        for (int j = w[i]; j <= val; j ++)
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    cout << dp[val];
    return 0;
}
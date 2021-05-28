#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 10000;
int v[MAXN];
int dp[MAXN];
int main()
{
    int val, n;
    cin >> val >> n;
    for (int i = 0; i < n; i++)
        cin >> v[i];
    for (int i = 0; i < n; i++)
        for (int j = v[i]; j <= val; j++)
            dp[j] = max(dp[j], dp[j - v[i]] + v[i]);
    cout << dp[val];
    return 0;
}
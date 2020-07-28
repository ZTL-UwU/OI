#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 3000;
int num[MAXN];
int v[MAXN];
int w[MAXN];
int dp[MAXN];
int main()
{
    int n, val;
    cin >> n >> val;
    for (int i = 0; i < n; i ++)
        cin >> num[i] >> w[i] >> v[i];
    for (int i = 0; i < n; i ++)
    {
        for (int j = val; j >= 0; j --)
        {
            for (int k = 0; k <= min(num[i], val / w[i]); k ++)
            {
                if (j - k * w[i] >= 0) dp[j] = max(dp[j], dp[j - k * w[i]] + v[i] * k);
            }
        }
    }
    cout << dp[val];
    return 0;
}
#include <iostream>
#include <math.h>
using namespace std;
const int MAXN = 2e3;
int mm[MAXN];
int dp[MAXN];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> mm[i];
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++)
            if (abs(mm[i] - mm[j]) != 1)
                dp[i] = max(dp[i], dp[j] + 1);
    }
    int maxn = -1;
    for (int i = 0; i < n; i++)
        maxn = max(maxn, dp[i]);
    cout << n - maxn << "\n";
    return 0;
}
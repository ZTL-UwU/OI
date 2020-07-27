#include <algorithm>
#include <iostream>
using namespace std;
struct data
{
    int l, r;
};
bool cmp(data a, data b)
{
    return a.r < b.r;
}
const int MAXN = 2e3;
data rules[MAXN];
int dp[MAXN];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> rules[i].l >> rules[i].r;
    sort(rules, rules + n, cmp);
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        for (int j = 0; j < i; j++)
            if (rules[j].r <= rules[i].l)
                dp[i] = max(dp[i], dp[j] + 1);
    }
    int maxn = -1;
    for (int i = 0; i < n; i++)
        maxn = max(maxn, dp[i]);
    cout << maxn;
    return 0;
}
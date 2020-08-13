#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const long long MAXN = 2e5 + 10;
long long tree[MAXN];
long long y[MAXN];
long long a[MAXN];
long long b[MAXN];
long long c[MAXN];
long long d[MAXN];
long long n;
inline long long lowbit(long long x) { return x & -x; }
inline long long sum(long long u)
{
    long long ans = 0;
    while (u > 0)   
    {
        ans += tree[u];
        u -= lowbit(u);
    }
    return ans;
}
inline void add(long long u, long long val)
{
    while (u <= n)
    {
        tree[u] += val;
        u += lowbit(u);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (long long i = 0; i < n; i++)
        cin >> y[i];
    for (long long i = 0; i < n; i++)
    {
        a[i] = sum(y[i] - 1);
        b[i] = sum(n) - sum(y[i]);
        add(y[i], 1);
    }
    memset(tree, 0, sizeof(tree));
    long long ans1 = 0;
    long long ans2 = 0;
    for (long long i = n - 1; i >= 0; i--)
    {
        c[i] = sum(y[i] - 1);
        d[i] = sum(n) - sum(y[i]);
        add(y[i], 1);
        ans1 += a[i] * c[i];
        ans2 += b[i] * d[i];
    }
    cout << ans2 << " " << ans1;
    return 0;
}
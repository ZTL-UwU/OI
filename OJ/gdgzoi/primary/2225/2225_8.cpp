#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
typedef long long ll;
const ll MAXN = 10000;
ll a[MAXN];
ll m[MAXN];
ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}
void exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return;
    }
    exgcd(b, a % b, x, y);
    ll tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}
int main()
{
    ll n;
    scanf("%d", &n);
    ll ans = 0;
    ll M = 1;
    for (ll i = 0; i < n; i ++)
    {
        scanf("%d %d", &m[i], &a[i]);
        M *= m[i];
    }
    for (ll i = 0; i < n; i ++)
    {
        ll Mi = M / m[i], Mi_1;
        ll y;
        ll g = gcd(Mi, m[i]);
        exgcd(Mi, m[i], Mi_1, y);
        while (Mi_1 < 0) Mi_1 += m[i] / g;
        ans += a[i] * Mi * Mi_1;
    }
    printf("%lld\n", ans % M);
    return 0;
}
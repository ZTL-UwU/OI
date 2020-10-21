#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
typedef long long ll;
const int MOD = 9973;
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
    int t;
    ll n, b;
    scanf("%d", &t);
    while (t --)
    {
        scanf("%lld %lld", &n, &b);
        ll x, y;
        // x = A/B
        // y = A/9973
        // Bx + 9973y = n
        exgcd(b, MOD, x, y);
        while (x < 0) x += MOD;
        x *= n;
        x %= MOD;
        printf("%lld\n", x);
    }
    return 0;
}
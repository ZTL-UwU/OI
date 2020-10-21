#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
typedef long long ll;
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
    ll tmp;
    tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}
int main()
{
    ll a, m;
    while (~scanf("%lld %lld", &a, &m))
    {
        ll g = gcd(a, m);
        ll x, y;
        exgcd(a, m, x, y);
        while (x < 0) x += m / g;
        printf("%lld\n", x);
    }
    return 0;
}
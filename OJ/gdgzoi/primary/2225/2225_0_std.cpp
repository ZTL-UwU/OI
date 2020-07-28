#include <cstdio>
#include <cctype>
#include <iostream>
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
    ll temp;
    temp = x;
    x = y;
    y = temp - (a / b) * y;
    return;
}
int main()
{
    ll A, B, C, k;
    while (cin >> A >> B >> C >> k)
    {
        if (A == B && B == C && C == k && A == 0)
            return 0;
        ll x, y;
        ll a = C, b = (ll)1 << k, c = B - A;
        if (!c)
        {
            printf("0\n");
            continue;
        }
        ll g = gcd(a, b);
        if (c % g)
        {
            printf("FOREVER\n");
            continue;
        }
        a /= g;
        b /= g;
        c /= g;
        exgcd(a, b, x, y);
        x = (x % b * c % b + b) % b;
        printf("%lld\n", x);
    }
    return 0;
}
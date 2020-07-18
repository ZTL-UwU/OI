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
    ll A, B, C, k;
    while (1)
    {
        cin >> A >> B >> C >> k;
        if ((!A) && (!B) && (!C) && (!k)) return 0;
        ll a = C, b = (ll)1 << k, c = B - A; //ax + by = c
        if (!c)
        {
            cout << "0\n";
            continue;
        }
        ll g = gcd(a, b);
        if (c % g)
        {
            cout << "FOREVER\n";
            continue;
        }
        a /= g;
        b /= g;
        c /= g;
        ll x, y;
        exgcd(a, b, x, y);
        x = (x % b * c % b + b) % b;
        cout << x << "\n";
    }
    return 0;
}
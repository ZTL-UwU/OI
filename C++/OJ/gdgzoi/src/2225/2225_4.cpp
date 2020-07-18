#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll;
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll ret = exgcd(b, a % b, x, y);
    ll tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ret;
}
int main()
{
    ll x, y, m, n, l;
    while (~scanf("%lld %lld %lld %lld %lld", &x, &y, &m, &n, &l))
    {
        ll a, b;
        ll A = n - m, B = x - y;
        if (A < 0)
        {
            A = -A;
            B = -B;
        }
        ll g = exgcd(A, l, a, b);
        cout << a << " " << b << " " << A << " " << B << " " << g << "\n";
        if (B % g)
        {
            printf("Impossible\n");
            continue;
        }
        cout << ((a * (B / g)) % (l / g) + (l / g)) % (l / g);
        // printf("%lld\n", ans);
    }
    return 0;
}
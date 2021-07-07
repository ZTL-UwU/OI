#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;
ll ans, x1, y1;

ll exgcd(ll a, ll A, ll &x1, ll &y1)
{
    if (!A)
    {
        x1 = 1;
        y1 = 0;
        return a;
    }
    ans = exgcd(A, a % A, x1, y1);
    ll t = x1;
    x1 = y1;
    y1 = t - a / A * y1;
    return ans;
}

int main()
{
    ll n, m, x, y, l;
    cin >> x >> y >> m >> n >> l;
    ll A = n - m, B = x - y;
    if (A < 0)
    {
        A = -A;
        B = -B;
    } //处理负数
    exgcd(A, l, x1, y1);
    cout << x1 << " " << y1 << " " << A << " " << B << " " << ans << "\n";
    if (B % ans != 0) //判断方程有无解。
        cout << "Impossible";
    else
        cout << ((x1 * (B / ans)) % (l / ans) + (l / ans)) % (l / ans); //处理负数
}
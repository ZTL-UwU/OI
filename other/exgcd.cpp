#include <bits/stdc++.h>
using namespace std;
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
    int a, b, c;
    exgcd(a, b);
    cout << 
    return 0;
}
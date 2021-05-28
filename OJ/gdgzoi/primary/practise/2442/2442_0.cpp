#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
typedef long long ll;
const int MAXN = 1e5 + 10;
ll ans[MAXN];
ll tree[MAXN];
ll lowbit(ll x) { return x & (-x); }
void add(ll x, ll num)
{
    while (x < MAXN)
    {
        tree[x] += num;
        x += lowbit(x);
    }
}
ll query(ll x)
{
    ll sum = 0;
    while (x > 0)
    {
        sum += tree[x];
        x -= lowbit(x);
    }
    return sum;
}
int main()
{
    ll n;
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        ll a;
        cin >> a;
        a++;
        ans[a] += i - query(a);
        add(a, 1);
    }
    ll tmp = 0;
    for (ll i = 1; i <= n; i++)
    {
        cout << tmp << "\n";
        tmp += ans[i];
    }
    return 0;
}
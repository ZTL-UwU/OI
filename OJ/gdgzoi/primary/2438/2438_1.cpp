#include <iostream>
#include <stdio.h>
using namespace std;
const int MAXN = 2500000;
typedef long long ll;
ll tree[MAXN];
ll add[MAXN];
void update(ll l, ll r, ll k, ll a, ll b, ll val)
{
    if (l >= a && r <= b)
    {
        tree[k] += val;
        add[k] += val;
        return;
    }
    ll mid = (l + r) >> 1;
    ll ls = k << 1, rs = k << 1 | 1;
    if (a <= mid)
        update(l, mid, ls, a, b, val);
    if (b > mid)
        update(mid + 1, r, rs, a, b, val);
    tree[k] = max(tree[ls], tree[rs]) + add[k];
}
inline ll query(ll l, ll r, ll k, ll a, ll b, ll addon)
{
    if (l >= a && r <= b)
        return tree[k] + addon;
    ll mid = (l + r) >> 1;
    ll ls = k << 1, rs = k << 1 | 1;
    ll tmp = -0x7fffffff;
    if (a <= mid)
        tmp = max(tmp, query(l, mid, ls, a, b, addon + add[k]));
    if (b > mid)
        tmp = max(tmp, query(mid + 1, r, rs, a, b, addon + add[k]));
    return tmp;
}
int main()
{
    ll c, s, r;
    scanf("%lld %lld %lld", &c, &s, &r);
    for (int i = 0; i < r; i ++)
    {
        ll o, d, n;
        scanf("%lld %lld %lld", &o, &d, &n);
        d--;
        if (query(1, c, 1, o, d, 0) + n <= s)
        {
            update(1, c, 1, o, d, n);
            puts("YES");
        }
        else
            put("NO");
    }
    return 0;
}
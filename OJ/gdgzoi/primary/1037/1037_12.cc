#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;
long long Tree[4000000];
long long add[4000000];
void build(long long l, long long r, long long k)
{
    if (l == r)
    {
        cin >> Tree[k];
        return;
    }
    long long mid = (l + r) >> 1;
    long long ls = k << 1, rs = k << 1 | 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    Tree[k] = min(Tree[ls], Tree[rs]);
}
void update(long long l, long long r, long long k, long long a, long long b, long long val)
{
    if (l >= a && r <= b)
    {
        Tree[k] -= val;
        add[k] -= val;
        return;
    }
    long long mid = (l + r) >> 1;
    long long ls = k << 1, rs = k << 1 | 1;
    if (a <= mid)
        update(l, mid, ls, a, b, val);
    if (b > mid)
        update(mid + 1, r, rs, a, b, val);
    Tree[k] = min(Tree[ls], Tree[rs]) + add[k];
}
inline long long query(long long l, long long r, long long k, long long a, long long b, long long addon)
{
    if (l >= a && r <= b)
        return Tree[k] + addon;
    long long mid = (l + r) >> 1;
    long long ls = k << 1, rs = k << 1 | 1;
    long long tmp = 0x7fffffff;
    if (a <= mid)
        tmp = min(tmp, query(l, mid, ls, a, b, addon + add[k]));
    if (b > mid)
        tmp = min(tmp, query(mid + 1, r, rs, a, b, addon + add[k]));
    return tmp;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n, m;
    cin >> n >> m;
    build(1, n, 1);
    for (int i = 1; i <= m; i++)
    {
        long long x, y, val;
        cin >> val >> x >> y;
        if (query(1, n, 1, x, y, 0) >= val)
        {
            update(1, n, 1, x, y, val);
        }
        else
        {
            cout << "-1\n";
            cout << i;
            return 0;
        }
    }
    cout << 0;
    return 0;
}
#include <iostream>
#include <stdio.h>
using namespace std;
const long long MAXN = 4e5 + 10;
long long num[MAXN];
long long tag[MAXN];
long long st[MAXN];
inline void commit(long long l, long long r, long long k, long long val)
{
    st[k] += (r - l + 1) * val;
    tag[k] += val;
}
inline void push_up(long long k)
{
    st[k] = st[k * 2] + st[k * 2 + 1];
}
inline void push_down(long long l, long long r, long long k)
{
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    commit(l, mid, ls, tag[k]);
    commit(mid + 1, r, rs, tag[k]);
    tag[k] = 0;
}
inline void build(long long l, long long r, long long k)
{
    if (l == r)
    {
        st[k] = num[l];
        return;
    }
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    push_up(k);
}
inline void update(long long l, long long r, long long k, long long x, long long y, long long val)
{
    if (x <= l && r <= y)
    {
        commit(l, r, k, val);
        return;
    }
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    push_down(l, r, k);
    if (x <= mid)
        update(l, mid, ls, x, y, val);
    if (y > mid)
        update(mid + 1, r, rs, x, y, val);
    push_up(k);
}
inline long long query(long long l, long long r, long long k, long long x, long long y)
{
    if (x <= l && r <= y)
        return st[k];
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    push_down(l, r, k);
    long long sum = 0;
    if (x <= mid)
        sum += query(l, mid, ls, x, y);
    if (y > mid)
        sum += query(mid + 1, r, rs, x, y);
    return sum;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long n, q;
    cin >> n >> q;
    for (long long i = 1; i <= n; i++)
        cin >> num[i];
    build(1, n, 1);
    while (q--)
    {
        long long type;
        cin >> type;
        if (type == 1)
        {
            long long x, y, val;
            cin >> x >> y >> val;
            update(1, n, 1, x, y, val);
        }
        if (type == 2)
        {
            long long x, y;
            cin >> x >> y;
            cout << query(1, n, 1, x, y) << "\n";
        }
    }
    return 0;
}
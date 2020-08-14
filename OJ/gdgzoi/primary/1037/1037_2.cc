#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const long long MAXN = 5e5 + 10;
struct seg_tree
{
    long long sum;
    long long lmax;
    long long rmax;
    long long maxx;
    #define st(x) tree[x].sum
    #define lm(x) tree[x].lmax
    #define rm(x) tree[x].rmax
    #define m(x) tree[x].maxx
} tree[MAXN * 4];
long long score[MAXN];
inline void push_up(long long k)
{
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    st(k) = st(ls) + st(rs);
    lm(k) = max(st(ls) + lm(rs), lm(ls));
    rm(k) = max(st(rs) + rm(ls), rm(rs));
    m(k) = max(max(m(ls), m(rs)), rm(ls) + lm(rs));
}
inline void build(long long l, long long r, long long k)
{
    if (l == r)
    {
        st(k) = score[l];
        lm(k) = score[l];
        rm(k) = score[l];
        m(k) = score[l];
        return;
    }
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    push_up(k);
}
inline void update(long long l, long long r, long long k, long long x, long long val)
{
    if (l == r)
    {
        st(k) = val;
        lm(k) = val;
        rm(k) = val;
        m(k) = val;
        return;
    }
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    if (x <= mid)
        update(l, mid, ls, x, val);
    else
        update(mid + 1, r, rs, x, val);
    push_up(k);
}
seg_tree query(long long l, long long r, long long k, long long x, long long y)
{
    if (x <= l && r <= y)
        return tree[k];
    long long mid = (l + r) / 2;
    long long ls = k * 2;
    long long rs = k * 2 + 1;
    if (y <= mid)
        return query(l, mid, ls, x, y);
    if (x > mid)
        return query(mid + 1, r, rs, x, y);
    seg_tree L = query(l, mid, ls, x, y);
    seg_tree R = query(mid + 1, r, rs, x, y);
    seg_tree re;
    re.sum = L.sum + R.sum;
    re.lmax = max(L.sum + R.lmax, L.lmax);
    re.rmax = max(R.sum + L.rmax, R.rmax);
    re.maxx = max(max(L.maxx, R.maxx), L.rmax + R.lmax);
    return re;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    long long n, q;
    cin >> n >> q;
    for (long long i = 1; i <= n; i++)
        cin >> score[i];
    build(1, n, 1);
    while (q--)
    {
        long long type;
        cin >> type;
        if (type == 1)
        {
            long long x, y;
            cin >> x >> y;
            if (x > y)
                swap(x, y);
            cout << query(1, n, 1, x, y).maxx << "\n";
        }
        else
        {
            long long x, val;
            cin >> x >> val;
            update(1, n, 1, x, val);
        }
    }
    return 0;
}
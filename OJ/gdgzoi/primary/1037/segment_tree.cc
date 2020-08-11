#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const int MAXN = 1e5 + 10;
long long add[MAXN * 4];
long long st[MAXN * 4];
inline void build(int l, int r, int k)
{
    if (l == r)
    {
        cin >> st[k];
        return;
    }
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    build(l, mid, ls);
    build(mid + 1, r, rs);
    st[k] = st[ls] + st[rs];
}
inline void update(int l, int r, int k, int x, int y, long long val)
{
    if (l >= x && r <= y)
    {
        add[k] += val;
        return;
    }
    st[k] += (min(r, y) - max(l, x) + 1) * val;
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    if (x <= mid)
        update(l, mid, ls, x, y, val);
    if (y > mid)
        update(mid + 1, r, rs, x, y, val);
}
inline long long query(int l, int r, int k, int x, int y)
{
    if (l >= x && r <= y)
        return st[k] + (r - l + 1) * add[k];
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    long long sum = (min(r, y) - max(l, x) + 1) * add[k];
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
    int n, q;
    cin >> n >> q;
    build(1, n, 1);
    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int x, y;
            long long val;
            cin >> x >> y >> val;
            update(1, n, 1, x, y, val);
        }
        else
        {
            int x, y;
            cin >> x >> y;
            cout << query(1, n, 1, x, y) << "\n";
        }
    }
    return 0;
}
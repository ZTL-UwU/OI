#include <bits/stdc++.h>

#include <dbg.h>
using namespace std;

#define int long long

int n;
int val[200010];

struct node
{
    int minn;
    int maxn;
    int sumn;
    int lazt; // plus
};
node t[800010];

inline int lson(int o) { return o << 1; }
inline int rson(int o) { return (o << 1) | 1; }
void push_up(int u)
{
    t[u].sumn = t[lson(u)].sumn + t[rson(u)].sumn;
    t[u].minn = min(t[lson(u)].minn, t[rson(u)].minn);
    t[u].maxn = max(t[lson(u)].maxn, t[rson(u)].maxn);
}
void push_down(int u, int l, int r)
{
    if (!t[u].lazt)
    {
        return;
    }
    int mid = (l + r) >> 1;
    t[lson(u)].sumn += (mid - l + 1) * t[u].lazt;
    t[rson(u)].sumn += (r - mid) * t[u].lazt;
    t[lson(u)].minn += t[u].lazt;
    t[rson(u)].minn += t[u].lazt;
    t[lson(u)].maxn += t[u].lazt;
    t[rson(u)].maxn += t[u].lazt;
    t[lson(u)].lazt += t[u].lazt;
    t[rson(u)].lazt += t[u].lazt;
    t[u].lazt = 0;
    return;
}
void build(int u, int l, int r)
{
    if (l == r)
    {
        t[u].sumn = val[l];
        t[u].minn = val[l];
        t[u].maxn = val[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(lson(u), l, mid);
    build(rson(u), mid + 1, r);
    push_up(u);
}
void plus_update(int u, int l, int r, int a, int b, int k)
{
    if (a <= l && b >= r)
    {
        t[u].sumn += (r - l + 1) * k;
        t[u].lazt += k;
        t[u].minn += k;
        t[u].maxn += k;
        return;
    }
    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (a <= mid)
    {
        plus_update(lson(u), l, mid, a, b, k);
    }
    if (b > mid)
    {
        plus_update(rson(u), mid + 1, r, a, b, k);
    }
    push_up(u);
}
void div_update(int u, int l, int r, int a, int b, int k)
{
    if (a <= l && b >= r && t[u].maxn - floor((double)t[u].maxn / k) == t[u].minn - floor((double)t[u].minn / k))
    {
        int tmp = t[u].minn - floor((double)t[u].minn / k);
        dbg(tmp);
        t[u].sumn -= (r - l + 1) * tmp;
        t[u].lazt -= tmp;
        t[u].minn -= tmp;
        t[u].maxn -= tmp;
        return;
    }
    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (a <= mid)
    {
        div_update(lson(u), l, mid, a, b, k);
    }
    if (b > mid)
    {
        div_update(rson(u), mid + 1, r, a, b, k);
    }
    push_up(u);
}
int sum_query(int u, int l, int r, int a, int b)
{
    if (a <= l && b >= r)
    {
        return t[u].sumn;
    }
    push_down(u, l, r);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (a <= mid)
    {
        ans += sum_query(lson(u), l, mid, a, b);
    }
    if (b > mid)
    {
        ans += sum_query(rson(u), mid + 1, r, a, b);
    }
    return ans;
}
int min_query(int u, int l, int r, int a, int b)
{
    if (a <= l && b >= r)
        return t[u].minn;
    push_down(u, l, r);
    int mid = (l + r) >> 1;
    int ans = 2139062143;
    if (a <= mid)
    {
        ans = min(ans, min_query(lson(u), l, mid, a, b));
    }
    if (b > mid)
    {
        ans = min(ans, min_query(rson(u), mid + 1, r, a, b));
    }
    return ans;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 1; i <= 800000; i++)
    {
        t[i].sumn = t[i].lazt = 0;
        t[i].minn = -1e9;
    }
    int q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> val[i];
    }
    build(1, 1, n);
    int ty, l, r, k;
    for (int i = 1; i <= q; i++)
    {
        cin >> ty;
        if (ty == 1)
        {
            cin >> l >> r >> k;
            l++;
            r++;
            plus_update(1, 1, n, l, r, k);
        }
        if (ty == 2)
        {
            cin >> l >> r >> k;
            l++;
            r++;
            div_update(1, 1, n, l, r, k);
        }
        if (ty == 3)
        {
            cin >> l >> r;
            l++;
            r++;
            cout << min_query(1, 1, n, l, r) << '\n';
        }
        if (ty == 4)
        {
            cin >> l >> r;
            l++;
            r++;
            cout << sum_query(1, 1, n, l, r) << '\n';
        }
    }
}
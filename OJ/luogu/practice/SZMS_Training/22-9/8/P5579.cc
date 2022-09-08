#include <algorithm>
#include <iostream>

using i64 = long long;
const int MAX_N = 5e5 + 10;

struct st_node
{
    i64 sum;
    i64 add;
    i64 tag;
    i64 max;
};

st_node st[MAX_N * 4];
i64 pre[MAX_N];
i64 a[MAX_N];
int n, m;

void build(int l, int r, int k)
{
    st[k].tag = -1;
    if (l == r)
        return;

    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r) / 2;

    build(l, mid, ls);
    build(mid + 1, r, rs);
}

void pushup(int k)
{
    int ls = k * 2;
    int rs = k * 2 + 1;
    st[k].sum = st[ls].sum + st[rs].sum;
    st[k].max = st[rs].max;
}

void cut(int l, int r, int k, i64 v)
{
    st[k].tag = v;
    st[k].sum = (i64)(r - l + 1) * v;
    st[k].max = v;
    st[k].add = 0;
}

void grow(int l, int r, int k, i64 v)
{
    st[k].add += v;
    st[k].sum += (i64)(pre[r] - pre[l - 1]) * v;
    st[k].max += (i64)a[r] * v;
}

void pushdown(int l, int r, int k)
{
    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r) / 2;
    if (st[k].tag != -1)
    {
        cut(l, mid, ls, st[k].tag);
        cut(mid + 1, r, rs, st[k].tag);
        st[k].tag = -1;
    }
    if (st[k].add)
    {
        grow(l, mid, ls, st[k].add);
        grow(mid + 1, r, rs, st[k].add);
        st[k].add = 0;
    }
}

int query(int l, int r, int k, i64 v)
{
    if (l == r)
        return st[k].sum < v ? n + 1 : l;

    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r) / 2;
    pushdown(l, r, k);
    if (st[ls].max >= v)
        return query(l, mid, ls, v);
    else
        return query(mid + 1, r, rs, v);
}

inline i64 update(int l, int r, int k, const int L, const int R, i64 v)
{
    if (L > R)
        return 0;
    if (L <= l && r <= R)
    {
        i64 sum = st[k].sum;
        cut(l, r, k, v);
        return sum - st[k].sum;
    }

    i64 ans = 0;
    int ls = k * 2;
    int rs = k * 2 + 1;
    int mid = (l + r) / 2;
    pushdown(l, r, k);
    if (L <= mid)
        ans += update(l, mid, ls, L, R, v);
    if (R > mid)
        ans += update(mid + 1, r, rs, L, R, v);
    pushup(k);
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    for (int i = 1; i <= n; i++)
        std::cin >> a[i];

    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + a[i];
    build(1, n, 1);

    i64 day = 0;
    for (int i = 0; i < m; i++)
    {
        i64 d, b;
        std::cin >> d >> b;
        grow(1, n, 1, d - day);
        day = d;

        std::cout << update(1, n, 1, query(1, n, 1, b), n, b) << "\n";
    }
    return 0;
}
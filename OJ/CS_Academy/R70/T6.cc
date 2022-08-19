// CS Academy Round #70 T6: And or Max

#include <iostream>

const int ONES = (1 << 20) - 1;
const int MAX_N = 2e5 + 10;

struct t_node
{
    int a, o, m; // add, or, max
    int tag_a, tag_o;
};

int a[MAX_N];
int n, q;

t_node st[4 * MAX_N];

void commit(int k, int tag, const bool is_a)
{
    if (is_a)
    {
        st[k].a &= tag;
        st[k].o &= tag;
        st[k].m &= tag;
        st[k].tag_a &= tag;
        st[k].tag_o &= tag;
    }
    else
    {
        st[k].a |= tag;
        st[k].o |= tag;
        st[k].m |= tag;
        st[k].tag_a |= tag;
        st[k].tag_o |= tag;
    }
}

void push_up(int k)
{
    const int ls = k * 2;
    const int rs = k * 2 + 1;
    st[k].a = st[ls].a & st[rs].a;
    st[k].o = st[ls].o | st[rs].o;
    st[k].m = std::max(st[ls].m, st[rs].m);
}

void push_down(int k)
{
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    commit(ls, st[k].tag_a, true);
    commit(rs, st[k].tag_a, true);

    commit(ls, st[k].tag_o, false);
    commit(rs, st[k].tag_o, false);

    st[k].tag_a = ONES;
    st[k].tag_o = 0;
}

void build(int l, int r, int k)
{
    st[k].tag_a = ONES;
    st[k].tag_o = 0;

    if (l == r)
    {
        st[k].a = st[k].o = st[k].m = a[l];
        return;
    }

    const int mid = (l + r) / 2;
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    build(l, mid, ls);
    build(mid + 1, r, rs);
    push_up(k);
}

void update(int l, int r, int k, const int L, const int R, const int x, const bool is_a)
{
    if (L <= l && r <= R && !((st[k].a ^ st[k].o) & (is_a ? (~x) : x)))
    {
        commit(k, x, is_a);
        return;
    }
    push_down(k);

    const int mid = (l + r) / 2;
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    if (L <= mid)
        update(l, mid, ls, L, R, x, is_a);
    if (R > mid)
        update(mid + 1, r, rs, L, R, x, is_a);

    push_up(k);
}

int query(int l, int r, int k, const int L, const int R)
{
    if (L <= l && r <= R)
        return st[k].m;
    push_down(k);

    const int mid = (l + r) / 2;
    const int ls = k * 2;
    const int rs = k * 2 + 1;

    int l_res = -1;
    int r_res = -1;
    if (L <= mid)
        l_res = query(l, mid, ls, L, R);
    if (R > mid)
        r_res = query(mid + 1, r, rs, L, R);

    return std::max(l_res, r_res);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    build(1, n, 1);

    for (int _i = 0; _i < q; _i++)
    {
        int op;
        std::cin >> op;

        if (op == 1 || op == 2)
        {
            int l, r, x;
            std::cin >> l >> r >> x;
            update(1, n, 1, l, r, x, !(op - 1));
        }
        else
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << query(1, n, 1, l, r) << "\n";
        }
    }

    return 0;
}

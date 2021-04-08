#include <algorithm>
#include <iostream>

const int MAX_N = 2e5 + 10;
const int MAX_TREE_N = MAX_N * 4;

struct holes
{
    int left_max = 0;
    int right_max = 0;
    int max = 0;
    int cnt = 0;
    int size = 0;

    holes() {}
    holes(int left_max, int right_max, int max, int cnt, int size)
    {
        this->left_max = left_max;
        this->right_max = right_max;
        this->max = max;
        this->cnt = cnt;
        this->size = size;
    }
};

struct st
{
    holes hole;
    int tag;
};

st tree[MAX_TREE_N];
int n;

void commit(int l, int r, int k, int val)
{
    tree[k].tag = val;

    const int new_val = val == 1 ? 0 : r - l + 1;
    tree[k].hole = holes(new_val, new_val, new_val, new_val, tree[k].hole.size);
}

const holes upload(const int l, const int r, const holes &ls_v, const holes &rs_v)
{
    holes res;

    const int mid = (l + r) / 2;

    if (ls_v.max == mid - l + 1)
        res.left_max = ls_v.max + rs_v.left_max;
    else
        res.left_max = ls_v.left_max;

    if (rs_v.max == r - mid)
        res.right_max = rs_v.max + ls_v.right_max;
    else
        res.right_max = rs_v.right_max;

    res.cnt = ls_v.cnt + rs_v.cnt;
    res.max = std::max(std::max(ls_v.max, rs_v.max), ls_v.right_max + rs_v.left_max);
    res.size = ls_v.size + rs_v.size;

    return res;
}

void push_down(const int l, const int r, const int k)
{
    if (tree[k].tag != 2)
    {
        const int ls = k * 2;
        const int rs = k * 2 + 1;
        const int mid = (l + r) / 2;

        commit(l, mid, ls, tree[k].tag);
        commit(mid + 1, r, rs, tree[k].tag);

        tree[k].tag = 2;
    }
}

void build(const int l = 1, const int r = n, const int k = 1)
{
    tree[k].hole.size = r - l + 1;
    tree[k].tag = 2;

    if (l == r)
        return;

    const int ls = k * 2;
    const int rs = k * 2 + 1;
    const int mid = (l + r) / 2;

    build(l, mid, ls);
    build(mid + 1, r, rs);
}

void update(const int l_tar, const int r_tar, const int val, const int k = 1, const int l = 1, const int r = n)
{
    if (l_tar <= l && r <= r_tar)
    {
        commit(l, r, k, val);
        return;
    }

    const int ls = k * 2;
    const int rs = k * 2 + 1;
    const int mid = (l + r) / 2;

    if (l == r)
        return;

    push_down(l, r, k);
    if (l_tar <= mid)
        update(l_tar, r_tar, val, ls, l, mid);
    if (r_tar > mid)
        update(l_tar, r_tar, val, rs, mid + 1, r);

    tree[k].hole = upload(l, r, tree[ls].hole, tree[rs].hole);
}

holes query(const int l_tar, const int r_tar, const int k = 1, const int l = 1, const int r = n)
{
    if (l_tar <= l && r <= r_tar)
        return tree[k].hole;

    const int ls = k * 2;
    const int rs = k * 2 + 1;
    const int mid = (l + r) / 2;

    push_down(l, r, k);

    if (l_tar <= mid && mid < r_tar)
        return upload(l, r, query(l_tar, r_tar, ls, l, mid), query(l_tar, r_tar, rs, mid + 1, r));
    else if (l_tar <= mid)
        return query(l_tar, r_tar, ls, l, mid);
    else
        return query(l_tar, r_tar, rs, mid + 1, r);
}

int queue_cnt(const int l_tar, const int r_tar, const int k = 1, const int l = 1, const int r = n)
{
    if (l_tar <= l && r <= r_tar)
        return tree[k].hole.cnt;

    const int ls = k * 2;
    const int rs = k * 2 + 1;
    const int mid = (l + r) / 2;

    push_down(l, r, k);
    int res = 0;
    if (l_tar <= mid)
        res += queue_cnt(l_tar, r_tar, ls, l, mid);
    if (r_tar > mid)
        res += queue_cnt(l_tar, r_tar, rs, mid + 1, r);
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int q;
    std::cin >> n >> q;

    build();
    for (int _i = 0; _i < q; _i++)
    {
        int op;
        std::cin >> op;

        if (op == 0)
        {
            int l, r;
            std::cin >> l >> r;

            update(l, r, 0);
        }
        else if (op == 1)
        {
            int l1, r1, l2, r2;
            std::cin >> l1 >> r1 >> l2 >> r2;

            const auto res = query(l1, r1);
            const int avaliable = res.size - res.cnt;
            update(l1, r1, 0);

            int l = -1;
            int r = r2 - l2 + 1;
            while (r - l > 1)
            {
                int mid = (l + r) / 2;
                if (queue_cnt(l2, l2 + mid) <= avaliable)
                    l = mid;
                else
                    r = mid;
            }

            update(l2, l2 + l, 1);
        }
        else if (op == 2)
        {
            int l, r;
            std::cin >> l >> r;

            std::cout << query(l, r).max << "\n";
        }
    }
    return 0;
}

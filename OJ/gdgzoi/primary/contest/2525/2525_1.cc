#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

int n;
std::vector<int> base;
std::vector<int> val;

class SegmentTree
{
private:
    struct TreeItem
    {
        int mid, ls, rs;
        long long int sum, g_sum;
        bool tag;
    };
    std::vector<TreeItem> tree;

    std::pair<long long int, long long int> build(int l = 1, int r = n, int k = 1)
    {
        if (l == r)
        {
            tree[k].g_sum = val[l];
            tree[k].sum = val[l] * base[l];
            return {val[l], val[l] * base[l]};
        }

        tree[k].ls = k * 2;
        tree[k].rs = k * 2 + 1;
        tree[k].mid = (l + r) / 2;

        const auto tmp_l = build(l, tree[k].mid, tree[k].ls);
        const auto tmp_r = build(tree[k].mid + 1, r, tree[k].rs);
        tree[k].g_sum = tmp_l.first + tmp_r.first;
        tree[k].sum = tmp_l.second + tmp_r.second;

        return {tree[k].g_sum, tree[k].sum};
    }

    void push_down(int k)
    {
        if (tree[k].tag)
        {
            tree[tree[k].ls].tag = !tree[tree[k].ls].tag;
            tree[tree[k].ls].sum = tree[tree[k].ls].g_sum - tree[tree[k].ls].sum;

            tree[tree[k].rs].tag = !tree[tree[k].rs].tag;
            tree[tree[k].rs].sum = tree[tree[k].rs].g_sum - tree[tree[k].rs].sum;

            tree[k].tag = false;
        }
    }

    void push_up(int k) { tree[k].sum = tree[tree[k].ls].sum + tree[tree[k].rs].sum; }

public:
    SegmentTree()
    {
        tree.resize(n * 4 + 10);
        build();
    }

    void update(int l_tar, int r_tar, int l = 1, int r = n, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
        {
            tree[k].tag = !tree[k].tag;
            tree[k].sum = tree[k].g_sum - tree[k].sum;
            return;
        }

        push_down(k);
        if (tree[k].mid >= l_tar)
            update(l_tar, r_tar, l, tree[k].mid, tree[k].ls);
        if (tree[k].mid < r_tar)
            update(l_tar, r_tar, tree[k].mid + 1, r, tree[k].rs);
        push_up(k);
    }

    long long int query(int l_tar, int r_tar, int l = 1, int r = n, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
            return tree[k].sum;

        push_down(k);
        long long int res = 0;
        if (l_tar <= tree[k].mid && tree[k].mid < r_tar)
            res = query(l_tar, r_tar, l, tree[k].mid, tree[k].ls) + query(l_tar, r_tar, tree[k].mid + 1, r, tree[k].rs);
        else if (l_tar <= tree[k].mid)
            res = query(l_tar, r_tar, l, tree[k].mid, tree[k].ls);
        else if (tree[k].mid < r_tar)
            res = query(l_tar, r_tar, tree[k].mid + 1, r, tree[k].rs);
        else
            res = 0;
        return res;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int m;
    std::cin >> n >> m;

    base.resize(n + 10);
    val.resize(n + 10);

    for (int i = 1; i <= n; i++)
        std::cin >> base[i];
    for (int i = 1; i <= n; i++)
        std::cin >> val[i];

    SegmentTree st;
    for (int _i = 0; _i < m; _i++)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x;
            std::cin >> x;

            st.update(x, x);
        }
        else if (op == 2)
        {
            int l, r;
            std::cin >> l >> r;

            st.update(l, r);
        }
        else if (op == 3)
        {
            int l, r;
            std::cin >> l >> r;

            std::cout << st.query(l, r) << "\n";
        }
    }
    return 0;
}

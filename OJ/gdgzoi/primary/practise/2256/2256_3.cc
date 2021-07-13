// Wrong

#include <iostream>
#include <climits>

const int INF = INT_MAX;

struct node
{
    bool is_zero = true;
    node *l_son;
    node *r_son;
    int id;

    node() {}
    node(bool is_zero, node *l_son, node *r_son, int id)
    {
        this->is_zero = is_zero;
        this->l_son = l_son;
        this->r_son = r_son;
        this->id = id;
    }

    int get_son_size(node *son)
    {
        if (is_zero)
            return 1;
        return son->get_son_size(son->l_son) + son->get_son_size(son->r_son) + 1;
    }
};

node *max(node *p1, node *p2)
{
    if (!p1)
        return p2;
    if (!p2)
        return p1;

    if (p1->is_zero && p2->is_zero)
        return p1->id < p2->id ? p1 : p2;
    if (p1->is_zero)
        return p2;
    if (p2->is_zero)
        return p1;

    const int p1_l = p1->get_son_size(p1->l_son);
    const int p2_l = p2->get_son_size(p2->l_son);

    if (p1_l > p2_l)
        return p1;
    if (p1_l < p2_l)
        return p2;

    const int p1_r = p1->get_son_size(p1->r_son);
    const int p2_r = p2->get_son_size(p2->r_son);

    return p1_r > p2_r ? p1 : p2;
}

const int MAX_N = 1e5 + 10;

node a[MAX_N];
int n, m;

namespace ST
{
    node *tree[4 * MAX_N];

    void push_up(int k)
    {
        const int ls = k * 2;
        const int rs = k * 2 + 1;

        tree[k] = max(tree[ls], tree[rs]);
    }

    int find(int tar, int l = 1, int r = n, int k = 1)
    {
        if (l == tar && r == tar)
            return k;

        const int ls = k * 2;
        const int rs = k * 2 + 1;
        const int mid = (l + r) / 2;

        if (tar <= mid)
            return find(tar, l, mid, ls);
        return find(tar, mid + 1, r, rs);
    }

    void update(int tar, node *new_tree, int l = 1, int r = n, int k = 1)
    {
        if (l == tar && r == tar)
        {
            tree[k] = new_tree;
            return;
        }

        const int ls = k * 2;
        const int rs = k * 2 + 1;
        const int mid = (l + r) / 2;

        if (tar <= mid)
            update(tar, new_tree, l, mid, ls);
        else
            update(tar, new_tree, mid + 1, r, rs);
        push_up(k);
    }

    node *query(int l_tar, int r_tar, int l = 1, int r = n, int k = 1)
    {
        if (l_tar <= l && r <= r_tar)
            return tree[k];

        const int ls = k * 2;
        const int rs = k * 2 + 1;
        const int mid = (l + r) / 2;

        node *res;
        if (l_tar <= mid)
            res = query(l_tar, r_tar, l, mid, ls);
        if (r_tar > mid)
            res = max(res, query(l_tar, r_tar, mid + 1, r, rs));
        return res;
    }
}; // namespace ST

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    std::cin >> n >> m;

    const int bottom_layer_start = ST::find(1) - 1;
    for (int i = 1; i <= n; i++)
        ST::tree[bottom_layer_start + i] = new node(true, nullptr, nullptr, i);

    node new_tree;
    for (int _i = 0; _i < m; _i++)
    {
        char op;
        std::cin >> op;

        if (op == 'C')
        {
            int l, r, k;
            std::cin >> l >> r >> k;

            new_tree.is_zero = false;
            new_tree.l_son = ST::tree[bottom_layer_start + l];
            new_tree.r_son = ST::tree[bottom_layer_start + r];
            new_tree.id = k;

            ST::update(k, &new_tree);
        }
        else if (op == 'Q')
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << ST::query(l, r)->id << "\n";
        }
    }

    return 0;
}

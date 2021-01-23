#include <iostream>

const int MAX_N = 1.1e5;
const int MAX_T = 4 * MAX_N;

int l_color[MAX_T];
int r_color[MAX_T];
int color[MAX_N];
int tree[MAX_T];
int tag[MAX_T];

void pushdown(int k)
{
    if (tag[k] == -1)
        return;

    int ls = k * 2;
    int rs = k * 2 + 1;

    l_color[ls] = r_color[ls] = tag[k];
    tree[ls] = 1;
    tag[ls] = tag[k];

    l_color[rs] = r_color[rs] = tag[k];
    tree[rs] = 1;
    tag[rs] = tag[k];

    tag[k] = -1;
}

void pushup(int k)
{
    int ls = k * 2;
    int rs = k * 2 + 1;

    tree[k] = tree[ls] + tree[rs];
    if (r_color[ls] == l_color[rs])
        tree[k] -= 1;

    l_color[k] = l_color[ls];
    r_color[k] = r_color[rs];
}

void build(int k, int l, int r)
{
    tag[k] = -1;
    if (l == r)
    {
        tree[k] = 1;
        l_color[k] = r_color[k] = color[l];
        return;
    }

    int mid = (l + r) / 2;
    build(k * 2, l, mid);
    build(k * 2 + 1, mid + 1, r);
    pushup(k);
}

void update(int k, int l, int r, int x, int y, int u, int v)
{
    if (l == r)
    {
        if (l_color[k] == u)
        {
            tree[k] = 1;
            l_color[k] = r_color[k] = v;
            tag[k] = v;
        }
        return;
    }

    pushdown(k);
    int mid = (l + r) / 2;
    if (x <= mid)
        update(k * 2, l, mid, x, y, u, v);
    if (y > mid)
        update(k * 2 + 1, mid + 1, r, x, y, u, v);
    pushup(k);
}

int query(int k, int l, int r, int x, int y)
{
    if (x <= l && r <= y)
        return tree[k];

    pushdown(k);
    int mid = (l + r) / 2;

    int res = 0;
    if (x <= mid)
        res += query(k * 2, l, mid, x, y);
    if (y > mid)
        res += query(k * 2 + 1, mid + 1, r, x, y);
    if (x <= mid && y > mid && r_color[k * 2] == l_color[k * 2 + 1])
        res -= 1;

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= n; i++)
        std::cin >> color[i];

    build(1, 1, n);
    for (int i = 0; i < m; i++)
    {
        int op;
        std::cin >> op;

        if (op == 1)
        {
            int x, y;
            std::cin >> x >> y;

            update(1, 1, n, 1, n, x, y);
        }
        else
            std::cout << query(1, 1, n, 1, n) << "\n";
    }
    return 0;
}
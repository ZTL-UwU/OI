#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

struct data
{
    long long int sum;
    int min;
    int max;
    int tag;
};

const int INF = 0x7fffffff;
const int MAXN = 5e5;
const int ADD_OP = 1;
const int DIV_OP = 2;
const int MIN_OP = 3;
const int SUM_OP = 4;

int value[MAXN];
data tree[MAXN];
int n;

inline void push_up(int k)
{
    int ls = k * 2;
    int rs = k * 2 + 1;

    tree[k].max = std::max(tree[ls].max, tree[rs].max);
    tree[k].min = std::min(tree[ls].min, tree[rs].min);
    tree[k].sum = tree[ls].sum + tree[rs].sum;
}

inline void push_down(int l, int r, int k)
{
    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;

    tree[ls].sum += (mid - l + 1) * tree[k].tag;
    tree[rs].sum += (r - mid) * tree[k].tag;
    tree[ls].max += tree[k].tag;
    tree[rs].max += tree[k].tag;
    tree[ls].min += tree[k].tag;
    tree[rs].min += tree[k].tag;
    tree[ls].tag += tree[k].tag;
    tree[rs].tag += tree[k].tag;
    tree[k].tag = 0;
}

// Build segment tree
inline void build(int l = 1, int r = n, int k = 1)
{
    if (l == r)
    {
        tree[k].sum = value[l];
        tree[k].min = value[l];
        tree[k].max = value[l];
        return;
    }

    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    build(l, mid, ls);     // Build left
    build(mid + 1, r, rs); // Build right

    push_up(k);
}

// Add and Divide
inline void update(int l, int r, int k, int x, int y, int val, int op)
{
    bool check = true;
    if (op == DIV_OP)
        check = tree[k].max - std::floor((double)tree[k].max / val) == tree[k].min - std::floor((double)tree[k].min / val);

    if (x <= l and r <= y and check)
    {
        int tmp = op == ADD_OP ? val : std::floor((double)tree[k].min / val) - tree[k].min;

        tree[k].sum += (r - l + 1) * tmp;
        tree[k].min += tmp;
        tree[k].max += tmp;
        tree[k].tag += tmp;
        return;
    }

    push_down(l, r, k);

    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;
    if (x <= mid)
        update(l, mid, ls, x, y, val, op);
    if (y > mid)
        update(mid + 1, r, rs, x, y, val, op);

    push_up(k);
}

// Sum and Min
inline long long int query(int l, int r, int k, int x, int y, int op)
{
    if (x <= l and r <= y)
        return op == SUM_OP ? tree[k].sum : tree[k].min;

    push_down(l, r, k);

    int mid = (l + r) / 2;
    int ls = k * 2;
    int rs = k * 2 + 1;

    long long int res = op == SUM_OP ? 0 : INF;
    if (x <= mid)
    {
        long long int next = query(l, mid, ls, x, y, op);
        res = op == SUM_OP ? res + next : std::min(res, next);
    }
    if (y > mid)
    {
        long long int next = query(mid + 1, r, rs, x, y, op);
        res = op == SUM_OP ? res + next : std::min(res, next);
    }

    return res;
}

int main()
{
    // I/O optimization
    std::ios::sync_with_stdio(false);
    std::cout.tie(0);
    std::cin.tie(0);

    int q;
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++)
        std::cin >> value[i];

    build();
    for (int t = 0; t < q; t++)
    {
        int op;
        std::cin >> op;

        if (op == ADD_OP or op == DIV_OP)
        {
            int l, r, val;
            std::cin >> l >> r >> val;
            update(1, n, 1, l + 1, r + 1, val, op);
        }
        if (op == SUM_OP or op == MIN_OP)
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << query(1, n, 1, l + 1, r + 1, op) << "\n";
        }
    }
    return 0;
}
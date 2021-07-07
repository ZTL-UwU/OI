#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
const int maxn = 200000;
struct brainhole
{
    int lhole, rhole, maxhole;
    int cnt;
    int size;
    brainhole operator+(const brainhole &b) const
    {
        brainhole c;
        c.maxhole = max(rhole + b.lhole, max(maxhole, b.maxhole));
        if (lhole == size)
            c.lhole = lhole + b.lhole;
        else
            c.lhole = lhole;
        if (b.rhole == b.size)
            c.rhole = b.rhole + rhole;
        else
            c.rhole = b.rhole;
        c.cnt = cnt + b.cnt;
        c.size = size + b.size;
        return c;
    }
};
struct segment_tree
{
    brainhole hole;
    int lazy; /* 0: cover with 0 1: cover with 1 2: no tag*/
    int l, r, mid;
} tree[4 * maxn + 5];
inline void pushup(int id) { tree[id].hole = tree[id * 2].hole + tree[id * 2 + 1].hole; }
inline void pushdown(int id)
{
    if (tree[id].lazy == 2)
        return;
    if (tree[id].lazy == 0)
    {
        tree[id * 2].hole.lhole = tree[id * 2].hole.rhole = tree[id * 2].hole.maxhole = tree[id * 2].hole.cnt =
            tree[id * 2].hole.size;
        tree[id * 2 + 1].hole.lhole = tree[id * 2 + 1].hole.rhole = tree[id * 2 + 1].hole.maxhole =
            tree[id * 2 + 1].hole.cnt = tree[id * 2 + 1].hole.size;
    }
    else if (tree[id].lazy == 1)
    {
        tree[id * 2].hole.lhole = tree[id * 2].hole.rhole = tree[id * 2].hole.maxhole = tree[id * 2].hole.cnt = 0;
        tree[id * 2 + 1].hole.lhole = tree[id * 2 + 1].hole.rhole = tree[id * 2 + 1].hole.maxhole =
            tree[id * 2 + 1].hole.cnt = 0;
    }
    tree[id * 2].lazy = tree[id * 2 + 1].lazy = tree[id].lazy;
    tree[id].lazy = 2;
}
void build(int p, int l, int r)
{
    tree[p].hole.size = r - l + 1;
    tree[p].hole.lhole = tree[p].hole.rhole = tree[p].hole.maxhole = tree[p].hole.cnt = 0;
    tree[p].l = l;
    tree[p].r = r;
    tree[p].lazy = 2;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    tree[p].mid = mid;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
}
void update(int p, int ql, int qr, bool c)
{
    int l = tree[p].l, r = tree[p].r, mid = tree[p].mid;
    std::cout << p << "\n";
    std::cout.flush();
    if (l >= ql && r <= qr)
    {
        tree[p].lazy = c;
        if (c == 0)
            tree[p].hole.lhole = tree[p].hole.rhole = tree[p].hole.maxhole = tree[p].hole.cnt = tree[p].hole.size;
        else
            tree[p].hole.lhole = tree[p].hole.rhole = tree[p].hole.maxhole = tree[p].hole.cnt = 0;
        return;
    }
    pushdown(p);
    if (mid >= ql)
        update(p * 2, ql, qr, c);
    if (mid < qr)
        update(p * 2 + 1, ql, qr, c);
    pushup(p);
}
brainhole query(int p, int ql, int qr)
{
    int l = tree[p].l, r = tree[p].r, mid = tree[p].mid;
    if (l >= ql && r <= qr)
        return tree[p].hole;
    pushdown(p);
    if (mid >= ql && mid < qr)
    {
        brainhole a = query(p * 2, ql, qr), b = query(p * 2 + 1, ql, qr);
        return a + b;
    }
    else if (mid >= ql)
        return query(p * 2, ql, qr);
    else
        return query(p * 2 + 1, ql, qr);
}
int query_num(int p, int ql, int qr)
{
    int l = tree[p].l, r = tree[p].r, mid = tree[p].mid;
    if (l >= ql && r <= qr)
        return tree[p].hole.cnt;
    pushdown(p);
    int res = 0;
    if (mid >= ql)
        res += query_num(p * 2, ql, qr);
    if (mid < qr)
        res += query_num(p * 2 + 1, ql, qr);
    return res;
}
int n, m;
int main()
{
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        int op;
        scanf("%d", &op);
        int l1, r1;
        scanf("%d%d", &l1, &r1);
        if (op == 0)
            update(1, l1, r1, 0);
        if (op == 1)
        {
            int l2, r2;
            scanf("%d%d", &l2, &r2);
            brainhole res = query(1, l1, r1);
            int num = res.size - res.cnt;
            update(1, l1, r1, 0);
            int l = -1, r = r2 - l2 + 1;
            while (r - l > 1)
            {
                printf("%d %d\n", l, r);
                int mid = (l + r) / 2;
                if (query_num(1, l2, l2 + mid) <= num)
                    l = mid;
                else
                    r = mid;
            }

            std::cout << l2 << " " << l2 + l << "\n";
            std::cout.flush();
            bool flag = true;
            if (l2 == 1 && l == -1)
            {
                flag = false;
                std::cout << "die\n";
                std::cout.flush();
                // return 0;
            }
            update(1, l2, l2 + l, 1);
        }
        if (op == 2)
            printf("%d\n", query(1, l1, r1).maxhole);
    }
}
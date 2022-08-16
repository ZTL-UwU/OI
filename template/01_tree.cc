#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct node
{
    int c[2];
    int sz;

    node()
    {
        c[0] = c[1] = 0;
        sz = 0;
    }
};

vector<int> roots;
vector<node> tree;

int clone_node(int x)
{
    node a = tree[x];
    tree.push_back(a);
    return tree.size() - 1;
}

void insert(int x, unsigned int v, int b)
{
    tree[x].sz += 1;
    if (b < 0)
    {
        return;
    }

    int t = (v >> b) & 1;
    tree[x].c[t] = clone_node(tree[x].c[t]);
    insert(tree[x].c[t], v, b - 1);
}

unsigned int kth(int k, int l, int r)
{
    unsigned int res = 0;

    int rl = roots[l], rr = roots[r];
    for (int b = 31; b >= 0; --b)
    {
        int n = tree[tree[rr].c[0]].sz - tree[tree[rl].c[0]].sz;
        if (n >= k)
        {
            rl = tree[rl].c[0];
            rr = tree[rr].c[0];
        }
        else
        {
            rl = tree[rl].c[1];
            rr = tree[rr].c[1];
            res |= 1 << b;
            k -= n;
        }
    }

    return res;
}

void debug(int x, unsigned int v, int b)
{
    if (x == 0)
    {
        return;
    }

    if (b < 0)
    {
        printf("%u ", v);
        return;
    }

    debug(tree[x].c[0], v, b - 1);
    debug(tree[x].c[1], v | (1 << b), b - 1);
}

int main()
{
    tree.push_back(node());
    tree.push_back(node());
    roots.push_back(1);
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        unsigned int xx = static_cast<unsigned int>(x);
        roots.push_back(clone_node(roots.back()));
        insert(roots.back(), xx, 31);
    }

    for (int _ = 0; _ < q; ++_)
    {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        if (l > r)
        {
            swap(l, r);
        }

        printf("%u\n", kth(k, l - 1, r));
    }
    return 0;
}

#include <iostream>
#include <string.h>
using namespace std;
struct tree
{
    // val----------------------------------------------------------

    int INF = 0x7fffffff;

    int max_len = 100010 /* val (times 4) */;

    int *Tree; // basic val

    void make_tree_basic(int x)
    {
        /* val */
        cin >> Tree[x];
    }

    inline int make_tree(int l, int r)
    {
        return min(Tree[l], Tree[r]);
    }

    void update(int pos, int val)
    {
        Tree[pos] = val;
    }

    // val----------------------------------------------------------

    void init()
    {
        Tree = new int[max_len * 4];
        memset(Tree, 0, max_len * 4 * sizeof(int));
    }
    void build(int l, int r, int k)
    {
        if (l == r)
        {
            make_tree_basic(k);
            return;
        }
        int mid = (l + r) >> 1;
        int ls = k << 1;
        int rs = k << 1 | 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        Tree[k] = make_tree(ls, rs);
    }
    void single_update(int l, int r, int k, int place, int val)
    {
        if (l == r)
        {
            update(k, val);
            return;
        }
        int mid = (l + r) >> 1;
        int ls = k << 1;
        int rs = k << 1 | 1;
        if (place <= mid)
            single_update(l, mid, ls, place, val);
        else
            single_update(mid + 1, r, rs, place, val);
        Tree[k] = make_tree(ls, rs);
    }
    inline int get_min(int l, int r, int k, int a, int b)
    {
        if (r < a || b < l)
            return 0;
        if (a <= l && b >= r)
            return Tree[k];
        int mid = (l + r) >> 1;
        int ls = k << 1;
        int rs = k << 1 | 1;
        int tmp1 = INF, tmp2 = INF;
        if (a <= mid)
            tmp1 = get_min(l, mid, ls, a, b);
        if (b > mid)
            tmp2 = get_min(mid + 1, r, rs, a, b);
        return min(tmp1, tmp2);
    }
};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    tree a;
    a.init();
    a.build(1, n, 1);
    for (int i = 0; i < m; i++)
    {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1)
            cout << a.get_min(1, n, 1, x, y) << " ";
        else
            a.single_update(1, n, 1, x, y);
    }
    return 0;
}
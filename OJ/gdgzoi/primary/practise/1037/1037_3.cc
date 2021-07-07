#include <iostream>
#include <string.h>
using namespace std;
long long len;
long long aa;
struct tree
{
    // basic items--------------------------------------------------

    long long *Tree; // basic val
    long long *add;  // basic val

    // basic items--------------------------------------------------

    // user functions----------------------------------------------------------

    long long seted_single = -0x7fffffff /* val */;
    long long max_len = 200010 /* val */; /* val (times 4) */

    void make_tree_basic_single(long long x) { Tree[x] = 0; }

    void make_tree_basic_long(long long x)
    { /* val */
    }

    inline long long make_tree_single(long long l, long long r) { return max(Tree[l], Tree[r]); }

    inline long long make_tree_long(long long l, long long r)
    { /* val */
    }

    void update_single(long long pos, long long val) { Tree[pos] = val; }

    void update_long(long long pos, long long val)
    { /* val */
    }

    inline long long comp_single(long long v1, long long v2) { return max(v1, v2); }

    inline long long comp_long(long long v1, long long v2)
    { /* val */
    }

    // user functions------------------------------------------------------------

    void init()
    {
        Tree = new long long[max_len * 4];
        memset(Tree, 0, max_len * 4 * sizeof(long long));
        add = new long long[max_len * 4];
        memset(add, 0, max_len * 4 * sizeof(long long));
    }

    void build_single(long long l, long long r, long long k)
    {
        if (l == r)
        {
            make_tree_basic_single(k);
            return;
        }

        long long mid = (l + r) >> 1;
        long long ls = k << 1, rs = k << 1 | 1;
        build_single(l, mid, ls);
        build_single(mid + 1, r, rs);
        Tree[k] = make_tree_single(ls, rs);
    }

    void build_long(long long l, long long r, long long k)
    {
        if (l == r)
        {
            make_tree_basic_long(k);
            return;
        }

        long long mid = (l + r) >> 1;
        long long ls = k << 1, rs = k << 1 | 1;
        build_long(l, mid, ls);
        build_long(mid + 1, r, rs);
        Tree[k] = make_tree_long(ls, rs);
    }

    void single_update(long long l, long long r, long long k, long long place, long long val)
    {
        if (l == r)
        {
            update_single(k, val);
            return;
        }

        long long mid = (l + r) >> 1;
        long long ls = k << 1, rs = k << 1 | 1;
        if (place <= mid)
            single_update(l, mid, ls, place, val);
        else
            single_update(mid + 1, r, rs, place, val);
        Tree[k] = make_tree_single(ls, rs);
    }

    void long_update(long long l, long long r, long long k, long long a, long long b, long long val)
    {
        if (l >= a && r <= b)
        {
            update_long(k, val);
            return;
        }

        Tree[k] += (min(r, b) - max(l, a) + 1) * val;
        long long mid = (l + r) >> 1;
        long long ls = k << 1, rs = k << 1 | 1;
        if (a <= mid)
            long_update(l, mid, ls, a, b, val);
        if (b > mid)
            long_update(mid + 1, r, rs, a, b, val);
    }

    inline long long long_query_single(long long l, long long r, long long k, long long a, long long b)
    {
        if (a <= l && b >= r)
            return Tree[k];
        long long mid = (l + r) >> 1;
        long long ls = k << 1, rs = k << 1 | 1;
        long long tmp1 = seted_single, tmp2 = seted_single;
        if (a <= mid)
            tmp1 = long_query_single(l, mid, ls, a, b);
        if (b > mid)
            tmp2 = long_query_single(mid + 1, r, rs, a, b);
        return comp_single(tmp1, tmp2);
    }

    inline long long long_query_long(long long l, long long r, long long k, long long a, long long b)
    {
        if (l >= a && r <= b)
            return Tree[k] + (r - l + 1) * add[k];
        long long mid = (l + r) >> 1;
        long long ls = k << 1, rs = k << 1 | 1;
        long long tmp = (min(r, b) - max(l, a) + 1) * add[k];
        if (a <= mid)
            tmp += long_query_long(l, mid, ls, a, b);
        if (b > mid)
            tmp += long_query_long(mid + 1, r, rs, a, b);
        return tmp;
    }
};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    long long n, p;
    cin >> n >> p;
    tree a;
    a.init();
    a.build_single(1, n, 1);
    for (long long i = 0; i < n; i++)
    {
        long long x;
        char type;
        cin >> type >> x;
        if (type == 'A')
        {
            a.single_update(1, n, 1, ++len, (x + aa) % p);
        }
        else
        {
            long long tmp = a.long_query_single(1, n, 1, len - x + 1, len + 1);
            cout << tmp << '\n';
            aa = tmp;
        }
    }
    return 0;
}
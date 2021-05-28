/*
 *
 * Name: Segment Tree
 * Copyright (C) 2017-2019 zhangtianli
 *
 */

/*
 *
 * basic operation
 *
 * - in main
 *   - tree "name"
 *   - init()  *important
 *	- build_single/_long()
 *	- operation by changing val in struct "tree"
 *   - used functions below
 *	** don't change the basic items
 *
 * functions:
 *
 *	1. void init(void)  make int Tree[] & add[]
 *
 *	2. void build_single(long long l, long long r, long long k)  bulid segnent tree by single update & query
 *      l , r : build tree from point "l" to point "r"
 *      k : start from which point number **should be 1 in defult
 *
 *   3. void bulid_long(long long l, long long r, long long k)  bulid segnent tree by long update & query
 *      l , r : build tree from point "l" to point "r"
 *      k : start from which point number **should be 1 in defult
 *
 *	4. void single_update(long long l, long long r, long long k, long long place, long long val) modify single element
 *      l , r : search from point "l" to point "r" **should be 1 & n (element number) in defult
 *      k : start point  **should be 1 in defult
 *      val : modify key (could be change into others)
 *
 *   5. void long_update(long long l, long long r, long long k, long long a, long long b, long long val)  modify
 *elements in a section l , r : search from point "l" to point "r" **should be 1 & n (element number) in defult k :
 *start point  **should be 1 in defult a , b : section's left point & right point val : modify key (could be change into
 *others)
 *
 *   6. inline long long long_query_single(long long l, long long r, long long k, long long a, long long b) querying a
 *section use with "build_single" & "single_update" l , r : search from point "l" to point "r" **should be 1 & n
 *(element number) in defult k : start point  **should be 1 in defult a , b : section's left point & right point return
 *: could be changed by user functions (basicly add and sum)
 *
 *   7. inline long long long_query_long(long long l, long long r, long long k, long long a, long long b) querying a
 *section use with "long_build" & "long_update" l , r : search from point "l" to point "r" **should be 1 & n (element
 *number) in defult k : start point  **should be 1 in defult a , b : section's left point & right point return : could
 *be changed by user functions (basicly add and sum)
 *
 * user functions:
 *   changeable function **do not change
 *
 *   1. seted_single : use INF for normal
 *   2. max_len : max_len of tree **it will be times 4 automatically
 *   3. void make_tree_basic_single(long long x) last layer's operation in tree. used in "build_single"
 *   4. void make_tree_basic_long(long long x) last layer's operation in tree. used in "build_long"
 *   5. long long make_tree_single(long long l, long long r) normal point tree make. used in "build_single"
 *   6. long long make_tree_long(long long l, long long r) normal point tree make. used in "build_long"
 *   7. void update_single(long long pos, long long val) change single element used in "single_update" normally is
 *Tree[pos] += val pos : place that change val val : val the change
 *   8. void update_long(long long pos, long long val) change single element used in "long_update" normally is add[pos]
 *+= val; pos : place that change val val : val the change
 *   9. inline long long comp_single(long long v1, long long v2) compare v1 & v2 used in "long_query_single"
 *      sum : return v1 + v2
 *      min : return std::min(v1, v2);
 *      max : return std::max(v1, v2);
 *   10. inline long long comp_long(long long v1, long long v2)  compare v1 & v2 used in "long_query_long"
 *      sum : return v1 + v2
 *      min : return std::min(v1, v2);
 *      max : return std::max(v1, v2);
 *
 */

#include <iostream>
#include <string.h>
#include <iomanip>
#define endl '\n'
using namespace std;

struct tree
{
    // basic items--------------------------------------------------

    long long *Tree; // basic val
    long long *add;  // basic val

    // basic items--------------------------------------------------

    // user functions----------------------------------------------------------

    long long seted_single = 0 /* val */;
    long long max_len = 200010 /* val */; /* val (times 4) */

    void make_tree_basic_single(long long x)
    {
        cin >> Tree[x];
        /* val */
    }

    void make_tree_basic_long(long long x)
    { /* val */
    }

    inline long long make_tree_single(long long l, long long r)
    {
        return Tree[l] + Tree[r];
        /* val */
    }

    inline long long make_tree_long(long long l, long long r)
    { /* val */
    }

    void update_single(long long pos, long long val)
    {
        Tree[pos] = 0;
        /* val */
    }

    void update_long(long long pos, long long val)
    { /* val */
    }

    inline long long comp_single(long long v1, long long v2)
    {
        return v1 + v2;
        /* val */
    }

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
    int n;
    cin >> n;
    tree a;
    a.init();
    a.build_single(1, n, 1);
    int m;
    cin >> m;
    while (m--)
    {
        int x, y;
        cin >> x >> y;
        double ans = a.long_query_single(1, n, 1, x, y) * 3.14;
        a.single_update(1, n, 1, (x + y) / 2, 1);
        cout << fixed << setprecision(2) << ans << endl;
    }
    return 0;
}
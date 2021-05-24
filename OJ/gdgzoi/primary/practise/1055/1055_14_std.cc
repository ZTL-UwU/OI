#include <bits/stdc++.h>
#define il inline
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define For(i, a, b) for (int(i) = (a); (i) <= (b); (i)++)
#define Max(a, b) ((a) > (b) ? (a) : (b))
using namespace std;
const int N = 200005;
int n, m, num[N], ls[N], rs[N];
int ye[N], co[N];
bool f[N];
struct node
{
    int ans, f;
};

il int gi()
{
    int a = 0;
    char x = getchar();
    bool f = 0;
    while ((x < '0' || x > '9') && x != '-')
        x = getchar();
    if (x == '-')
        x = getchar(), f = 1;
    while (x >= '0' && x <= '9')
        a = (a << 3) + (a << 1) + x - 48, x = getchar();
    return f ? -a : a;
}

il void pushup(int rt)
{
    if (rs[rt << 1] == ls[rt << 1 | 1] - 1)
        f[rt] = f[rt << 1] & f[rt << 1 | 1];
    rs[rt] = rs[rt << 1 | 1];
    ls[rt] = ls[rt << 1];
    num[rt] = Max(num[rt << 1], num[rt << 1 | 1]);
}

il void build(int l, int r, int rt)
{
    if (l == r)
    {
        rs[rt] = ls[rt] = ye[l], num[rt] = co[l], f[rt] = 1;
        return;
    }
    int m = l + r >> 1;
    build(lson), build(rson);
    pushup(rt);
}

il node query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        node tmp;
        tmp.ans = num[rt], tmp.f = f[rt];
        return tmp;
    }
    int m = l + r >> 1;
    node tmp;
    tmp.ans = 0, tmp.f = 1;
    if (L <= m)
    {
        node x = query(L, R, lson);
        tmp.ans = Max(tmp.ans, x.ans);
        tmp.f &= x.f;
    }
    if (R > m)
    {
        node x = query(L, R, rson);
        tmp.ans = Max(tmp.ans, x.ans);
        tmp.f &= x.f;
    }
    return tmp;
}

int main()
{
    n = gi();
    For(i, 1, n) ye[i] = gi(), co[i] = gi();
    build(1, n, 1);
    m = gi();
    int x, y;
    while (m--)
    {
        x = gi(), y = gi();
        if (x >= y)
        {
            printf("false\n");
            continue;
        }
        int st = lower_bound(ye + 1, ye + n + 1, x) - ye, ed = lower_bound(ye + 1, ye + n + 1, y) - ye;
        bool fl, fr;
        int op = 0;
        fl = ye[st] == x, fr = ye[ed] == y;
        if (!fl)
            st--;
        if (st + 1 <= ed - 1)
            op = query(st + 1, ed - 1, 1, n, 1).ans;
        std::cout << st << fl << ed << fr << op;
        if ((op >= co[ed] && fr) || (co[st] < co[ed] && fl && fr) || (op >= co[st] && fl))
            printf("false\n");
        else if (ed - st != ye[ed] - ye[st] || !fr || !fl)
            printf("maybe\n");
        else
            printf("true\n");
    }
    return 0;
}
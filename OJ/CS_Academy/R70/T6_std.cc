#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M, a[200005];
struct Node
{
    int and_sum, or_sum, Max;
    int and_tag, or_tag;
    Node *ch[2];
    void update()
    {
        and_sum = ch[0]->and_sum & ch[1]->and_sum;
        or_sum = ch[0]->or_sum | ch[1]->or_sum;
        Max = max(ch[0]->Max, ch[1]->Max);
    }
    void OR(int x)
    {
        or_sum |= x, and_sum |= x, Max |= x;
        or_tag |= x, and_tag |= x;
    }
    void AND(int x)
    {
        or_sum &= x, and_sum &= x, Max &= x;
        or_tag &= x, and_tag &= x;
    }
    void pushdown()
    {
        ch[0]->AND(and_tag), ch[0]->OR(or_tag);
        ch[1]->AND(and_tag), ch[1]->OR(or_tag);
        and_tag = (1 << 20) - 1, or_tag = 0;
    }
    int diff() { return and_sum ^ or_sum; }
} * root, w[400005], *tw = w;

Node *build(int lf, int rg)
{
    Node *nd = ++tw;
    nd->and_tag = (1 << 20) - 1;
    if (lf != rg)
    {
        int mid = (lf + rg) >> 1;
        nd->ch[0] = build(lf, mid);
        nd->ch[1] = build(mid + 1, rg);
        nd->update();
    }
    else
        nd->and_sum = nd->or_sum = nd->Max = a[lf];
    return nd;
}

void Or(Node *nd, int lf, int rg, int L, int R, int x)
{
    if (L <= lf && rg <= R && !(nd->diff() & x))
        return nd->OR(x);
    int mid = (lf + rg) >> 1;
    nd->pushdown();
    if (L <= mid)
        Or(nd->ch[0], lf, mid, L, R, x);
    if (R > mid)
        Or(nd->ch[1], mid + 1, rg, L, R, x);
    nd->update();
}

void And(Node *nd, int lf, int rg, int L, int R, int x)
{
    if (L <= lf && rg <= R && !(nd->diff() & (~x)))
        return nd->AND(x);
    int mid = (lf + rg) >> 1;
    nd->pushdown();
    if (L <= mid)
        And(nd->ch[0], lf, mid, L, R, x);
    if (R > mid)
        And(nd->ch[1], mid + 1, rg, L, R, x);
    nd->update();
}

int Query(Node *nd, int lf, int rg, int L, int R)
{
    if (L <= lf && rg <= R)
        return nd->Max;
    int mid = (lf + rg) >> 1, rt = 0;
    nd->pushdown();
    if (L <= mid)
        rt = max(rt, Query(nd->ch[0], lf, mid, L, R));
    if (R > mid)
        rt = max(rt, Query(nd->ch[1], mid + 1, rg, L, R));
    return rt;
}

void solve()
{
    int opt, l, r, x;
    for (int i = 1; i <= M; i++)
    {
        scanf("%d", &opt);
        if (opt == 3)
        {
            scanf("%d%d", &l, &r);
            printf("%d\n", Query(root, 1, N, l, r));
        }
        else
        {
            scanf("%d%d%d", &l, &r, &x);
            if (opt == 1)
                And(root, 1, N, l, r, x);
            else
                Or(root, 1, N, l, r, x);
        }
    }
}

int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);
    root = build(1, N);
    solve();
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define IT vector<Node>::iterator
using namespace std;
const int mod = 998244353;
const long long INF = (1ll << 60) - 1;
struct Node
{
    long long l, r;
} a[105], b[105];
vector<Node> tmpa[70], tmpb[70], ans;
int ch[100000][2], na, nb, node_cnt, root;
int newnode()
{
    int u = ++node_cnt;
    ch[u][0] = ch[u][1] = 0;
    return u;
}
void getnode1(int &rot, long long lt, long long rt, long long lq, long long rq, int d)
{
    if (!rot)
        rot = newnode(), tmpa[d].push_back((Node){lt, rt});
    if (lt >= lq && rt <= rq)
        return;
    long long mid = (lt + rt) >> 1;
    if (lq <= mid)
        getnode1(ch[rot][0], lt, mid, lq, rq, d + 1);
    if (rq > mid)
        getnode1(ch[rot][1], mid + 1, rt, lq, rq, d + 1);
}
void getnode2(long long lt, long long rt, long long lq, long long rq, int d)
{
    if (lt >= lq && rt <= rq)
    {
        tmpb[d].push_back((Node){lt, rt});
        return;
    }
    long long mid = (lt + rt) >> 1;
    if (lq <= mid)
        getnode2(lt, mid, lq, rq, d + 1);
    if (rq > mid)
        getnode2(mid + 1, rt, lq, rq, d + 1);
}
void solve()
{
    node_cnt = root = 0;
    for (int i = 0; i <= 60; i++)
        tmpa[i].clear(), tmpb[i].clear();
    for (int i = 1; i <= na; i++)
        getnode1(root, 0, INF, a[i].l, a[i].r, 0);
    for (int i = 1; i <= nb; i++)
        getnode2(0, INF, b[i].l, b[i].r, 0);
    for (int i = 1; i <= 60; i++)
        for (IT u = tmpa[i].begin(); u != tmpa[i].end(); u++)
            for (IT v = tmpb[i].begin(); v != tmpb[i].end(); v++)
            {
                long long low = v->l ^ v->r;
                ans.push_back((Node){(v->l ^ u->l) & (~low), (v->l ^ u->l) | low});
            }
}
int cmp(const Node &a, const Node &b) { return a.l < b.l; }
long long calc(long long l, long long r)
{
    l %= mod, r %= mod;
    return ((r - l + 1) * (l + r) >> 1);
}
int main()
{
    scanf("%d", &na);
    for (int i = 1; i <= na; i++)
        scanf("%lld%lld", &a[i].l, &a[i].r);
    scanf("%d", &nb);
    for (int i = 1; i <= nb; i++)
        scanf("%lld%lld", &b[i].l, &b[i].r);
    solve();
    swap(a, b), swap(na, nb);
    solve();
    sort(ans.begin(), ans.end(), cmp);
    if (ans.begin() == ans.end())
    {
        puts("0");
        return 0;
    }
    long long l = ans.begin()->l, r = ans.begin()->r;
    int totans = 0;
    for (IT i = ans.begin() + 1; i != ans.end(); i++)
    {
        if (i->l <= r + 1)
            r = max(r, i->r);
        else
            totans = (totans + calc(l, r)) % mod, l = i->l, r = i->r;
    }
    totans = (totans + calc(l, r)) % mod;
    cout << (totans + mod) % mod;
}
// By AcerMo
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int M = 100500;
struct edge
{
    int fr, to, w1;
    double w2;
} e[M];
vector<edge> v[M];
int la, ra;
int n, m, st, ed, nd;
int fa[M], sh[M], be[M], siz[M];
bool vis[M];
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x;
}
inline void constt()
{
    for (int i = 1; i <= nd; i++)
        fa[i] = i, siz[i] = 1;
    return;
}
inline bool cmp(edge a, edge b) { return a.w2 < b.w2; }
inline int find(int x)
{
    if (fa[x] != x)
        return fa[x] = find(fa[x]);
    return x;
}
inline void unionn(int a, int b)
{
    if (siz[a] <= siz[b])
        siz[b] += siz[a], fa[a] = b;
    else
        siz[a] += siz[b], fa[b] = a;
    return;
}
inline void kru(int lim)
{
    int cnt = 1;
    double qlm = 2e9;
    constt();
    for (int i = 1; i <= m; i++)
    {
        int r1 = find(e[i].fr);
        int r2 = find(e[i].to);
        if (e[i].w2 < lim)
            continue;
        qlm = min(qlm, e[i].w2);
        if (r1 != r2)
        {
            unionn(r1, r2);
            if (find(st) == find(ed))
                return (void)(la = (int)qlm, ra = (int)(e[i].w2 + 0.9999));
        }
    }
    return;
}
signed main()
{
    freopen("trip.in", "r", stdin);
    freopen("trip.out", "w", stdout);
    n = read();
    m = read();
    int l = 0, r = 0;
    for (int i = 1; i <= m; i++)
    {
        e[i].fr = read();
        e[i].to = read();
        e[i].w1 = read();
        r = max(r, e[i].w1);
        nd = max(nd, max(e[i].fr, e[i].to));
    }
    for (int i = 1; i <= n; i++)
    {
        int x = read(), y;
        while (x--)
            y = read(), be[y] = i;
    }
    for (int i = 1; i <= n; i++)
        sh[i] = read();
    for (int i = 1; i <= m; i++)
    {
        int r1 = be[e[i].fr], r2 = be[e[i].to];
        if (r1 != r2)
            e[i].w2 = (double)((double)e[i].w1 * (sh[r1] + sh[r2]) / 200.0);
        else
            e[i].w2 = (double)((double)(e[i].w1 * (sh[r1])) / 100.0);
    }
    sort(e + 1, e + m + 1, cmp);
    st = read();
    ed = read();
    while (l < r)
    {
        int mid = (l + r) >> 1;
        kru(mid);
        if (fa[ed] == fa[st])
            l = mid + 1;
        else
            r = mid;
    }
    cout << la << " " << ra;
    return 0;
}
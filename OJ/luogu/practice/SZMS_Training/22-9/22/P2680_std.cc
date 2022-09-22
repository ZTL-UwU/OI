#include <bits/stdc++.h>
#define LL long long
#define inf LONG_LONG_MAX
#define re register
#define he(x) for (register int i = head[x]; i; i = e[i].nxt)
using namespace std;
int n, m, sum[300100], lg[300010], f[300010][20], dep[300010], head[600010], tot;
int l, r, len[300010], val[300010], mid, ans;
struct CCF
{
    int nxt, to, val;
} e[600010];
struct IOI
{
    int u, v, dis, lca;
} p[300010];
template <class frd>
inline void read(frd &a)
{
    bool f = 0;
    a = 0;
    char ch = getchar();
    while (ch < 48 || ch > 57)
    {
        if (ch == '-')
            f = 1;
        ch = getchar();
    }
    while (ch >= 48 && ch <= 57)
        a = (a << 1) + (a << 3) + (ch ^ 48), ch = getchar();
    if (f)
        a = -a;
}
template <typename T>
inline void print(T x, char c = '\n')
{
    static int buf[40];
    if (x == 0)
    {
        putchar('0');
        putchar(c);
        return;
    }
    if (x < 0)
        putchar('-'), x = -x;
    for (buf[0] = 0; x; x /= 10)
        buf[++buf[0]] = (x % 10 ^ 48);
    while (buf[0])
        putchar(buf[buf[0]--]);
    putchar(c);
}
inline bool cmp(IOI ttt, IOI kkk) { return ttt.dis > kkk.dis; }
inline void add(int x, int y, int z)
{
    e[++tot].val = z;
    e[tot].to = y;
    e[tot].nxt = head[x];
    head[x] = tot;
}

void dfs1(int x, int fa)
{
    f[x][0] = fa;
    dep[x] = dep[fa] + 1;
    for (int i = 1; (1 << i) <= dep[x]; i++)
    {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int y = e[i].to;
        if (y == fa)
            continue;
        len[y] = len[x] + e[i].val;
        val[y] = e[i].val;
        dfs1(y, x);
    }
}

int lca(int x, int y)
{
    if (dep[x] < dep[y])
        std::swap(x, y);
    while (dep[x] > dep[y])
        x = f[x][lg[dep[x] - dep[y]] - 1];

    if (x == y)
        return x;
    for (int i = lg[dep[x]] - 1; i >= 0; i--)
    {
        if (f[x][i] != f[y][i])
        {
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

void dfs2(int x, int f)
{
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int y = e[i].to;
        if (y == f)
            continue;
        dfs2(y, x);
        sum[x] += sum[y];
    }
}
inline bool check(int lim)
{
    int cnt = 0, maxn = 0;
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= m; i++)
    {
        if (p[i].dis <= lim)
            break;
        sum[p[i].u]++;
        sum[p[i].v]++;
        sum[p[i].lca] -= 2;
        cnt++;
    }
    dfs2(1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (sum[i] == cnt)
            maxn = max(maxn, val[i]);
    }
    return p[1].dis - maxn <= lim;
}
int main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    read(n);
    read(m);
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        read(u);
        read(v);
        read(w);
        l = max(l, w);
        add(u, v, w);
        add(v, u, w);
    }
    for (int i = 1; i <= n; i++)
        lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
    dfs1(1, 0);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        read(p[i].u);
        read(p[i].v);
        p[i].lca = lca(p[i].u, p[i].v);
        p[i].dis = len[p[i].u] + len[p[i].v] - (len[p[i].lca] << 1);
        r = max(r, p[i].dis);
    }
    sort(p + 1, p + m + 1, cmp);
    l = r - l;
    while (l <= r)
    {
        mid = (l + r) >> 1;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << ans;
    fclose(stdin);
    fclose(stdout);
    return 0;
}
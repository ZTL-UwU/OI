#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
#define LL long long

inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar())
        x = x * 10 + c - '0';
    return x * f;
}
const int INF = 2147483600;
const int MAXN = 501000;

int N;
int a[MAXN + 1];
int cnt, tim;
int Next[MAXN << 1], Node[MAXN << 1], Root[MAXN << 1];
int dfn[MAXN + 1], Hvs[MAXN + 1], fa[MAXN + 1], dep[MAXN + 1];
int sz[MAXN + 1];
int top[MAXN + 1];

inline void insert(int u, int v)
{
    Node[++cnt] = v;
    Next[cnt] = Root[u];
    Root[u] = cnt;
    return;
}
inline void dfs(int k, int Fa)
{
    dep[k] = dep[Fa] + 1;
    sz[k] = 1;
    Hvs[k] = -1;
    fa[k] = Fa;
    for (int x = Root[k]; x; x = Next[x])
    {
        int v = Node[x];
        if (v == Fa)
            continue;
        dfs(v, k);
        sz[k] += sz[v];
        if (Hvs[k] == -1 || sz[Hvs[k]] < sz[v])
            Hvs[k] = v;
    }
    return;
}
inline void dfs2(int k, int tp)
{
    top[k] = tp;
    dfn[k] = ++tim;
    if (Hvs[k] != -1)
        dfs2(Hvs[k], tp);
    else
        return;
    for (int x = Root[k]; x; x = Next[x])
    {
        int v = Node[x];
        if (v == fa[k] || v == Hvs[k])
            continue;
        dfs2(v, v);
    }
    return;
}
int c[MAXN + 1];
inline int lowbit(int x) { return x & (-x); }
inline void Add(int i, int k)
{
    for (int x = i; x <= N; x += lowbit(x))
        c[x] ^= k;
    return;
}
inline int Query(int i)
{
    int res = 0;
    for (int x = i; x; x -= lowbit(x))
        res ^= c[x];
    return res;
}
inline int Que(int x, int y)
{
    int fx = top[x], fy = top[y], ans = 0;
    while (fx != fy)
    {
        if (dep[fx] > dep[fy])
            ans = ans ^ Query(dfn[x]) ^ Query(dfn[fx] - 1), x = fa[fx];
        else
            ans = ans ^ Query(dfn[y]) ^ Query(dfn[fy] - 1), y = fa[fy];
        fx = top[x], fy = top[y];
    }
    if (dep[x] < dep[y])
        ans = ans ^ Query(dfn[y]) ^ Query(dfn[x] - 1);
    else
        ans = ans ^ Query(dfn[x]) ^ Query(dfn[y] - 1);
    return ans;
}
char str[MAXN + 1];

int main()
{
    ios::sync_with_stdio(0);
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    N = read();
    for (int i = 1; i <= N; i++)
        a[i] = read();
    for (int i = 2; i <= N; i++)
    {
        int u = read(), v = read();
        insert(u, v);
        insert(v, u);
    }
    dfs(1, 0);
    dfs2(1, 1);
    int Q = read();
    for (int i = 1; i <= N; i++)
        Add(dfn[i], a[i]);
    while (Q--)
    {
        scanf("%s", str);
        if (str[0] == 'Q')
        {
            int u = read(), v = read();
            if (Que(u, v))
                puts("Yes");
            else
                puts("No");
        }
        else
        {
            int u = read(), v = read();
            Add(dfn[u], a[u] ^ v);
            a[u] = v;
        }
    }
    return 0;
}
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <set>
#define LL long long
#define N 100010
using namespace std;

set<int> s;
typedef set<int>::iterator It;
struct info
{
    int to, nex, w;
} e[N * 2];
int n, m, _log, tot, head[N * 2];
int dep[N], f[N][20], p[N], dfn[N];
LL dis[N][20], Ans;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline void add_edge(int u, int v, int w)
{
    e[++tot].to = v;
    e[tot].nex = head[u];
    head[u] = tot;
    e[tot].w = w;
}

void dfs(int u, int fa)
{
    for (int i = 1; i <= _log; ++i)
    {
        f[u][i] = f[f[u][i - 1]][i - 1];
        dis[u][i] = dis[u][i - 1] + dis[f[u][i - 1]][i - 1];
    }

    for (int i = head[u]; i; i = e[i].nex)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        f[v][0] = u;
        dis[v][0] = e[i].w;
        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
}

LL LCA(int u, int v)
{
    LL res = 0;
    if (dep[u] > dep[v])
        swap(u, v);
    int d = dep[v] - dep[u];

    for (int i = 0; i <= _log; ++i)
        if (d & (1 << i))
            res += dis[v][i], v = f[v][i];

    if (u == v)
        return res;

    for (int i = _log; i >= 0; i--)
        if (f[u][i] != f[v][i])
        {
            res += dis[u][i] + dis[v][i];
            u = f[u][i];
            v = f[v][i];
        }

    return res + dis[u][0] + dis[v][0];
}

void dddfs(int u)
{
    dfn[u] = ++tot;
    p[tot] = u;

    for (int i = head[u]; i; i = e[i].nex)
    {
        int v = e[i].to;
        if (!dfn[v])
            dddfs(v);
    }
}

inline It L(It it)
{
    if (it == s.begin())
        return --s.end();
    return --it;
}

inline It R(It it)
{
    if (it == --s.end())
        return s.begin();
    return ++it;
}

int main()
{
    n = read();
    _log = log(n) / log(2);
    for (int i = 1; i < n; ++i)
    {
        int u = read(), v = read(), w = read();
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    dfs(1, 0);
    tot = 0;
    dddfs(1);

    m = read();
    while (m--)
    {
        int ch = getchar();
        while (ch != '+' && ch != '-' && ch != '?')
            ch = getchar();
        It it;
        int t;
        if (ch == '?')
            printf("%lld\n", Ans / 2);
        else
        {
            int x = read();
            if (ch == '+')
            {
                if (s.size())
                {
                    it = s.lower_bound(dfn[x]);
                    if (it == s.end())
                        it = s.begin();
                    t = *L(it);
                    Ans += LCA(x, p[t]) + LCA(x, p[*it]) - LCA(p[t], p[*it]);
                }
                s.insert(dfn[x]);
            }
            else
            {
                it = s.find(dfn[x]);
                t = *L(it), it = R(it);
                Ans -= LCA(x, p[t]) + LCA(x, p[*it]) - LCA(p[t], p[*it]);
                s.erase(dfn[x]);
            }
        }
    }
    return 0;
}
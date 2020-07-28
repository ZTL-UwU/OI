#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i <= b; ++i)
#define dep(i, a, b) for (int i = a; i >= b; --i)
using namespace std;
const int MAXN = 2010;
const int INF = 0x7fffffff;
int read()
{
    int sum = 0, flag = 1;
    char c;
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            flag = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        sum = (sum << 1) + (sum << 3) + c - '0';
    return sum * flag;
}
int n, m;
int link[MAXN], tot = 1;
int d[MAXN];
struct edge
{
    int y, v, next;
} e[MAXN << 1];
int in[MAXN];
int ans;
void insert(int x, int y, int v)
{
    e[++tot].y = y;
    e[tot].v = v;
    e[tot].next = link[x];
    link[x] = tot;
    e[++tot].y = x;
    e[tot].v = 0;
    e[tot].next = link[y];
    link[y] = tot;
}
void init()
{
    m = read();
    n = read();
    int x, y, z, t = 2 + n + m;
    rep(i, 1, m)
    {
        x = read();
        insert(1, i + 1, x);
    }
    rep(i, 1, n)
    {
        x = read();
        rep(j, 1, x)
        {
            y = read();
            if (!in[y])
            {
                insert(1 + y, m + 1 + i, INF);
                in[y] = i + 1 + m;
            }
            else
                insert(in[y], m + 1 + i, INF);
        }
        z = read();
        insert(m + 1 + i, t, z);
    }
    n = t;
}
int head, tail;
int q[MAXN];
bool check = true;
int fd;
void bfs()
{
    memset(d, -1, sizeof(d));
    head = tail = 0;
    q[++tail] = 1;
    d[1] = 0;
    while (head < tail)
    {
        int k = q[++head];
        for (int i = link[k]; i; i = e[i].next)
            if (e[i].v && d[e[i].y] < 0)
            {
                d[e[i].y] = d[k] + 1;
                q[++tail] = e[i].y;
            }
    }
    if (d[n] != -1)
        check = true;
}
int dfs(int k, int l)
{
    if (k == n)
        return l;
    int maxl = 0;
    for (int i = link[k]; i && maxl < l; i = e[i].next)
    {
        if (d[e[i].y] == d[k] + 1 && e[i].v)
        {
            if (fd = dfs(e[i].y, min(e[i].v, l - maxl)))
            {
                maxl += fd;
                e[i].v -= fd;
                e[i ^ 1].v += fd;
            }
        }
    }
    if (!maxl)
        d[k] = -1;
    return maxl;
}
void dinic()
{
    while (check)
    {
        check = false;
        bfs();
        if (!check)
            break;
        while (fd = dfs(1, INF))
            ans += fd;
    }
}
int main()
{
    init();
    dinic();
    printf("%d\n", ans);
    return 0;
}
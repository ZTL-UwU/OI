#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
struct node
{
    int to, v, next;
} e[20010];
int n, tot, k, root, N, ans, t;
int head[10010], f[10010], vis[10010], siz[10010], dis[10010], a[10010], INF = 0x7fffffff;

void addedge(int x, int y, int v)
{
    e[++tot].next = head[x];
    head[x] = tot;
    e[tot].v = v;
    e[tot].to = y;
}
void getroot(int x, int fa)
{
    siz[x] = 1;
    f[x] = 0;
    for (int i = head[x]; i; i = e[i].next)
    {
        if (e[i].to == fa || vis[e[i].to])
            continue;
        getroot(e[i].to, x);
        siz[x] += siz[e[i].to];
        f[x] = max(f[x], siz[e[i].to]);
    }
    f[x] = max(f[x], N - siz[x]);

    if (f[x] < f[root])
        root = x;
}
void getdis(int x, int fa)
{
    a[++t] = dis[x];
    for (int i = head[x]; i; i = e[i].next)
    {
        if (e[i].to == fa || vis[e[i].to])
            continue;
        dis[e[i].to] = dis[x] + e[i].v;
        getdis(e[i].to, x);
    }
}
int cal(int x, int v)
{
    dis[x] = v;
    t = 0;
    getdis(x, 0);
    sort(a + 1, a + t + 1);
    int l = 1, r = t, ans1 = 0;
    while (l < r)
    {
        if (a[l] + a[r] <= k)
        {
            ans1 += r - l;
            l++;
        }
        else
            r--;
    }
    return ans1;
}
void solve(int x)
{
    ans += cal(x, 0);
    vis[x] = 1;
    for (int i = head[x]; i; i = e[i].next)
    {
        if (vis[e[i].to])
            continue;
        ans -= cal(e[i].to, e[i].v);
        N = siz[e[i].to];
        root = 0;
        getroot(e[i].to, x);
        solve(root);
    }
}
int main()
{
    while (1)
    {
        ans = 0, root = 0, tot = 0;
        memset(vis, 0, sizeof(vis));
        memset(head, 0, sizeof(head));
        scanf("%d%d", &n, &k);
        if (n == 0 && k == 0)
            break;
        for (int i = 1; i < n; i++)
        {
            int x, y, v;
            scanf("%d%d%d", &x, &y, &v);
            addedge(x, y, v);
            addedge(y, x, v);
        }
        f[0] = INF;
        N = n;
        getroot(1, 0);
        solve(root);
        printf("%d\n", ans);
    }
    return 0;
}

/** 
20 10
1 2 3
2 3 4
3 4 5
4 5 6
5 6 7
6 7 8
7 8 9
8 9 10
9 10 11
10 11 12
11 12 13
12 13 14
13 14 15
14 15 16
15 16 17
16 17 18
17 18 19
18 19 20
19 20 21
0 0
**/
//10

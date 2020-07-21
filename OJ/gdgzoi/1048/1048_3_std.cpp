#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;
struct JOKER
{
    int b, next, v;
} e[200007];
int n, tot, ans, id, f[100007], head[100007];
int tree[10000007][2];
bool vis[100007];
void add(int x, int y, int z)
{
    e[++tot].b = y;
    e[tot].v = z;
    e[tot].next = head[x];
    head[x] = tot;
}
void dfs(int u)
{
    vis[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].b;
        if (!vis[v])
        {
            f[v] = f[u] ^ e[i].v;
            dfs(v);
        }
    }
}
void insert(int x)
{
    int now = 1;
    for (int i = 31; i >= 0; i--)
    {
        int t;
        if (!(x & (1 << i)))
            t = 0;
        else
            t = 1;
        if (!tree[now][t])
            tree[now][t] = ++id;
        cout << id << endl;
        now = tree[now][t];
    }
}
int joker(int x)
{
    int now = 1, res = 0;
    for (int i = 31; i >= 0; i--)
    {
        int t;
        if (!(x & (1 << i)))
            t = 1;
        else
            t = 0;
        if (tree[now][t])
        {
            res = res * 2 + 1;
            now = tree[now][t];
        }
        else
        {
            res *= 2;
            now = tree[now][1 - t];
        }
    }
    return res;
}
int main()
{
    id = 1;
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
    {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
    }

    f[1] = 0;
    dfs(1);

    for (int i = 1; i <= n; i++)
        insert(f[i]);
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i]);
    for (int i = 1; i <= n; i++)
        ans = max(ans, joker(f[i]));
    printf("%d\n", ans);
    return 0;
}
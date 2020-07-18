#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXNN = 300010;
const int MAXN = 600010;
vector<int> g[MAXNN];
int rmq[MAXN][21];
int first[MAXNN];
int deep[MAXN];
int sum[MAXNN];
int num[MAXN];
int lg[MAXN];
int a[MAXNN];
int size;
inline int lowbit(int x) { return x & (-x); }
void update(int x, int k)
{
    while (x <= size)
    {
        sum[x] += k;
        x += lowbit(x);
    }
}
inline int query(int x)
{
    int res = 0;
    while (x > 0)
    {
        res += sum[x];
        x -= lowbit(x);
    }
    return res;
}
inline int lca(int x, int y)
{
    int l = min(first[x], first[y]);
    int r = max(first[x], first[y]);
    int k = lg[r - l + 1];
    int res = num[deep[rmq[l][k]] < deep[rmq[r - (1 << k) + 1][k]] ? rmq[l][k] : rmq[r - (1 << k) + 1][k]];
    return res;
}
void dfs(int u, int d, int fa)
{
    first[u] = ++ size;
    deep[size] = d;
    num[size] = u;
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, d + 1, u);
        deep[++ size] = d;
        num[size] = u;
    }
}
int main()
{
    lg[0] = -1;
    for (int i = 1; i < MAXN; i ++) lg[i] = lg[i >> 1] + 1;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    for (int i = 0; i < n - 1; i ++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 1, -1);
    for (int i = 1; i <= size; i ++) rmq[i][0] = i;
    for (int i = 1; i <= 20; ++ i)
        for (int j = 1; j + (1 << i) + 1 <= size; ++ j)
            rmq[j][i] = deep[rmq[j][i - 1]] < deep[rmq[j + (1 << (i - 1))][i - 1]] ? rmq[j][i - 1] : rmq[j + (1 << (i - 1))][i - 1];
    for (int i = 0; i < n - 1; i ++)
    {
        int p = lca(a[i], a[i + 1]);
        update(a[i], 1);
        update(p, -1);
        update(a[i + 1], 1);
        update(p, -1);
    }
    for (int i = 0; i < n; i ++)
    {
        int res = query(i);
        printf("%d\n", res);
    }
    return 0;
}
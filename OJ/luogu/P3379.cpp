#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 500010;
vector<int> g[MAXN];
int fa[MAXN][20];
int deep[MAXN];
int lg[MAXN];
void dfs(int u, int f)
{
    fa[u][0] = f;
    deep[u] = deep[f] + 1;
    for (int i = 1; i <= lg[deep[u]]; i ++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 0; i < g[u].size(); i ++)
        if (g[u][i] != f)
            dfs(g[u][i], u);
}
int lca(int x, int y)
{
    if (deep[x] < deep[y]) swap(x, y);
    while (deep[x] > deep[y])
        x = fa[x][lg[deep[x] - deep[y]] - 1];
    if (x == y) return x;
    for (int i = lg[deep[x]] - 1; i >= 0; i --)
        if (fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int main()
{
    for (int i = 1; i < MAXN; i ++) lg[i] = lg[i >> 1] + 1;
    int n, q, s;
    scanf("%d %d %d", &n, &q, &s);
    for (int i = 0; i < n - 1; i ++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(s, 0);
    for (int i = 0; i < q; i ++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        int res = lca(x, y);
        printf("%d\n", res);
    }
    return 0;
}
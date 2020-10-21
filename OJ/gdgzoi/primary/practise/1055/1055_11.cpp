#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 50010;
vector<int> g[MAXN];
int fa[MAXN][20];
int deep[MAXN];
int lg[MAXN];
int in[MAXN];
int n;
void init()
{
    for (int i = 0; i < MAXN; i ++) g[i].clear();
    memset(deep, 0, sizeof(deep));
    memset(in, 0, sizeof(in));
    memset(fa, 0, sizeof(fa));
}
void dfs(int u)
{
    for (int i = 1; i <= lg[deep[u]]; i ++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        deep[v] = deep[u] + 1;
        fa[v][0] = u;
        dfs(v);
    }
}
int lca(int x, int y)
{
    if (deep[y] < deep[x]) swap(x, y);
    while (deep[x] < deep[y]) y = fa[y][lg[deep[y] - deep[x]] - 1];
    if (x != y)
    {
        for (int i = lg[deep[x]] - 1; i >= 0; i --)
            if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
        x = fa[x][0];
    }
    return x;
}
int main()
{
    for (int i = 1; i < MAXN; i ++) lg[i] = lg[i / 2] + 1;
    int t;
    scanf("%d", &t);
    while (t --)
    {
        init();
        scanf("%d", &n);
        for (int i = 0; i < n - 1; i ++)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            g[u].push_back(v);
            in[v] ++;
        }
        int root;
        for (int i = 1; i <= n; i ++) if (!in[i]) { root = i; break; }
        dfs(root);
        int x, y;
        scanf("%d %d", &x, &y);
        int res = lca(x, y);
        printf("%d\n", res);
    }
    return 0;
}
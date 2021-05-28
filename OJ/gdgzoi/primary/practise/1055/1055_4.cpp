#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 50010;
vector<data> g[MAXN];
vector<data> s[MAXN];
int first[MAXN];
int f[MAXN][30];
int deep[MAXN];
int num[MAXN];
data fa[MAXN];
int lg[MAXN];
int size;
int lca;
int check(int u)
{
    if (u == lca)
        return 0;
    return check(fa[u].v) + fa[u].w;
}
void dfs(int u, int d, int father)
{
    first[u] = ++size;
    fa[u].v = father;
    deep[size] = d;
    num[size] = u;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i].v;
        if (v == father)
        {
            fa[u].w = g[u][i].w;
            continue;
        }
        dfs(v, d + 1, u);
        num[++size] = u;
        deep[size] = d;
    }
}
int main()
{
    lg[0] = -1;
    for (int i = 1; i < MAXN; i++)
        lg[i] = lg[i / 2] + 1;
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        char dum;
        scanf("%d %d %d %c", &u, &v, &w, &dum);
        g[u].push_back((data){v, w});
        g[v].push_back((data){u, w});
    }
    dfs(1, 1, -1);
    for (int i = 1; i <= size; i++)
        f[i][0] = i;
    for (int i = 1; i < 25; i++)
        for (int j = 0; j + (1 << i) + 1 <= size; j++)
            f[j][i] =
                deep[f[j][i - 1]] < deep[f[j + (1 << (i - 1))][i - 1]] ? f[j][i - 1] : f[j + (1 << (i - 1))][i - 1];
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        int l = first[x], r = first[y];
        if (l > r)
            swap(l, r);
        int k = lg[r - l + 1];
        lca = num[deep[f[l][k]] < deep[f[r - (1 << k) + 1][k]] ? f[l][k] : f[r - (1 << k) + 1][k]];
        // cout << lca << endl;
        int ans = check(num[l]) + check(num[r]);
        printf("%d\n", ans);
    }
    return 0;
}
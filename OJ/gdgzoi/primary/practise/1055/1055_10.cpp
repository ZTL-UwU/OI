#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 100010;
const int MAXNN = 50100;
int lg[MAXN];
int num[MAXN];
int dis[MAXNN];
int deep[MAXN];
int first[MAXNN];
int rmq[MAXN][20];
vector<data> g[MAXNN];
int size;
inline int lca(int x, int y)
{
    int l = min(first[x], first[y]);
    int r = max(first[x], first[y]);
    int k = lg[r - l + 1];
    return num[deep[rmq[l][k]] < deep[rmq[r - (1 << k) + 1][k]] ? rmq[l][k] : rmq[r - (1 << k) + 1][k]];
}
void dfs(int u, int d, int fa)
{
    first[u] = ++size;
    deep[size] = d;
    num[size] = u;
    for (int i = 0; i < g[u].size(); ++i)
    {
        int v = g[u][i].v, w = g[u][i].w;
        if (v == fa)
            continue;
        dis[v] = dis[u] + w;
        dfs(v, d + 1, u);
        deep[++size] = d;
        num[size] = u;
    }
}
int main()
{
#ifdef WIN32
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    lg[0] = -1;
    for (int i = 1; i < MAXN; ++i)
        lg[i] = lg[i >> 1] + 1;
    int n, u, v, w, q, x, y, z;
    cin >> n >> q;
    for (int i = 0; i < n - 1; ++i)
    {
        cin >> u >> v;
        g[u].push_back((data){v, 1});
        g[v].push_back((data){u, 1});
    }
    dfs(1, 1, -1);
    for (int i = 1; i <= size; ++i)
        rmq[i][0] = i;
    for (int i = 1; i <= 18; ++i)
        for (int j = 1; j + (1 << i) + 1 <= size; ++j)
            rmq[j][i] = deep[rmq[j][i - 1]] < deep[rmq[j + (1 << (i - 1))][i - 1]] ? rmq[j][i - 1] :
                                                                                     rmq[j + (1 << (i - 1))][i - 1];
    for (int i = 0; i < q; ++i)
    {
        int point, cost;
        cin >> x >> y >> z;
        int lca1 = lca(x, y);
        int lca2 = lca(y, z);
        int lca3 = lca(x, z);
        if (lca1 == lca2)
            point = lca3;
        else if (lca2 == lca3)
            point = lca1;
        else
            point = lca2;
        cost = dis[x] + dis[y] + dis[z] - dis[lca1] - dis[lca2] - dis[lca3];
        cout << point << " " << cost << '\n';
    }
    return 0;
}
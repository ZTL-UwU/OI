#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
struct data { int v, w; };
const int MAXNN = 40010;
const int MAXN = 90010;
vector<data> g[MAXN];
int rmq[MAXN][20];
int first[MAXNN];
int deep[MAXN];
int num[MAXN];
int dis[MAXN];
int lg[MAXN];
int size;
inline int lca(int x, int y)
{
    int l = min(first[x], first[y]);
    int r = max(first[x], first[y]);
    int k = lg[r - l + 1];
    return num[deep[rmq[l][k]] < deep[rmq[r - (1 << k) + 1][k]] ? rmq[l][k] : rmq[r - (1 << k) + 1][k]];
}
void init()
{
    for (int i = 0; i < MAXNN; i ++) g[i].clear();
    memset(first, 0, sizeof(first));
    memset(deep, 0, sizeof(deep));
    memset(num, 0, sizeof(num));
    memset(dis, 0, sizeof(dis));
    size = 0;
}
void dfs(int u, int d, int fa)
{
    first[u] = ++ size;
    deep[size] = d;
    num[size] = u;
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i].v, w = g[u][i].w;
        if (v == fa) continue;
        dis[v] = dis[u] + w;
        dfs(v, d + 1, u);
        deep[++ size] = d;
        num[size] = u;
    }
}
int main()
{
    lg[0] = -1;
    for (int i = 1; i < MAXN; i ++) lg[i] = lg[i >> 1] + 1;
    ios::sync_with_stdio(false);
    cout.tie(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t --)
    {
        init();
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n - 1; i ++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].push_back((data){v, w});
            g[v].push_back((data){u, w});
        }
        dfs(1, 1, -1);
        for (int i = 1; i <= size; i ++) rmq[i][0] = i;
        for (int i = 1; i <= 19; i ++)
            for (int j = 1; j + (1 << i) + 1 <= size; j ++)
                rmq[j][i] = deep[rmq[j][i - 1]] < deep[rmq[j + (1 << (i - 1))][i - 1]] ? rmq[j][i - 1] : rmq[j + (1 << (i - 1))][i - 1];
        for (int i = 0; i < q; i ++)
        {
            int x, y;
            cin >> x >> y;
            cout << dis[x] + dis[y] - 2 * dis[lca(x, y)] << '\n';
        }
    }
    return 0;
}
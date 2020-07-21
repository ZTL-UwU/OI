#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 200010;
vector<data> g[MAXN];
int maxn[MAXN];
int dp[MAXN];
void dfs1(int u, int fa)
{
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i].v, w = g[u][i].w;
        if (v != fa)
        {
            dfs1(v, u);
            maxn[u] = max(maxn[u], min(w, maxn[v]));
        }
    }
}
void dfs2(int u, int fa)
{
    
}
int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i ++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u].push_back((data){v, w});
            g[v].push_back((data){u, w});
        }
    }
    dfs1(1, -1);
    return 0;
}
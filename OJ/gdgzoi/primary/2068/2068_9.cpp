#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
struct data
{
    int v, w;
};
const int MAXN = 20000;
vector<data> g[MAXN];
int dis[MAXN];
void dfs1(int u, int fa)
{
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i].v;
        int w = g[u][i].w;
        if (v != fa)
        {
            dfs1(v, u);
            dis[u] = max(dis[u], dis[v] + w);
        }
    }
}
void dfs2(int u, int fa)
{
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i].v;
        int w = g[u][i].w;
        if (v != fa)
        {
            dfs2(v, u);
            
        }
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 2; i <= n - 1; i ++)
    {
        int v, w;
        cin >> v >> w;
        g[i].push_back((data){v, w});
    }
    dfs1(1, -1);
    return 0;
}
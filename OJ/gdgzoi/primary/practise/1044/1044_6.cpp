#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
const int MAXN = 10000;
vector<int> g[MAXN];
int dfn[MAXN];
int low[MAXN];
bool iscp[MAXN];
bool vis[MAXN];
int tt;
void dfs(int u, int fa)
{
    vis[u] = true;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!vis[v] && v != fa)
            dfs(v, u);
    }
}
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++tt;
    int ch = 0;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!dfn[v])
        {
            tarjan(v, u);
            ch++;
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
                iscp[u] = true;
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
    if (fa == -1 && ch == 1)
        iscp[u] = false;
}
int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    tarjan(1, -1);
    vector<int> ans;
    for (int i = 2; i < n; i++)
    {
        if (iscp[i])
        {
            memset(vis, 0, sizeof(vis));
            vis[i] = true;
            dfs(1, -1);
            if (!vis[i])
                ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    return 0;
}
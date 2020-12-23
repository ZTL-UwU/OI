#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
const int MAXN = 20000;
vector<int> g[MAXN];
int dfn[MAXN];
int low[MAXN];
bool iscp[MAXN];
bool vis[MAXN];
int tt;
int n, m;
const int INF = 0x7fffffff;
void init()
{
    n = 0, m = 0;
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(iscp, 0, sizeof(iscp));
    tt = 0;
}
void dfs(int u, int cut)
{
    vis[u] = true;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!vis[v] && v != cut)
        {
            dfs(v, cut);
        }
    }
}
int check(int cut)
{
    memset(vis, 0, sizeof(vis));
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i] && i != cut)
        {
            dfs(i, cut);
            res++;
        }
    }
    return res;
}
void tarjan(int u, int fa)
{
    int ch = 0;
    dfn[u] = low[u] = ++tt;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (v == fa)
            continue;
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
    while (1)
    {
        init();
        cin >> n >> m;
        if (!n && !m)
            return 0;
        for (int i = 0; i < m; i++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 1; i <= n; i++)
            if (!dfn[i])
                tarjan(i, -1);
        int maxn = -INF;
        for (int i = 1; i <= n; i++)
        {
            if (iscp[i])
            {
                int tmp = check(i);
                maxn = max(maxn, tmp);
            }
        }
        cout << maxn << endl;
    }
    return 0;
}

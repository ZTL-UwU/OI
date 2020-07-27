#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
const int MAXN = 20010;
vector<int> g[MAXN];
queue<int> q;
bool used[MAXN];
bool vis[MAXN];
int val[MAXN];
int in[MAXN];
int n, m;
int num;
int sum;
void init()
{
    for (int i = 0; i < MAXN; i ++) g[i].clear();
    while (!q.empty()) q.pop();
    memset(used, 0, sizeof(used));
    memset(vis, 0, sizeof(vis));
    memset(val, 0, sizeof(val));
    memset(in, 0, sizeof(in));
    n = m = num = sum = 0;
}
void topo()
{
    for (int i = 1; i <= n; i ++) if (in[i] == 1) q.push(i);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        used[u] = true;
        for (int i = 0; i < g[u].size(); i ++)
        {
            int v = g[u][i];
            in[v] --;
            if (in[v] == 1) q.push(v);
        }
    }
}
void dfs(int u, int fa)
{
    num ++;
    sum += val[u];
    for (int i = 0; i < g[u].size(); i ++)
    {
        int v = g[u][i];
        if (v != fa && !vis[v] && !used[v])
        {
            vis[v] = true;
            dfs(v, u);
        }
    }
}
int check()
{
    int ans = 0;
    for (int i = 1; i <= n; i ++)
    {
        num = sum = 0;
        if (!vis[i] && !used[i]) dfs(i, 0);
        if (num % 2) ans += sum;
    }
    return ans;
}
int main()
{
    int t;
    cin >> t;
    while (t --)
    {
        init();
        cin >> n >> m;
        for (int i = 1; i <= n; i ++) cin >> val[i];
        for (int i = 0; i < m; i ++)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            in[v] ++;
            in[u] ++;
        }
        topo();
        cout << check() << endl;
    }
    return 0;
}
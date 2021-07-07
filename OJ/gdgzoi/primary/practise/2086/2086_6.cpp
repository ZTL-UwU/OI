#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
const int MAXN = 50010;
const int INF = 0x7fffffff;
vector<int> g[MAXN];
int father[MAXN];
int subtree[MAXN];
int ans[MAXN];
void dfs(int u, int fa)
{
    subtree[u] = 1;
    father[u] = fa;
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (v != fa)
        {
            dfs(v, u);
            subtree[u] += subtree[v];
        }
    }
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, -1);
    int minn = INF;
    for (int i = 1; i <= n; i++)
    {
        int maxn = n - subtree[i];
        for (int j = 0; j < g[i].size(); j++)
        {
            int v = g[i][j];
            if (v != father[i])
                maxn = max(maxn, subtree[g[i][j]]);
        }
        ans[i] = maxn;
        minn = min(minn, maxn);
    }
    for (int i = 1; i <= n; i++)
        if (ans[i] == minn)
            cout << i << ' ';
    return 0;
}

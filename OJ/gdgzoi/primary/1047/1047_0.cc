#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
const int MAXN = 1e3;
vector<int> g[MAXN];
int link[MAXN];
bool vis[MAXN];
int n, m;
bool hungary_dfs(int u)
{
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!vis[v])
        {
            vis[v] = true;
            if (link[v] == 0 || hungary_dfs(link[v]))
            {
                link[v] = u;
                link[u] = v;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int ans = 0;
    for (int i = 1; i <= n + m; i++)
    {
        memset(vis, 0, sizeof(vis));
        if (hungary_dfs(i))
            ans++;
    }
    return ans;
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int p;
        while (1)
        {
            cin >> p;
            if (!p)
                break;
            g[p].push_back(m + i);
        }
    }
    cout << hungary();
    return 0;
}
#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 3e3;
vector<int> g[MAXN];
int link[MAXN];
bool vis[MAXN];
int m, n;
bool hungary_dfs(int u)
{
    for (int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if (!vis[v])
        {
            vis[v] = true;
            if (link[v] == -1 || hungary_dfs(link[v]))
            {
                link[v] = u;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        memset(vis, 0, sizeof(vis));
        if (hungary_dfs(i))
            ans++;
        else
            break;
    }
    return ans;
}
int main()
{
    memset(link, -1, sizeof(link));
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        g[i].push_back(x + m);
        if (x != y)
            g[i].push_back(y + m);
    }
    cout << hungary();
    return 0;
}
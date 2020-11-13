#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 210;
int g[MAXN][MAXN];
int depth[MAXN];
int cur[MAXN];
int n, m, s, t;
bool dinic_bfs()
{
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= n; i++)
        {
            if (!depth[i] && g[u][i])
            {
                depth[i] = depth[u] + 1;
                q.push(i);
            }
        }
    }
    if (!depth[t])
        return false;
    return true;
}
int dinic_dfs(int u, int minn)
{
    if (u == t)
        return minn;
    for (int &i = cur[u]; i <= n; i++)
    {
        if (depth[i] == depth[u] + 1 && g[u][i])
        {
            int tmp = dinic_dfs(i, min(minn, g[u][i]));
            if (tmp > 0)
            {
                g[u][i] -= tmp;
                g[i][u] += tmp;
                return tmp;
            }
        }
    }
    return 0;
}
long long dinic()
{
    long long ans = 0;
    while (dinic_bfs())
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (g[i][j])
                {
                    cur[i] = j;
                    break;
                }
            }
        }
        int tmp;
        while (tmp = dinic_dfs(s, INF))
            ans += tmp;
    }
    return ans;
}
int main()
{
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u][v] += w;
    }
    cout << dinic();
    return 0;
}
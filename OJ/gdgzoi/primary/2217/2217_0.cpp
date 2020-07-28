#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 410;
int s, n, f, d, t;
int g[MAXN][MAXN];
int depth[MAXN];
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
        for (int i = s; i <= t; i++)
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
    for (int i = s; i <= t; i++)
    {
        if (depth[i] == depth[u] + 1 && g[u][i])
        {
            int next = dinic_dfs(i, min(minn, g[u][i]));
            if (next > 0)
            {
                g[i][u] += next;
                g[u][i] -= next;
                return next;
            }
        }
    }
    return 0;
}
int dinic()
{
    int ans = 0;
    while (dinic_bfs())
    {
        int tmp;
        while (tmp = dinic_dfs(s, INF))
            ans++;
    }
    return ans;
}
int main()
{
    cin >> n >> f >> d;
    s = 0;
    t = n + f + d + 1;
    for (int i = 1; i <= n; i++)
    {
        int ff, dd;
        cin >> ff >> dd;
        for (int j = 0; j < ff; j++)
        {
            int fff;
            cin >> fff;
            g[s][fff] = 1;
            g[fff][f + i] = 1;
        }
        for (int j = 0; j < dd; j++)
        {
            int ddd;
            cin >> ddd;
            g[f + n + ddd][t] = 1;
            g[f + i][f + n + ddd] = 1;
        }
    }
    cout << dinic();
    return 0;
}
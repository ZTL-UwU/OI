#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 410;
int s, t, n, f, d;
int g[MAXN][MAXN];
int minn[MAXN];
int pre[MAXN];
int EK_bfs()
{
    memset(minn, 127, sizeof(minn));
    for (int i = 0; i < MAXN; i++)
        pre[i] = -1;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = s; i <= t; i++)
        {
            if (pre[i] == -1 && g[u][i])
            {
                pre[i] = u;
                minn[i] = min(minn[u], g[u][i]);
                q.push(i);
            }
        }
    }
    if (pre[t] == -1)
        return -1;
    return minn[t];
}
int EK()
{
    int ans = 0;
    while (1)
    {
        int tmp = EK_bfs();
        if (tmp == -1)
            break;
        int u = t;
        while (u != s)
        {
            g[u][pre[u]] += tmp;
            g[pre[u]][u] -= tmp;
            u = pre[u];
        }
        ans++;
    }
    return ans;
}
int main()
{
    cin >> n >> f >> d;
    s = 0;
    t = f + d + n + 1;
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
    cout << EK();
    return 0;
}
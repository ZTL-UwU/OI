#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
int g[1000][1000];
int n, f, d, s, t;
int minn[1000];
int pre[1000];
inline int EK_bfs()
{
    memset(minn, 127, sizeof(minn));
    for (int i = 0; i < 1000; i++)
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
                minn[i] = min(minn[u], g[u][i]);
                pre[i] = u;
                q.push(i);
            }
        }
    }
    if (pre[t] == -1)
        return -1;
    return minn[t];
}
inline int EK()
{
    int ans = 0;
    while (1)
    {
        int tmp = EK_bfs();
        if (tmp == -1)
            break;
        ans += tmp;
        int u = t;
        while (u != s)
        {
            g[u][pre[u]] += tmp;
            g[pre[u]][u] -= tmp;
            u = pre[u];
        }
    }
    return ans;
}
int main()
{
    cin >> n >> f >> d;
    s = 0;
    t = n + n + f + d + 1;
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
        g[f + i][f + n + i] = 1;
        for (int j = 0; j < dd; j++)
        {
            int ddd;
            cin >> ddd;
            g[f + n + i][f + n + n + ddd] = 1;
            g[f + n + n + ddd][t] = 1;
        }
    }
    cout << EK();
    return 0;
}
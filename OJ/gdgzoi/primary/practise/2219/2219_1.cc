#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v, w;
};
int minn[1000];
int pre[1000];
int g[1000][1000];
int n, m, s, t;
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
            g[pre[u]][u] -= tmp;
            g[u][pre[u]] += tmp;
            u = pre[u];
        }
    }
    return ans;
}
int main()
{
    int T;
    cin >> T;
    for (int tt = 1; tt <= T; tt++)
    {
        memset(g, 0, sizeof(g));
        cin >> n >> m;
        s = 1;
        t = n;
        for (int i = 0; i < m; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            g[u][v] = w;
        }
        cout << "Case " << tt << ": " << EK() << "\n";
    }
    return 0;
}
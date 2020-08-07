#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
int g[1000][1000];
int n, k, s, t;
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
        int u = t;
        ans += tmp;
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
    cin >> n >> k;
    s = 0;
    t = n + n + 1;
    for (int i = 1; i <= n; i++)
    {
        g[s][i] = k;
        g[n + i][t] = k;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            char ch;
            cin >> ch;
            if (ch == 'Y')
                g[i][n + j] = 1;
        }
    }
    cout << EK();
    return 0;
}
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
int s = 1, t = 26;
int g[100][100];
int minn[100];
int pre[100];
inline int transform(char c)
{
    if (c >= 'A' && c <= 'Z')
        return (c - 'A') + 1;
    return 27 + (c - 'a');
}
inline int EK_bfs()
{
    memset(minn, 127, sizeof(minn));
    for (int i = 0; i < 100; i++)
        pre[i] = -1;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int i = 1; i <= 52; i++)
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
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        char u, v;
        int w;
        cin >> u >> v >> w;
        int x = transform(u);
        int y = transform(v);
        g[x][y] += w;
    }
    cout << EK();
    return 0;
}
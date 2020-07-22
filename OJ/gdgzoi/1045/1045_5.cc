#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 2e3;
int g[MAXN][MAXN];
int minn[MAXN];
int pre[MAXN];
int m, n, s = 0, t;
int EK_bfs()
{
    memset(minn, 127, sizeof(minn));
    for (int i = 0; i < MAXN; i++) pre[i] = -1;
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
long long EK()
{
    long long ans = 0;
    while (1)
    {
        long long tmp = EK_bfs();
        if (tmp == -1)
            break;
        int u = t;
        while (u != s)
        {
            g[u][pre[u]] += tmp;
            g[pre[u]][u] -= tmp;
            u = pre[u];
        }
        ans += tmp;
    }
    return ans;
}
int main()
{
    cin >> m >> n;
    t = m + n + 1;
    for (int i = 1; i <= m; i++)
    {
        int p;
        cin >> p;
        g[s][i] = p;
    }
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        for (int j = 0; j < a; j++)
        {
            int k;
            cin >> k;
            bool flag = true;
            for (int l = 1; l <= n; l++)
                if (g[k][l])
                    flag = false;
            if (flag)
                g[k][m + 1] = INF;
        }
        int b;
        cin >> b;
        g[m + i][t] = b;
    }
    cout << EK();
    return 0;
}
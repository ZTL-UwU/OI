#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
const int INF = 0x7fffffff;
const int MAXN = 2e3;
int n, m, d, s, t;
int g[MAXN][MAXN];
string mp[MAXN];
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
            if (pre[i] == -1 && g[u][i] != 0)
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
int EK()
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
    cin >> n >> m >> d;
    s = 0;
    t = n * m * 2 + 10;
    for (int i = 1; i <= n; i++)
    {
        cin >> mp[i];
        mp[i] = "#" + mp[i];
        for (int j = 1; j <= m; j++)
        {
            int h = mp[i][j] - '0';
            if (h != 0)
            {
                int u = (i - 1) * m + j;
                int u1 = n * m + u;
                g[u][u1] = h;
                if (i <= d || j <= d || i > n - d || j > m - d)
                    g[u1][t] = INF;
            }
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int u = (i - 1) * m + j;
            int u1 = n * m + u;
            char c;
            cin >> c;
            if (c == 'L')
            {
                cnt++;
                g[s][u] = 1;
            }
            if (mp[i][j] - '0' != 0)
            {
                for (int k = 1; k <= n; k++)
                {
                    for (int l = 1; l <= m; l++)
                    {
                        int v = (k - 1) * m + l;
                        if ((mp[i][j] - '0' != 0) && (k != i || l != j)
                            && (d * d >= (i - k) * (i - k) + (j - l) * (j - l)))
                            g[u1][v] = INF;
                    }
                }
            }
        }
    }
    cout << cnt - EK();
    return 0;
}
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int x, y;
};
const int INF = 100;
const int MAXN = 1e3;
bool vis[MAXN][MAXN];
int n, m, d, s, t;
queue<data> q_tmp;
int g[MAXN][MAXN];
string map[30];
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
void bfs()
{
    while (!q_tmp.empty())
    {
        data u = q_tmp.front();
        q_tmp.pop();
        vis[u.x][u.y] = true;
        for (int i = -d; i <= d; i++)
        {
            for (int j = -(d - abs(i)); j <= d - abs(i); j++)
            {
                int x = u.x + i;
                int y = u.y + j;
                if (x > 0 && y > 0 && x <= n && y <= m && (map[x][y - 1] - '0') && !vis[x][y])
                {
                    q_tmp.push((data){x, y});
                    g[m * n + (u.x - 1) * n + u.y][(x - 1) * n + y] = INF;
                }
            }
        }
    }
}
int main()
{
    int cnt = 0;
    cin >> n >> m >> d;
    s = 0;
    t = n * m * 2 + 1;
    for (int i = 1; i <= n; i++)
        cin >> map[i];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int h = map[i][j - 1] - '0';
            if (h)
            {
                int u = (i - 1) * n + j;
                int v = m * n + u;
                g[u][v] = h;
                if (i <= d || j <= d || i >= n - d + 1 || j >= m - d + 1)
                    g[v][t] = INF;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        string tmp;
        cin >> tmp;
        for (int j = 1; j <= m; j++)
        {
            if (tmp[j - 1] == 'L')
            {
                cnt++;
                int u = (i - 1) * n + j;
                int v = m * n + u;
                g[s][u] = INF;
                q_tmp.push((data){i, j});
            }
        }
    }
    bfs();
    cout << cnt - EK();
    return 0;
}
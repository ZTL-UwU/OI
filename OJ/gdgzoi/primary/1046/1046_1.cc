#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 2e3 + 10;
struct data2
{
    int minn, dis;
};
struct data
{
    int v, w, f;
};
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int ans1, ans2, n, s, t;
vector<data> g[MAXN];
int cost[MAXN][MAXN];
bool inque[MAXN];
int minn[MAXN];
int dis[MAXN];
int pre[MAXN];
inline data2 EK_bfs()
{
    memset(inque, 0, sizeof(inque));
    memset(minn, 127, sizeof(minn));
    memset(dis, 127, sizeof(dis));
    for (int i = 0; i < MAXN; i++)
        pre[i] = -1;
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    inque[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            int f = g[u][i].f;
            if (w > 0 && dis[v] > dis[u] + f)
            {
                dis[v] = dis[u] + f;
                pre[v] = u;
                minn[v] = min(minn[u], w);
                if (!inque[v])
                {
                    inque[v] = true;
                    q.push(v);
                }
            }
        }
    }
    data2 res;
    if (pre[t] == -1)
        res.minn = -1;
    else
    {
        res.minn = minn[t];
        res.dis = dis[t];
    }
    return res;
}
inline void EK()
{
    while (1)
    {
        data2 tmp = EK_bfs();
        if (tmp.minn == -1)
            break;
        int u = t;
        while (u != s)
        {
            int tmp_f;
            for (int i = 0; i < g[pre[u]].size(); i++)
            {
                if (g[pre[u]][i].v == u)
                {
                    g[pre[u]][i].w -= tmp.minn;
                    tmp_f = g[pre[u]][i].f;
                }
            }
            bool found = false;
            for (int i = 0; i < g[u].size(); i++)
            {
                if (g[u][i].v == pre[u])
                {
                    g[u][i].w += tmp.minn;
                    found = true;
                }
            }
            if (!found)
                g[u].push_back((data){pre[u], tmp.minn, -tmp_f});
            u = pre[u];
        }
        ans1 += tmp.minn;
        ans2 += tmp.minn * tmp.dis;
    }
}
int main()
{
    cin >> n;
    s = 0;
    t = n * 10 + 1;
    ans1 = 0;
    ans2 = 0;
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int now = (i - 1) * n + j;
            g[now].push_back((data){5 * n + now, 1, 0});
            char ch;
            cin >> ch;
            if (ch == '@')
                g[s].push_back((data){now, 1, 0});
            else
                cost[i][j] = ch - '0';
        }
        g[5 * n + i * n].push_back((data){t, 1, 0});
    }
    for (int i = 1; i <= 5; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                int x = i + dir[k][0];
                int y = j + dir[k][1];
                if (x >= 1 && y >= 1 && x <= 5 && y <= n)
                    g[5 * n + (i - 1) * n + j].push_back((data){(x - 1) * n + y, 1, cost[x][y]});
            }
        }
    }
    EK();
    cout << ans2 << "\n";
    return 0;
}
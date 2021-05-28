#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 5e3 + 10;
struct data2
{
    int minn, dis;
};
struct data
{
    int v, w, f;
};
vector<data> g[MAXN];
bool inque[MAXN];
int minn[MAXN];
int pre[MAXN];
int dis[MAXN];
int n, m, s, t;
data2 EK_bfs()
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
    data2 ret;
    if (pre[t] == -1)
        ret.minn = -1;
    else
    {
        ret.minn = minn[t];
        ret.dis = dis[t];
    }
    return ret;
}
long long ans1 = 0;
long long ans2 = 0;
void EK()
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
            bool flag = true;
            for (int i = 0; i < g[u].size(); i++)
            {
                if (g[u][i].v == pre[u])
                {
                    g[u][i].w += tmp.minn;
                    flag = false;
                }
            }
            if (flag)
                g[u].push_back((data){pre[u], tmp.minn, -tmp_f});
            u = pre[u];
        }
        ans1 += tmp.minn;
        ans2 += tmp.minn * tmp.dis;
    }
}
int main()
{
    cin >> n >> m;
    s = 1;
    t = n;
    for (int i = 0; i < m; i++)
    {
        int u, v, w, f;
        cin >> u >> v >> w >> f;
        g[u].push_back((data){v, w, f});
    }
    EK();
    cout << ans2;
    return 0;
}
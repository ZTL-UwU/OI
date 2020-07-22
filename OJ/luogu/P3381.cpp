#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
const int MAXN = 5e3 + 10;
struct data2 { int minn, dis; };
struct data { int v, w, f; };
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
    for (int i = 0; i < MAXN; i++) pre[i] = -1;
    queue<int> q;
    q.push(s);
    inque[s] = true;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inque[u] = false;
        for (int i = 0; i < q.size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            int f = g[u][i].f;
            if (w > 0 && pre[v] == -1 && dis[v] > dis[u] + f)
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
    {
        ret.minn = -1;
        ret.dis = -1;
    }
    else
    {
        ret.minn = minn[t];
        ret.dis = dis[t];
    }
    return ret;
}
long long EK()
{
    long long ans = 0;
    while (1)
    {
        data2 tmp = EK_bfs();
        if (tmp.minn == -1)
            break;
        int u = t;
        while (u != s)
        {
            g[pre[u]][u].w -= tmp.minn;
            bool flag = false;
            for (int i = 0; i < g[u].size(); i++)
                if (g[u][i].v == pre[u])
                    flag = true;
            if (flag)
                g[u][pre[u]].w += tmp.minn;
            else
                g[u].push_back((data){pre[u], tmp.minn, -g[u][pre[u]].f});
            u = pre[u];
        }
        ans += tmp.minn;
    }
    return ans;
}
int main()
{
    cin >> n >> m >> s >> t;
    for (int i = 0; i < m; i++)
    {
        int u, v, w, f;
        cin >> u >> v >> w >> f;
        g[u].push_back((data){v, w, f});
    }
    cout << EK() << " " << dis[t];
    return 0;
}
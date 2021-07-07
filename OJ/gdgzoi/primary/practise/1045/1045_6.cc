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
const int INF = 0x7fffffff;
const int MAXN = 1e3;
vector<data> g[MAXN];
int n, k, d, s, t;
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
        for (int i = 0; i < g[u].size(); i++)
        {
            int v = g[u][i].v;
            int w = g[u][i].w;
            if (pre[v] == -1 && w)
            {
                minn[v] = min(minn[u], w);
                pre[v] = u;
                q.push(v);
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
            for (int i = 0; i < g[pre[u]].size(); i++)
            {
                if (g[pre[u]][i].v == u)
                {
                    g[pre[u]][i].w -= tmp;
                    break;
                }
            }
            bool flag = true;
            for (int i = 0; i < g[u].size(); i++)
            {
                if (g[u][i].v == pre[u])
                {
                    g[u][i].w += tmp;
                    flag = false;
                    break;
                }
            }
            if (flag)
                g[u].push_back((data){pre[u], tmp});
            u = pre[u];
        }
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k >> d;
    s = 0;
    t = n + d + 1;
    for (int i = 1; i <= d; i++)
    {
        int w;
        cin >> w;
        g[n + i].push_back((data){t, w});
    }
    for (int i = 1; i <= n; i++)
    {
        int z;
        cin >> z;
        g[s].push_back((data){i, k});
        for (int j = 0; j < z; j++)
        {
            int dd;
            cin >> dd;
            g[i].push_back((data){n + dd, 1});
        }
    }
    cout << EK();
    return 0;
}
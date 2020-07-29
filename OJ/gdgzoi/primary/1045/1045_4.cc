#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;
struct data { int v, w; };
vector<data> g[2010];
int love[1010][30];
int minn[2010];
int pre[2010];
int val[30];
int n, b, s, t;
inline int EK_bfs()
{
    memset(minn, 127, sizeof(minn));
    for (int i = 0; i < 2010; i++)
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
            if (pre[v] == -1 && w > 0)
            {
                pre[v] = u;
                minn[v] = min(minn[u], w);
                q.push(v);
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
        }
    }
    return ans;
}
inline void init()
{
    for (int i = 0; i < 2010; i++)
        g[i].clear();
}
int main()
{
    cin >> n >> b;
    s = 0;
    t = n + b + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= b; j++)
            cin >> love[i][j];
    for (int i = 1; i <= b; i++)
        cin >> val[i];
    int ans = -1;
    for (int l = 1; l <= b; l++)
    {
        for (int r = l; r <= n; r++)
        {
            init();
            for (int i = 1; i <= n; i++)
            {
                g[s].push_back((data){i, 1});
                for (int j = l ; j <= r; j++)
                    g[i].push_back((data){j, 1});
            }
            for (int i = 1; i <= b; i++)
                g[i].push_back((data){s, val[i]});
            if (EK() >= n)
                ans = max(ans, r - l);
        }
    }
    cout << ans;
    return 0;
}
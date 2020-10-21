#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
struct data
{
    int v;
    int w;
};
const int INF = 0x7fffffff;
const int MAXN = 1000;
vector<data> g[MAXN];
char mp[MAXN][MAXN];
int minn[MAXN];
int pre[MAXN];
int n, k, s, t;
inline int EK_bfs()
{
    for (int i = 0; i < MAXN; i++)
    {
        minn[i] = INF;
        pre[i] = -1;
    }
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
            bool found = false;
            for (int i = 0; i < g[u].size(); i++)
            {
                if (g[u][i].v == pre[u])
                {
                    g[u][i].w += tmp;
                    found = true;
                    break;
                }
            }
            if (!found)
                g[u].push_back((data){pre[u], tmp});
            u = pre[u];
        }
    }
    return ans;
}
inline void build(int limit)
{
    for (int i = 0; i < MAXN; i++)
        g[i].clear();
    for (int i = 1; i <= n; i++)
    {
        g[s].push_back((data){i, limit});
        g[i].push_back((data){n + i, k});
        g[3 * n + i].push_back((data){t, limit});
        g[2 * n + i].push_back((data){3 * n + i, k});
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (mp[i][j] == 'Y')
                g[i].push_back((data){3 * n + j, 1});
            else
                g[n + i].push_back((data){2 * n + j, 1});
        }
    }
}
inline int solve()
{
    int l = 0;
    int r = n;
    while (r - l > 1)
    {
        int mid = (r + l) / 2;
        build(mid);
        if (EK() == mid * n)
            l = mid;
        else
            r = mid;
    }
    build(r);
    return EK() == r * n ? r : l;
}
int main()
{
    cin >> n >> k;
    s = 0;
    t = 4 * n + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cin >> mp[i][j];
    cout << solve();
    return 0;
}